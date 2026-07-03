#ifndef _TM1622_H_
#define _TM1622_H_

/* ============================================================
 *  TM1622 段码 LCD 驱动 - 64段屏
 *  通信层 + 显示填充层（字模表/映射表/段码填充均已内置）
 *  同款屏换芯片移植：仅需修改下方管脚配置区
 * ============================================================ */
/* 显示路数（本屏固定5路：A2/A1/PD3/PD2/PD1） */
#define TM1622_CH_COUNT  5
/* 单路显示数据（业务层算好后传入） */
typedef struct {
    unsigned int  cur;     /* 电流，单位 0.1A */
    unsigned int  vol;     /* 电压，单位 0.1V */
    unsigned int  powr;    /* 功率，单位 0.1W */
    unsigned char active;  /* 1=充电中(显示数值), 0=空闲(显示0) */
} TM1622_Channel_t;
/* ============================================================
 *  管脚配置区（移植时修改此处）
 * ============================================================ */
#ifdef TM1622_IMPLEMENTATION
#include "common.h"
#include "gpio.h"
/* ---- 1. 引脚定义（修改此处更改接线） ---- */
#define TM1622_CS      P10
#define TM1622_WRITE   P11
#define TM1622_DATA    P12
/* ---- 2. 引脚操作宏（移植时改为目标平台的置/复位接口） ---- */
#define CS_HIGH()     (TM1622_CS = 1)
#define CS_LOW()      (TM1622_CS = 0)
#define WR_HIGH()     (TM1622_WRITE = 1)
#define WR_LOW()      (TM1622_WRITE = 0)
#define DATA_HIGH()   (TM1622_DATA = 1)
#define DATA_LOW()    (TM1622_DATA = 0)
#define DATA_SET(v)   (TM1622_DATA = (v))
/* ---- 3. GPIO 模式初始化（推挽输出，移植时改为目标芯片寄存器） ---- */
#define TM1622_GPIO_INIT()  do{ \
    PORT_SET_MUX(PIO10CFG, GPIO_MUX_MODE); \
    PORT_SET_MUX(PIO11CFG, GPIO_MUX_MODE); \
    PORT_SET_MUX(PIO12CFG, GPIO_MUX_MODE); \
    GPIO1_ConfigOutput(GPIO_PIN_0, GPIO_PP, GPIO_PULLUP, CURRENT_00); \
    GPIO1_ConfigOutput(GPIO_PIN_1, GPIO_PP, GPIO_PULLUP, CURRENT_00); \
    GPIO1_ConfigOutput(GPIO_PIN_2, GPIO_PP, GPIO_PULLUP, CURRENT_00); \
    CS_HIGH(); WR_HIGH(); DATA_LOW(); \
}while(0)

/* ---- 4. 短延时（按系统主频调整，保证时序裕量） ---- */
#define TM1622_NOP()  _nop_();_nop_();_nop_();_nop_();\
                       _nop_();_nop_();_nop_();_nop_()

#endif /* TM1622_IMPLEMENTATION */
/* ============================================================
 *  公共函数声明
 * ============================================================ */
/* --- 通信层 --- */
void init_tm1622(void);
void write_cmd_100(unsigned char cmd);
void write_101(unsigned char address, unsigned char dat);
/* --- 显示层 --- */
void TM1622_UpdateAll(TM1622_Channel_t *ch);  /* 更新5路数据并刷新整屏 */
void TM1622_Clear(void);                       /* 清屏 */
#endif /* _TM1622_H_ */
