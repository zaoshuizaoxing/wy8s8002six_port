# TM1622 LCD ??????

- Source PDF: `C:\Users\ThinkPadX390\Desktop\wy8s8002six_port\TM-TM1622.pdf`
- Converted: 2026-07-03
- Usage: TM1622 LCD ??????????? CS/RD/WR/DATA ??????????????????? RAM?
- Note: This Markdown is text extracted from the vendor PDF. Tables may need cross-checking against the original PDF layout for board-signoff decisions.

## Page Index

- [Page 1](#page-1)
- [Page 2](#page-2)
- [Page 3](#page-3)
- [Page 4](#page-4)
- [Page 5](#page-5)
- [Page 6](#page-6)
- [Page 7](#page-7)
- [Page 8](#page-8)
- [Page 9](#page-9)
- [Page 10](#page-10)
- [Page 11](#page-11)
- [Page 12](#page-12)
- [Page 13](#page-13)
- [Page 14](#page-14)
- [Page 15](#page-15)
- [Page 16](#page-16)

## Page 1

1 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
特性描述 
 
TM1622是256点内存映象和多功能的LCD驱动专用芯片,TM1622的软件配置特性使它适用于多种LCD应用
场合,包括:LCD模块和显示子系统。用于连接主控制器和TM1622的管脚只有4或5条，TM1622还有一个节电命
令用于降低系统功耗。本产品性能优良、质量可靠。 
 
功能特点 
 
 工作电压2.4~ 5.2V 
 内置32 KHz RC振荡器 
 可外接32KHz频率源作为时钟输入 
 内置时基频率源 
 内置蜂鸣器输出驱动，有两种输出频率可选(2 KHz或者4 KHz) 
 
内置节电模式，可用于减少功耗 
 
内置时基发生器和看门狗（WDT）输出 
 
内置32ⅹ8位显示寄存器,32个SEG，8个COM输出驱动, 1/4偏压 
 
四线串行接口 
 
提供VLCD管脚用于调整LCD操作电压 
 
三种数据访问模式 
 
八个时基/看门狗定时器时钟源 
 
数据模式和命令模式指令 
 
三种封装形式可选：LQFP44（短脚），LQFP52，LQFP64, 
 
内部结构框图 
 
控制和时
序电路
蜂鸣器
驱动电路
32*8显存
LCD驱动/偏
压发生电路
看门狗和
时基输出
OSCI
CS
RD
WR
DATA
VDD
GND
BZ
BZ
COM0
COM7
......
......
.....
.....
SEG0
SEG31
VLCD
IRQ

## Page 2

2 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
管脚排列 
 
11
10
9
8
7
6
5
DATA
4
3
2
1
T2
22
21
20
19
18
17
16
15
14
13
T3
12
23
24
25
26
27
28
29
30
31
32
33
SEG2
34
35
36
37
38
39
40
41
42
43
44
TM1622
T1
IRQ
VSS
WR
RD
COM0
SEG10
SEG11
SEG12
SEG23
VLCD
VDD
OSCI
SEG3
SEG4
SEG5
SEG6
SEG7
SEG8
SEG9
SEG0
SEG1
SEG22
SEG21
SEG20
SEG19
SEG18
SEG17
SEG16
SEG15
SEG14
SEG13
14
13
12
11
10
9
8
7
6
5
4
3
2
1
15
T3
16
VLCD
30
29
28
27
26
25
24
23
22
21
20
19
18
COM0
17
31
32
35
36
37
38
39
40
41
42
43
44
45
46
47
48
34
33
NC
51
52
53
54
55
56
57
58
59
60
61
62
63
64
SEG31
50
49
NC
T2
T1
BZ
NC
BZ
IRQ
VDD
OSCI
VSS
DATA
WR
RD
NC
CS
NC
NC
SEG7
COM1
COM2
COM3
COM4
COM5
COM6
COM7
TOP VIEW
QFP44/LQFP44
TM1622
TOP VIEW
LQFP64
COM1
NC
COM2
COM3
COM4
COM5
COM6
COM7
SEG0
SEG1
SEG2
SEG3
SEG4
SEG5
SEG6
SEG8
SEG9
SEG10
SEG11
SEG12
SEG13
SEG14
SEG15
SEG16
SEG17
SEG18
SEG19
NC
NC
NC
SEG30
SEG29
SEG28
SEG27
SEG26
SEG25
SEG24
SEG23
SEG22
SEG21
SEG20
13
12
11
10
9
8
7
6
5
4
3
2
1
VLCD
26
25
24
23
22
21
20
19
18
17
16
15
COM1
14
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
SEG31
SEG19
COM0
T3
T1
IRQ
VDD
OSCI
VSS
DATA
WR
RD
CS
SEG6
TM1622
TOP VIEW
QFP52
COM2
COM3
COM4
COM5
COM6
COM7
SEG0
SEG1
SEG2
SEG3
SEG4
SEG5
SEG8
SEG9
SEG10
SEG11
SEG12
SEG13
SEG14
SEG15
SEG16
SEG17
SEG18
SEG30
SEG29
SEG28
SEG27
SEG26
SEG25
SEG24
SEG23
SEG22
SEG21
SEG20
T2
SEG7
14
13
12
11
10
9
8
7
6
5
4
3
2
1
15
T3
16
VLCD
32
31
30
29
28
27
26
25
24
23
22
21
20
38
39
40
41
42
43
44
45
46
47
48
49
50
51
37
36
NC
52
53
54
55
56
57
58
59
60
61
62
63
64
SEG31
NC
T2
T1
BZ
NC
BZ
IRQ
VDD
OSCI
VSS
DATA
WR
RD
NC
CS
NC
NC
SEG7
TM1622
TOP VIEW
LQFP64
COM2
COM3
COM4
COM5
COM6
COM7
SEG0
SEG1
SEG2
SEG3
SEG8
SEG9
SEG10
SEG11
SEG12
SEG13
SEG14
SEG15
SEG16
SEG17
SEG18
SEG19
SEG30
SEG29
SEG28
SEG27
SEG26
SEG25
SEG24
SEG23
SEG22
SEG21
SEG20
COM0
17
35
NC
COM1
18
34
NC
NC
19
33
NC
SEG4
SEG5
SEG6
CS

## Page 3

3 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
管脚功能 
 
管脚名称 
管脚序号 
I/O 
功能说明 
CS 
1 
I 
 片选信号，CS 为高时，读写数据或者命令无效，串行接口电路复
位，CS 为低电平时，可正常读写数据和命令 
RD 
3 
I 
READ模式时钟输入，在RD 信号源的下沿，显存内的数据会写到DATA线
上，TM1622可以在下一个RD 上升沿锁存这些数据 
WR 
4 
I 
WRITE模式时钟输入，在WR 信号上升沿时，DATA线上的数据被写进
TM1622 
DATA 
5 
I/O 
串行数据输入/输出 
GND 
6 
- 
接系统地 
OSCI 
7 
I 
外接一32KHz频率源，若用内部RC振荡器，该脚应该浮空 
VDD 
8 
- 
芯片电源输入 
VLCD 
9 
I 
LCD偏压输入 
IRQ 
10 
O 
时基或看门狗定时器溢出标志位，NMOS开漏输出 
BZ/ BZ 
11/13 
O 
蜂鸣器输出驱动 
T1，T2，T3 14，15，16, 
I 
偏压输入，正常使用中不建议使用 
COM0~COM7 
17~25 
O 
LCD COM端驱动输出口 
SEG0~SEG31 
26~64 
O 
LCD SEG端驱动输出口 
NC 
2,12,19,33,34, 
35,49,50,51,52 
不连接 
*备注：上表中的管脚序号，以LQFP64 封装为例。不同的封装，脚位有所不一样，详情请参考管脚排列图。 
 
输入输出等效电路 
 
 
 
集成电路系静电敏感器件，在干燥季节或者干燥环境使用容易产生大量静电，静电放电可能会
损坏集成电路，天微电子建议采取一切适当的集成电路预防处理措施，不正当的操作 
焊接，可能会造成ESD 损坏或者性能下降，芯片无法正常工作。

## Page 4

4 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
极限参数
（1）（2） 
 
参数名称 
参数符号 
极限值 
单 位 
逻辑电源电压 
VDD 
-0.5～+7.0 
V 
输入端电压范围 
Data, CS , WR , RD 
Vin 
-0.5～VDD+0.5 
V 
工作温度范围 
Topr 
-40～+85 
℃ 
储存温度范围 
Tstg 
-55～+150 
℃ 
人体模式（HBM） 
ESD 
2000 
V 
机器模式（MM） 
200 
V 
（1）芯片长时间工作在上述极限参数条件下，可能造成器件可靠性降低或永久性损坏，天微电子不建议实
际使用时任何一项参数达到或超过这些极限值。 
（2）所有电压值均相对于系统地测试。 
 
推荐工作条件 
 
在-45℃~+85℃下测试，除非另有说明 
TM1622 
单位 
参数名称 
参数符号 
测试条件 
最小值 
典型值 
最大值 
电源电压 
VDD 
- 
2.7 
5.0 
5.2 
V 
外置时钟频率 
Ext_CLOCK 
 
 
32 
 
KHz 
工作温度范围 
Ta 
 
-20 
 
+85 
℃ 
工作结温范围 
Tj 
 
-40 
 
+125 
℃ 
 
AC 电气特性 
 
在VDD=5.0V 及工作温度为-40℃~+85℃下测试，典型值在
VDD=5.0V 和Ta=+25℃条件下得出，除非另有说明 
TM1622 
单位 
参数名称 
参数符号 
测试条件 
最小值 
典型值 
最大值 
系统时钟 
Fsys1 
VDD=3.0V，片内RC 
24 
32 
40 
KHz 
VDD=5.0V，片内RC 
VDD=3.0/5.0V,外部时钟 
- 
32 
- 
LCD 驱动扫描频率 
Flcd 
VDD=3.0V,片内RC 
24 
32 
40 
Hz 
VDD=5.0V，片内RC 
24 
32 
40 
VDD=3.0/5.0V,外部时钟 
- 
32 
- 
COM 时钟周期 
Tcom 
n 个COM 口 
 
n/Flcd 
 
Hz 
WR 时钟频率 
Fclk1 
VDD=5.0V,50%占空比 
4 
 
300 
KHz 
VDD=3.0V,50%占空比 
4 
 
150 
RD 时钟频率 
Fclk2 
VDD=5.0V,50%占空比 
1 
 
75 
KHz 
VDD=3.0V,50%占空比 
1 
 
150 
CS 高电平宽度 
Tcsh 
 
500 
600 
- 
ns 
WR ，RD 输入电平持续
时间 
Tclk 
VDD=5.0V，写模式 
3.5 
 
125 
μs 
VDD=5.0V，读模式 
6.7 
 
 
VDD=3.0V，写模式 
1.7 
 
125 
VDD=3.0V，读模式 
3.4 
 
 
声音输出频率 
Ftone 
TONE 2K,片内RC 
1.5 
2.0 
2.5 
KHz 
TONE 4K,片内RC 
3 
4 
5

## Page 5

5 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
DC 电气特性 
 
在VDD=5.0V 及工作温度为-40℃~+85℃下测试，典型值在
VDD=5.0V 和Ta=+25℃条件下得出，除非另有说明 
TM1622 
单位 
参数名称 
参数符号 
VDD 
测试条件 
最小值 
典型值 
最大值 
工作电压 
VDD 
- 
- 
2.4 
5.0 
5.2 
V 
工作电流 
Idd 
3.0V 
片内RC，空载 
 
100 
300 
μA 
5.0V 
片内RC，空载 
 
150 
500 
工作电流 
Idd1 
3.0V 
外部时钟，空载 
 
50 
120 
μA 
5.0V 
外部时钟，空载 
 
120 
240 
待机电流 
IDD2 
3.0V 
省电模式，空载 
 
1 
5 
μA 
5.0V 
省电模式，空载 
 
1.5 
10 
COM 时钟周期 
Tcom 
 
n 个COM 口 
 
n/Flcd 
 
Hz 
WR 时钟频率 
Fclk1 
3.0V 
50%占空比 
4 
 
150 
KHz 
5.0V 
50%占空比 
4 
 
300 
RD 时钟频率 
Fclk2 
3.0V 
50%占空比 
1 
 
150 
KHz 
5.0V 
50%占空比 
1 
 
75 
CS 高电平宽度 
Tcsh 
 
 
500 
600 
- 
ns 
WR ，RD 输入高低电平
持续时间 
Tclk 
3.0V 
写模式 
1.7 
 
125 
μs 
5.0V 
读模式 
3.4 
 
 
3.0V 
写模式 
3.5 
 
125 
5.0V 
读模式 
6.7 
 
 
输入低电平电压 
Vil 
3.0V 
DATA, WR , CS ,
RD 
0 
 
0.6 
V 
5.0V 
0 
 
1.0 
输入高电平电压 
Vih 
3.0V 
DATA, WR , CS ,
RD 
1.2 
 
3.0 
V 
5.0V 
1.6 
 
5.0 
DATA,BZ, BZ
IRQ 灌电
流 
IOL1 
3.0V 
Vol=0.5V 
2 
4.5 
- 
mA 
5.0V 
Vol=0.5V 
1 
3 
 
DATA,BZ，BZ 拉电流 
IOh1 
3.0V 
Voh=2.5V 
-1 
-2 
 
mA 
5.0V 
Voh=4.5V 
-2 
-3.5 
 
SEG 灌电流 
Isegl 
3.0V 
Vseg=0.5V 
280 
400 
500 
μA 
5.0V 
Vseg=0.5V 
300 
430 
550 
SEG 拉电流 
Isegh 
3.0V 
Vseg=2.5V 
-110 
-160 
-210 
μA 
5.0V 
Vseg=4.5V 
-130 
-180 
-230 
COM 灌电流 
Icoml 
3.0V 
Vseg=0.5V 
410 
460 
510 
μA 
5.0V 
Vseg=0.5V 
410 
460 
510 
COM 拉电流 
Icomh 
3.0V 
Vseg=2.5V 
-120 
-170 
-220 
μA 
5.0V 
Vseg=4.5V 
-140 
-190 
-240

## Page 6

6 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
应用信息 
 
MCU
TM1622
CS
RD
WR
DATA
10K
1/4 Bias,1/8 Duty
IRQ
COM0~COM7
SEG0~SEG31
......
......
VDD
VLCD
VDD
LCD Panel
BZ
BZ
Piezo
*VR
GND
OSCI
104
*32KHz
 
说明： 
1、上图给出的简图以LQFP64封装的芯片为例。 
2、VLCD的电压必须小于或者等于VDD的电压。 
3、VLCD的上拉可调电阻用来调节LCD的控制电压，当VDD=5.0V，Vlcd=4.0V，则VR=15K±20%。 
4、如不需要读取TM1622 的显存数据，RD 可以不连接到MCU。 
5、VDD 对GND 的电容可以滤掉芯片VDD 上的产生的纹波，所以此电容不能省掉，并在PCB 布板时，尽量接
近芯片。 
6、芯片时钟可选片内RC 和外部时钟。如果使用内部RC 振荡，OSCI 脚必须保持浮空状态，*32KHz 的时钟
必须撤离，否则芯片可能不能正常工作。。 
7、TM1622 开LCD 显示后，COM 口循环输出阶梯波，这一特性使得TM1622 可以驱动2COM，4COM,8COM 的LCD。 
8、如果不使用时基/WDT 功能，IRQ 与MCU 的连线可以不连接。由于IRQ 为Nmos 开漏输出，所以如果使用
时基/WDT 功能，IRQ 必须接一10K 上拉电阻，否则IRQ 将不能输出高电平。

## Page 7

7 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
功能描述 
 
1:显示内存（RAM） 
 
 
 静态显示内存包含32×8 位的格式来存储需要显示的数据，RAM 的数据直接映像到LCD 显示驱动器，
也可以通过READ,WRITE,和READ-MODIFY-WRITE 命令进行读写操作，下图给出的为RAM 映像图 
COM7
SEG0
0
2
4
6
62
1
3
5
7
63
......
......
......
......
......
......
......
D3
COM6
COM5
COM4
COM3
COM2
COM1
COM0
SEG1
SEG2
SEG3
SEG31
D2
D0
D3
D2
D1
D0
Addr
Data
Data
Data 4 bits(D3,D2,D1,D0)
Addr
D1
 
 
2:时基和看门狗输出（WDT） 
 
 
时基发生器和看门狗输出（WDT）共用相同的（÷256）分频电路， TIMER EN/DIS/CLR， 
WDT EN/DIS/CLR 分别作用于时基发生器和看门狗电路。下图给出了示意图。 
IRQ
D
CK
÷4
÷256
Q
R
WDT
CLR WDT
TIMER EN/DIS
WDT EN/DIS
Time Base
CLR Timer
IRQ EN/DIS
Clock Source
VDD
 
开启WDT 后，一旦WDT 超时，IRQ 将被拉低，并一直保持低电平状态直到执行CLR WDT 或者执行IRQ DIS
命令后，才会关断IRQ 的输出，此时IRQ 输出高阻状态，被外部上拉电阻强制拉为高电平状态。 
如果选择外部时钟作为系统频率源时，SYS DIS 命令无效，系统也不能进入省电模式。TM1622 在断电或
者撤消外部时钟前，一直保持工作状态。

## Page 8

8 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
3:蜂鸣器驱动输出 
 
 
 TM1622 内置了一个简单的声音发生器，可以在BZ 和BZ 脚输出一对差动驱动信号，用于驱动蜂鸣
器产生一个单音。执行TONE2K 和TONE4K 命令后，可以输出2KHz 和4KHz 频率驱动蜂鸣器发出两种不同的
声音；TONEOFF 命令可以用于关闭声音输出。当系统失效或者执行了TONGOFF 命令后，BZ 和BZ 将保持低
电平输出状态。 
 
4:命令模式 
 
TM1622 可以用软件配置，两种模式的命令可以配置TM1622 和读写显存的数据，TM1622 的配置模式称
为命令模式，对芯片显存进行操作模式，称为数据模式，下表中给出了数据和命令模式的类型码表： 
操作 
模式 
类型码 
READ 
数据 
110 
WRITE 
数据 
101 
READ-MODIFY-WRITE 
数据 
101 
COMMAND 
命令 
100 
 
模式命令应该在数据或者命令传送前发送。如果要传送的连续命令，命令模式类型码100 只能发送一
次，后续紧跟着的命令不同命令的命令代码。在不连续命令模式或者不连续地址的数据模式下每次发完一个
命令或者一个数据指令后，CS 应该先置“1”，保证当前的的操作模式复位。CS 管脚置“0”后，应该先发
送新的操作模式类型码。 
 
5:通讯端口 
 
TM1622 只有四个管脚用于与MCU 的通讯，管脚CS 用于初始化串行接口电路和结束指令数据的传送。
CS 置“1”时，TM1622 不接受任何MCU 发送的命令和数据并且初始化串行接口。在不同的操作类型码之
间，CS 必须用一个高电平初始化TM1622 的串行接口，否则传送的命令或者数据会出错。管脚DATA 是串
行数据输入/输出脚，读/写数据可以通过DATA 与RD , WR 之间的配合来完成。管脚RD 是读显存时钟输
入脚，在RD 信号的下降沿时，显存内的数据会被输出到芯片DATA 寄存器里面，在RD 的上升沿和下一个
下降沿之间，DATA 寄存器里面的数据会被读出到DATA 脚上。管脚WR 是写时钟输入，在WR 信号上沿，
管脚DATA 上的数据，地址，命令将被写入到TM1622。可选的管脚IRQ ,可用作MCU 与TM1622 的通讯接口，
IRQ 可以通过软件设置作为时基定时器输出或者WDT 溢出标志位输出，MCU 与TM1622 的IRQ 相连后，可
以实现时基或者WDT 功能的应用。IRQ 由于是Nmos 开漏输出，使用过程中必须加10k 上拉电阻。如果不
需要使用时基或者WDT 功能，IRQ 可以浮空。

## Page 9

9 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
读写时序图 
 
READ 模式（命令代码：110） 
 
1
1
0
A5
A4
A3
A2
A1
A0
D0
D1
D2
D3
1
1
0
A5
A4
A3
A2
A1
A0
D0
D1
D2
D3
CS
WR
RD
DATA
Memory Address1(MA1)
Data(MA1)
Memory Address2(MA2)
Data(MA2)
 
READ 模式（读连续地址） 
 
1
1
0
A5
D0
CS
WR
RD
DATA
Memory Address(MA)
Data(MA)
Data(MA+1)
Data(MA+3)
Data(MA+2)
A4
A3
A2
A1
A0
D1
D2
D3
D0
D1
D2
D3
D0
D1
D2
D3
D0
D1
D2
D3
D0
 
WRITE 模式（命令代码：101） 
 
1
0
1
A5
CS
WR
DATA
Memory Address1(MA1)
Data(MA1)
1
0
1
Memory Address2(MA2)
Data(MA2)
A4
A3
A2
A1
A0
D0
D1
D2
D3
A5
A4
A3
A2
A1
A0
D0
D1
D2
D3
 
WRITE 模式（写连续地址） 
 
1
0
1
A5
CS
WR
DATA
Memory Address1(MA)
Data(MA)
Data(MA+1)
Data(MA+2)
Data(MA+3)
A4
A3
A2
A1
A0
D0
D1
D2
D3
D0
D1
D2
D3
D0
D1
D2
D3
D0
D1
D2
D3
D0

## Page 10

10 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
READ-MODIFY-WRITE 模式（命令代码：101） 
 
1
1
0
A5
CS
WR
RD
DATA
Memory Address1(MA1)
Data(MA1)
Data(MA1)
Data(MA2)
1
1
0
A5
Memory Address2(MA2)
A4
A3
A2
A1
A0
D0
D1
D2
D3
D0
D1
D2
D3
A4
A3
A2
A1
A0
D0
D1
D2
D3
 
READ-MODIFY-WRITE 模式（访问连续地址） 
 
1
1
0
A5
A4
CS
WR
RD
DATA
Memory Address(MA)
Data(MA)
Data(MA)
Data(MA+1)
Data(MA+1)
Data(MA+2)
A3
A2
A1
A0
D0
D1
D2
D3
D0
D1
D2
D3
D0
D1
D2
D3
D0
D1
D2
D3
D0
D1
D2
D3
D0
 
命令模式（命令代码：100） 
 
1
0
0
C8
CS
WR
DATA
Command 1
Command
or
Data Mode
C7
C6
C5
C4
C3
C2
C1
C0
C8
C7
C6
C5
C7
C3
C2
C1
C0
Command 1
 
数据和命令模式 
 
CS
WR
RD
DATA
Command
or
Data Mode
Address and Data
Command
or
Data Mode
Address and Data
Command
or
Data Mode
Address and Data
 
备注：MCU 应该在RD 的上升沿和下一个下降沿之间读取DATA 上的数据，且RD 和WR 的波形不能有交
叉，即同一时刻，只允许单独对RD 或者WR 进行操作。

## Page 11

11 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
命令概述表 
 
命令名称 
类型码 
命令代码 
D/C 
功能描述 
上电复位
后缺省 
READ 
110 
A5 A4 A3 A2 A1 A0 D0 D1 D2 D3 
D 
读显存数据 
 
WRITE 
101 
A5 A4 A3 A2 A1 A0 D0 D1 D2 D3 
D 
写显存数据 
 
READ-MODIFY-WRITE 
101 
A5 A4 A3 A2 A1 A0 D0 D1 D2 D3 
D 
读和写数据 
 
SYS DIS 
100 
0000_0000_X 
C 
关闭系统振荡器和LCD 偏压发生器 
√ 
SYS EN 
100 
0000_0001_X 
C 
打开系统振荡器 
 
LCD OFF 
100 
0000_0010_X 
C 
关闭LCD 显示 
√ 
LCD ON 
100 
0000_0011_X 
C 
开启LCD 显示 
 
TIMER DIS 
100 
0000_0100_X 
C 
时基输出失效 
 
WDT DIS 
100 
0000_0101_X 
C 
WDT 溢出标志输出失效 
 
TIMER EN 
100 
0000_0110_X 
C 
使能时基输出 
 
WDT EN 
100 
0000_0111_X 
C 
使能WDT 溢出标志失效 
 
TONE OFF 
100 
0000_1000_X 
C 
关闭声音输出 
√ 
CLR TIMER 
100 
0000_1101_X 
C 
时基发生器清零 
 
CLR WDT 
100 
0000_1111_X 
C 
清除WDT 状态 
 
RC 32K 
100 
0001_10XX_X 
C 
系统时钟源，片内RC 振荡器 
√ 
EXT 32K 
100 
0001_11XX_X 
C 
系统时钟源，外部时钟源 
 
TONE 4K 
100 
010X_XXXX_X 
C 
声音输出频率：4KHz 
 
TONE 2K 
100 
0110_XXXX_X 
C 
声音输出频率：2KHz 
 
IRQ DIS 
100 
100X_0XXX_X 
C 
IRQ 输出失效 
√ 
IRQ EN 
100 
100X_1XXX_X 
C 
使能IRQ 输出 
 
F1 
100 
101X_0000_X 
C 
时基本输出频率：1Hz 
WDT 使能后输出延时：4 s 
 
F2 
100 
101X_0001_X 
C 
时基本输出频率：2Hz 
WDT 使能后输出延时：2s 
 
F4 
100 
101X_0010_X 
C 
时基本输出频率：4Hz 
WDT 使能后输出延时：1 s 
 
F8 
100 
101X_0011_X 
C 
时基本输出频率：8Hz 
WDT 使能后输出延时：1/2 s 
 
F16 
100 
101X_0100_X 
C 
时基本输出频率：16Hz 
WDT 使能后输出延时：1/4 s 
 
F32 
100 
101X_0101_X 
C 
时基本输出频率：32Hz 
WDT 使能后输出延时：1/8s 
 
F64 
100 
101X_0110_X 
C 
时基本输出频率：64Hz 
WDT 使能后输出延时：1/16 s 
 
F128 
100 
101X_0111_X 
C 
时基本输出频率：128Hz 
WDT 使能后输出延时：1/32 s 
√ 
TEST 
100 
1110-0000-X 
C 
测试模式，正常使用中不得发送 
 
NORMAL 
100 
1110-0011-X 
C 
正常模式 
√ 
注： 
1：X 不关心，建议写“0”。2：A5~A0 显存地址。3：D0~D4 显存数据。4：D/C 数据/命令模式。 
5：上电复位后缺省：上电复位后芯片默认的状态 
所有的粗体数字：即110，101，100 为模式命令类型码。100 为命令模式类型码，如果给TM1622 发送
连续的命令，除第一个命令外，其他的命令不能再发100 类型码。声音频率源和时基/WDT 时钟频率源由片
内的32KHz RC 振荡器或者外部的32KHz 频率源提供。输出频率计算详见前文中系统描述章节的时基和看门
狗输出（WDT）和上表中关于时基/WDT 频率输出频率设置指令F0~F128。建议在上电复位后，用MCU 初始化
TM1622，因为如果上电复位失败后，TM1622 将不能正常工作。 
TEST 指令（100 1110-0000-X），用户在正常使用过程中不得给芯片发送，否则芯片将进入测试模式，
而不能正常执行MCU 发送的其他命令和数据。

## Page 12

12 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
封装示意图 
LQFP44（短脚）： 
 
Item
Dimensions
表示
Unit
Spec
LP
LW
LL
FL
θ
Detail "X"
*Mold Option
*Mold Option
TL
BL
BW
FT
BW
TL
TH
SO
BT
BL
Detail "X"
总长
BL
BW
mm
10.10
(10.00)
9.90
mm
mm
mm
TL
LW
LP
FT
BT
SO
TH
LL
FL
Θ
胶体宽度
跨度
脚宽
脚间距
脚厚
胶体厚度
站高
胶体高度
脚长
单边长
脚角度
8
(4)
0
mm
mm
mm
mm
mm
mm
mm
10.10
(10.00)
9.90
12.05
(12.00)
11.95
0.350
TYP
0.800
TYP
0.150
(0.127)
0.100
1.45
(1.40)
1.35
0.150
(0.100)
0.050
1.550
Max.
1.10
(1.00)
0.90
0.70
(0.60)
0.50
(Φ1.20)
TOP E-MARK
 (Φ1.80)

## Page 13

13 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
封装示意图（LQFP52 14mm*14mm） 
Item
Dimensions
表示
Unit
Spec
LP
LW
LL
FL
θ
Detail "X"
*Mold Option
*Mold Option
TL
BL
BW
FT
BW
TL
TH
SO
BT
BL
Detail "X"
总长
BL
BW
mm
14.10
(14.00)
13.90
mm
mm
mm
TL
LW
LP
FT
BT
SO
TH
LL
FL
Θ
胶体宽度
跨度
脚宽
脚间距
脚厚
胶体厚度
站高
胶体高度
脚长
单边长
脚角度
8
(4)
0
mm
mm
mm
mm
mm
mm
mm
14.10
(14.00)
13.90
16.20
(16.00)
15.80
0.400
TYP
1.000
TYP
0.150
(0.127)
0.100
1.45
(1.40)
1.35
0.150
(0.100)
0.050
1.550
Max.
1.10
(1.00)
0.90
0.75
(0.60)
0.45
(Φ1.50)

## Page 14

14 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
封装示意图（LQFP64 7mm*7mm） 
Item
Dimensions
表示
Unit
Spec
LP
LW
LL
FL
θ
Detail "X"
*Mold Option
*Mold Option
TL
BL
BW
FT
BW
TL
TH
SO
BT
BL
Detail "X"
总长
BL
BW
mm
7.10
(7.00)
6.90
mm
mm
mm
TL
LW
LP
FT
BT
SO
TH
LL
FL
Θ
胶体宽度
跨度
脚宽
脚间距
脚厚
胶体厚度
站高
胶体高度
脚长
单边长
脚角度
8
(4)
0
mm
mm
mm
mm
mm
mm
mm
9.20
(9.00)
8.80
0.180
TYP
0.400
TYP
0.150
(0.127)
0.100
1.45
(1.40)
1.35
0.150
(0.100)
0.050
1.550
Max.
1.10
(1.00)
0.90
0.75
(0.60)
0.45
(Φ1.00)
7.10
(7.00)
6.90

## Page 15

15 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
封装示意图（LQFP64 14mm*14mm） 
Item
Dimensions
表示
Unit
Spec
LP
LW
LL
FL
θ
Detail "X"
*Mold Option
*Mold Option
TL
BL
BW
FT
BW
TL
TH
SO
BT
BL
Detail "X"
总长
BL
BW
mm
14.10
(14.00)
13.90
mm
mm
mm
TL
LW
LP
FT
BT
SO
TH
LL
FL
Θ
胶体宽度
跨度
脚宽
脚间距
脚厚
胶体厚度
站高
胶体高度
脚长
单边长
脚角度
8
(4)
0
mm
mm
mm
mm
mm
mm
mm
14.10
(14.00)
13.90
16.20
(16.00)
15.80
0.350
TYP
0.800
TYP
0.150
(0.127)
0.100
1.45
(1.40)
1.35
0.150
(0.100)
0.050
1.550
Max.
1.10
(1.00)
0.90
0.75
(0.60)
0.45
(Φ1.50)

## Page 16

16 
©Titan Micro Electronics www.titanmec.com 
V2.0 
32ⅹ8 LCD 驱动专用芯片 TM1622 
 
封装示意图（LQFP64 14mm*20mm，脚长1.2mm） 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
All specs and applications shown above subject to change without prior notice. 
(以上电路及规格仅供参考，如本公司进行修正，恕不另行通知)
