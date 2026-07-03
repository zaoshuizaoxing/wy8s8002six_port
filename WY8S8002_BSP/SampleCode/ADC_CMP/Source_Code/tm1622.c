#define TM1622_IMPLEMENTATION
#include "tm1622.h"

/* ============================================================
 *  字模表（与本屏段位图绑定，同款屏直接沿用）
 * ============================================================ */

/* 测试用全屏填充数据 */
unsigned char code date0[]={0x0B,0x00,0x07,0x05,0x0C,0x0D,0x0F,0x00,0x0F,0x0D,0x0B,0x00,0x07,0x05,0x0C,0x0D,0x0F,0x00,0x0F,0x0D,0x0B,0x00,0x07,0x05,0x0C,0x0D,};
unsigned char code date1[]={0x0E,0x06,0x0C,0x0e,0x06,0x0A,0x0A,0x0E,0x0E,0x0E,0x0E,0x06,0x0C,0x0e,0x06,0x0A,0x0A,0x0E,0x0E,0x0E,0x0E,0x06,0x0C,0x0e,0x06,0x0A,};

/* 电流数字字模（每数字2字节，0~9） */
unsigned char code cur_dbuf[] = {0xe,0x0e,0x08,0x04,0x6,0xd,0xa,0xd,0x8,0x7,0xa,0xb,0xe,0xb,0x08,0x0c,0xe,0x0f,0xa,0xf};

/* 电压/功率数字字模（每数字2字节，0~9） */
unsigned char code vol_dbuf[] = {0x07,0x07,02,01,0xb,0x6,0xb,0x5,0xe,0x1,0xd,0x5,0xd,0x7,3,1,0xf,0x7,0xf,05};

/* ============================================================
 *  显存映射表（路号→显存逻辑地址，与本屏走线绑定）
 *  每路2个地址：[i*2]=十位, [i*2+1]=个位
 * ============================================================ */
unsigned char code cur_chenlbuf[10]  = {12,13,14,15,16,17,18,19,20,21};
unsigned char code vol_chenlbuf[10]  = {22,23,24,25,26,27,28,29,30,31};
unsigned char code powr_chenlbuf[10] = {11,10,8,7,6,5,3,2,1,0};

/* 功率符号标志（×10/单位W/小数点） */
data struct {
    unsigned char bc[5];
    unsigned char wpr[5];
    unsigned char tpr[5];
} powr_infor;

/* 显存镜像（内部，业务层不可见） */
#define LCD_MAX_BUF  64
static unsigned char xdata disp_buf[LCD_MAX_BUF];

/* ============================================================
 *  通信层
 * ============================================================ */

/***************写 100 命令函数***************
 * 帧格式: [1][0][0] + 8bit命令(MSB先) + 结束位
 * ********************************************/
void write_cmd_100(unsigned char cmd)
{
	unsigned char i;

	CS_LOW();
	WR_LOW();  TM1622_NOP(); DATA_HIGH(); TM1622_NOP(); WR_HIGH(); TM1622_NOP();
	WR_LOW();  TM1622_NOP(); DATA_LOW();  TM1622_NOP(); WR_HIGH(); TM1622_NOP();
	WR_LOW();  TM1622_NOP(); DATA_LOW();  TM1622_NOP(); WR_HIGH(); TM1622_NOP();

	for(i = 0; i < 8; i++)
	{
		WR_LOW();
		DATA_SET(cmd & 0x80);
		TM1622_NOP();
		WR_HIGH();
		cmd <<= 1;
	}

	WR_LOW();  TM1622_NOP(); DATA_LOW(); TM1622_NOP(); WR_HIGH(); TM1622_NOP();
	WR_LOW();  TM1622_NOP();
	CS_HIGH();
}

/***************写 101 数据函数***************
 * 帧格式: [1][0][1] + 6bit地址(MSB先) + 4bit数据(LSB先)
 * ********************************************/
void write_101(unsigned char address, unsigned char dat)
{
	unsigned char i, add;
	add = address << 2;

	CS_LOW();
	WR_LOW();  TM1622_NOP(); DATA_HIGH(); TM1622_NOP(); WR_HIGH(); TM1622_NOP();
	WR_LOW();  TM1622_NOP(); DATA_LOW();  TM1622_NOP(); WR_HIGH(); TM1622_NOP();
	WR_LOW();  TM1622_NOP(); DATA_HIGH(); TM1622_NOP(); WR_HIGH(); TM1622_NOP();

	for(i = 0; i < 6; i++)
	{
		WR_LOW();
		DATA_SET(add & 0x80);
		TM1622_NOP();
		WR_HIGH();
		add <<= 1;
	}

	for(i = 0; i < 4; i++)
	{
		WR_LOW();
		DATA_SET(dat & 0x01);
		WR_HIGH();
		TM1622_NOP();
		dat >>= 1;
	}

	WR_LOW();
	DATA_LOW();
	CS_HIGH();
}

/* 整屏刷新到芯片 */
static void display_inputbuf(unsigned char *pty, unsigned int len)
{
	unsigned int i;
	for(i = 0; i < len; i++)
	{
		write_101(i, *pty);
		pty++;
	}
}

/***************TM1622 初始化函数**************/
void init_tm1622(void)
{
	unsigned char i;

	TM1622_GPIO_INIT();
	write_cmd_100(0x01);  /* 打开系统振荡器 */
	write_cmd_100(0x03);  /* 开启 LCD 显示   */
	write_cmd_100(0x18);  /* 片内 RC 32KHz   */
	write_cmd_100(0xe3);  /* 正常模式        */

	for(i = 0; i < 64; i++)   /* 清显存 */
	{
		write_101(i, 0);
	}
}

/* ============================================================
 *  显示层 - 段码填充逻辑（与本屏布局绑定）
 * ============================================================ */

/* 清屏 */
void TM1622_Clear(void)
{
	unsigned char i;
	for(i = 0; i < LCD_MAX_BUF; i++) disp_buf[i] = 0;
	display_inputbuf(disp_buf, LCD_MAX_BUF);
}

/* 更新5路数据并刷新整屏
 * ch: 指向5个 TM1622_Channel_t 的数组 */
void TM1622_UpdateAll(TM1622_Channel_t *ch)
{
	unsigned char i;
	unsigned char a, b, c;
	unsigned char qk;
	unsigned int  pwr;

	/* ---- 电流填充 ---- */
	for(i = 0; i < TM1622_CH_COUNT; i++)
	{
		if(ch[i].active)
		{
			a = ch[i].cur / 100;
			b = ch[i].cur % 100 / 10;
			c = ch[i].cur % 10;
		}
		else { a = 0; b = 0; c = 0; }

		if(a == 0 && b == 0 && c == 0)
		{
			disp_buf[cur_chenlbuf[i * 2]       * 2]     = cur_dbuf[0] | 0x01;
			disp_buf[cur_chenlbuf[i * 2]       * 2 + 1] = cur_dbuf[0];
			disp_buf[cur_chenlbuf[i * 2 + 1]   * 2]     = cur_dbuf[0] | 0x01;
			disp_buf[cur_chenlbuf[i * 2 + 1]   * 2 + 1] = cur_dbuf[0];
		}
		else
		{
			disp_buf[cur_chenlbuf[i * 2]       * 2]     = cur_dbuf[b * 2]     | 0x01;
			disp_buf[cur_chenlbuf[i * 2]       * 2 + 1] = cur_dbuf[b * 2 + 1];
			disp_buf[cur_chenlbuf[i * 2 + 1]   * 2]     = cur_dbuf[c * 2]     | 0x01;
			disp_buf[cur_chenlbuf[i * 2 + 1]   * 2 + 1] = cur_dbuf[c * 2 + 1];
		}
	}

	/* ---- 电压填充 ---- */
	for(i = 0; i < TM1622_CH_COUNT; i++)
	{
		a = ch[i].vol / 100;
		b = ch[i].vol % 100 / 10;
		c = ch[i].vol % 10;
		if(a == 0)
		{
			disp_buf[vol_chenlbuf[i * 2]       * 2]     = vol_dbuf[b * 2];
			disp_buf[vol_chenlbuf[i * 2]       * 2 + 1] = vol_dbuf[b * 2 + 1] | 0x08;
			disp_buf[vol_chenlbuf[i * 2 + 1]   * 2]     = vol_dbuf[c * 2];
			disp_buf[vol_chenlbuf[i * 2 + 1]   * 2 + 1] = vol_dbuf[c * 2 + 1] | 0x08;
		}
		else
		{
			disp_buf[vol_chenlbuf[i * 2]       * 2]     = vol_dbuf[a * 2];
			disp_buf[vol_chenlbuf[i * 2]       * 2 + 1] = vol_dbuf[a * 2 + 1];
			disp_buf[vol_chenlbuf[i * 2 + 1]   * 2]     = vol_dbuf[b * 2];
			disp_buf[vol_chenlbuf[i * 2 + 1]   * 2 + 1] = vol_dbuf[b * 2 + 1] | 0x08;
		}
	}

	/* ---- 功率填充 ---- */
	for(i = 0; i < TM1622_CH_COUNT; i++)
	{
		pwr = ch[i].powr;
		qk = 0;
		if(ch[i].active)
		{
			if(pwr >= 1000) { qk = 1; pwr = pwr / 10; }
			a = pwr / 100;
			b = pwr % 100 / 10;
			c = pwr % 10;
		}
		else { a = 0; b = 0; c = 0; qk = 0; }

		powr_infor.bc[i]  = 0;
		powr_infor.wpr[i] = 1;
		powr_infor.tpr[i] = 0;

		if(a == 0 && b == 0 && c == 0 && qk == 0)
		{
			disp_buf[powr_chenlbuf[i * 2]     * 2]     = vol_dbuf[0];
			disp_buf[powr_chenlbuf[i * 2]     * 2 + 1] = vol_dbuf[0];
			disp_buf[powr_chenlbuf[i * 2 + 1] * 2]     = vol_dbuf[0];
			disp_buf[powr_chenlbuf[i * 2 + 1] * 2 + 1] = vol_dbuf[0];
			powr_infor.tpr[i] = 1;
		}
		else if(a == 0 && qk == 0)
		{
			disp_buf[powr_chenlbuf[i * 2]     * 2]     = vol_dbuf[b * 2];
			disp_buf[powr_chenlbuf[i * 2]     * 2 + 1] = vol_dbuf[b * 2 + 1];
			disp_buf[powr_chenlbuf[i * 2 + 1] * 2]     = vol_dbuf[c * 2];
			disp_buf[powr_chenlbuf[i * 2 + 1] * 2 + 1] = vol_dbuf[c * 2 + 1];
			powr_infor.tpr[i] = 1;
		}
		else if(a > 0)
		{
			if(qk == 0)
			{
				disp_buf[powr_chenlbuf[i * 2]     * 2]     = vol_dbuf[a * 2];
				disp_buf[powr_chenlbuf[i * 2]     * 2 + 1] = vol_dbuf[a * 2 + 1];
				disp_buf[powr_chenlbuf[i * 2 + 1] * 2]     = vol_dbuf[b * 2];
				disp_buf[powr_chenlbuf[i * 2 + 1] * 2 + 1] = vol_dbuf[b * 2 + 1];
			}
			else
			{
				powr_infor.bc[i] = 1;
				disp_buf[powr_chenlbuf[i * 2]     * 2]     = vol_dbuf[b * 2];
				disp_buf[powr_chenlbuf[i * 2]     * 2 + 1] = vol_dbuf[b * 2 + 1];
				disp_buf[powr_chenlbuf[i * 2 + 1] * 2]     = vol_dbuf[c * 2];
				disp_buf[powr_chenlbuf[i * 2 + 1] * 2 + 1] = vol_dbuf[c * 2 + 1];
			}
		}
	}

	/* ---- 符号位拼接（×10/单位W/小数点） ---- */
	disp_buf[2*9]     = 0;
	disp_buf[2*9 + 1] = 0;
	if(powr_infor.wpr[0] == 1) disp_buf[2*9 + 1] |= 0x08;
	if(powr_infor.bc[1]  == 1) disp_buf[2*9 + 1] |= 0x04;

	disp_buf[2*4]     = 0;
	disp_buf[2*4 + 1] = 0;
	if(powr_infor.wpr[2] == 1) disp_buf[2*4]     |= 0x04;
	if(powr_infor.bc[3]  == 1) disp_buf[2*4]     |= 0x02;
	if(powr_infor.bc[4]  == 1) disp_buf[2*4]     |= 0x01;

	if(powr_infor.bc[2] == 1) disp_buf[powr_chenlbuf[4] * 2 + 1] |= 0x08;
	if(powr_infor.bc[0] == 1) disp_buf[powr_chenlbuf[0] * 2 + 1] |= 0x08;

	if(powr_infor.tpr[0] == 1) disp_buf[powr_chenlbuf[1] * 2 + 1] |= 0x08;
	if(powr_infor.tpr[1] == 1) disp_buf[powr_chenlbuf[2] * 2 + 1] |= 0x08;
	if(powr_infor.tpr[2] == 1) disp_buf[powr_chenlbuf[5] * 2 + 1] |= 0x08;
	if(powr_infor.tpr[3] == 1) disp_buf[powr_chenlbuf[6] * 2 + 1] |= 0x08;
	if(powr_infor.tpr[4] == 1) disp_buf[powr_chenlbuf[8] * 2 + 1] |= 0x08;

	if(powr_infor.wpr[1] == 1) disp_buf[powr_chenlbuf[3] * 2 + 1] |= 0x08;
	if(powr_infor.wpr[3] == 1) disp_buf[powr_chenlbuf[7] * 2 + 1] |= 0x08;
	if(powr_infor.wpr[4] == 1) disp_buf[powr_chenlbuf[9] * 2 + 1] |= 0x08;

	/* ---- 刷新到芯片 ---- */
	display_inputbuf(disp_buf, LCD_MAX_BUF);
}
