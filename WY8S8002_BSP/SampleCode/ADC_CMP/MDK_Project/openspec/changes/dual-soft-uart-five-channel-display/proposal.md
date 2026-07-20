## Why

当前硬件 UART0 无法在内部时钟条件下可靠工作于 115200 波特率，且现有固件仅实现 P06 单路 9600 软件接收，不能处理两组 C1-C4 遥测数据。需要将接收、协议解析和显示映射封装为模块，并通过业务全局状态向上层提供五路稳定的电压、电流与功率数据。

## What Changes

- **BREAKING**：停止使用 UART0 和 P01 的 UART RX 复用；P01、P06 改为 115200、8N1 软件接收 GPIO。
- 增加双路软件 UART RX，使用 Timer2 自动重载进行逐位采样；上游两组报文不得重叠。
- 增加两组固定 11 字节遥测帧的校验、重同步与 C1-C4 解析。
- 扩展业务层全局状态，集中提供 C1、C2、C3、C4 和有线五路电压、电流、功率及连接状态。
- 将 P03/P05 ADC 数据作为有线电压/电流，映射到 TM1622 第 4 路；C1-C4 映射到第 0-3 路。
- 增加 P17 低电平按键消抖与 P13 背光开关控制。

## Capabilities

### New Capabilities

- `dual-soft-uart-rx`: P01/P06 双路 115200 软件 UART 接收与资源仲裁。
- `charger-telemetry-protocol`: 两组 11 字节 C1-C4 遥测帧解析与有效数据发布。
- `five-channel-measurement`: 五路业务测量状态、功率计算及 TM1622 映射。
- `backlight-key-control`: P17 按键消抖与 P13 背光切换。

### Modified Capabilities

- `wy8s8002-board-resources`: 移除 UART0 资源所有权，新增 P01/P06/P17 GPIO、Timer2 与 Timer3 资源约束。
- `business-logic-layer`: 全局业务状态和主循环任务改为封装五路测量、协议和背光逻辑。
- `soft-uart-rx`: 单路 P06/Timer2 接收能力替换为双路 P01/P06 115200 自动重载接收能力。

## Impact

- 影响 `board_config`、`soft_uart_rx`、`app_logic`、`main` 和 Keil C51 编译文件列表；新增遥测协议与按键模块。
- 影响 P01、P06、P17、P13、Timer2、Timer3 的硬件资源所有权；P02-P05 ADC 与 P10-P12 TM1622 引脚保持原有用途。
- 业务代码继续通过 `extern App_State_t xdata g_app` 访问状态，不直接访问驱动寄存器或协议缓冲。
