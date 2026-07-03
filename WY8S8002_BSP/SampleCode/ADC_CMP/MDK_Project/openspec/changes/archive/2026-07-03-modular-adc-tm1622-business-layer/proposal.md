## Why

当前 ADC_CMP 示例工程仍以原厂 ADC 比较/PWM 刹车演示为主，业务所需的四路 ADC 采样、TM1622 显示、UART0、P06 软件 UART 接收和背光控制没有形成稳定的模块化规格与业务接口。

需要将已经确认的 WY8S8002A 引脚资源和 TM1622 显示驱动整合为可维护的业务固件基础，并把需求、设计和实现任务纳入 OpenSpec，避免代码实现与规格长期脱节。

## What Changes

- 将 `main.c` 从原厂 ADC_CMP 示例流程改为板级初始化 + 业务调度主循环。
- 新增板级配置层，统一初始化系统时钟、UART0、背光、TM1622、ADC 采样和 P06 软件 UART。
- 新增四路 ADC 采样模块，按手册确认的 `P02/P03/P04/P05 = AIN7/AIN6/AIN5/AIN4` 轮询采样。
- 将 TM1622 平台层移植到 WY8S8002A，使用 `P10=CS`、`P11=WR`、`P12=DATA` 三线写入接口。
- 新增 P06 GPIO 中断 + Timer2 采样的软件 UART 接收模块。
- 新增业务逻辑层 `g_app`，业务层通过全局状态和封装接口使用底层驱动。
- 从 Keil 工程编译列表移除旧 `adc_cmp.c` 示例，避免旧 ADC 中断和 P11 测试输出与新业务资源冲突。

## Capabilities

### New Capabilities

- `wy8s8002-board-resources`: WY8S8002A 板级引脚资源、时钟、UART0、背光、TM1622 和软件 UART 初始化约束。
- `adc-sampling`: 四路 ADC 输入采样、通道映射和毫伏换算接口。
- `tm1622-display`: TM1622 三线写入、初始化、清屏和 5 路业务显示刷新接口。
- `soft-uart-rx`: P06 GPIO 中断 + Timer2 位采样的软件 UART 接收。
- `business-logic-layer`: 面向业务开发的全局状态 `g_app` 和主循环任务调度接口。

### Modified Capabilities

- None.

## Impact

- 影响 Keil C51 工程 `WY8S8002XX.uvproj` 的编译文件列表。
- 影响 `Source_Code/main.c`、`Source_Code/tm1622.h`。
- 新增 `board_config.*`、`adc_sample.*`、`soft_uart_rx.*`、`app_logic.*`。
- 硬件资源所有权固定为：`P00/P01` UART0，`P02-P05` ADC，`P06` 软件 UART RX，`P10-P12` TM1622，`P13` 背光。
- 验证依赖 Keil C51 命令行构建和后续板级示波器/逻辑分析仪检查。
