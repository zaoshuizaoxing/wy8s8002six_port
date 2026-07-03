## Context

工程目标芯片为 WY8S8002A，工具链为 Keil C51/PK51，代码运行模型是 8051 裸机循环 + 中断。现有 ADC_CMP 示例工程最初用于 ADC 比较和 PWM 刹车演示，不适合作为后续业务层直接开发的结构。

芯片手册确认：`P02/P03/P04/P05` 分别为 `AIN7/AIN6/AIN5/AIN4`；`P00/P01` 可配置为 UART0；`P06` 支持 GPIO 中断，但管脚复用表中 23/24 为保留值，因此不能按 INT0/INT1 复用实现；`P10/P11/P12` 可作为普通 GPIO 驱动 TM1622 三线写入；`P13` 可作为背光控制输出。

## Manual References

模块开发必须优先参考本 change 随附的 Markdown 手册：

- `manuals/wy8s8002a-datasheet.md`：WY8S8002A 主控芯片手册，用于确认引脚复用、GPIO 中断、UART0、Timer2、ADC 通道映射、时钟和电气约束。
- `manuals/tm1622-datasheet.md`：TM1622 LCD 驱动芯片手册，用于确认 `CS/RD/WR/DATA` 接口、命令模式 `100`、写数据模式 `101`、时序和显示 RAM。
- `manuals/README.md`：模块到手册的引用映射。

当代码、规格或业务逻辑涉及硬件资源、寄存器、时序、管脚复用、电气能力或显示协议时，开发者必须先核对上述 Markdown 手册；如果 Markdown 表格抽取不清晰，再回查原始 PDF。

## Goals / Non-Goals

**Goals:**

- 将硬件资源配置、ADC 采样、TM1622 显示、软件 UART 接收和业务状态分层封装。
- 保留一个面向业务逻辑的全局状态 `g_app`，业务开发不直接操作寄存器。
- 保持 Keil C51 可编译，避免旧示例代码占用新业务引脚或中断资源。
- 使用静态存储，避免动态内存和复杂运行时依赖。

**Non-Goals:**

- 不实现完整通信协议解析，只提供软件 UART 接收字节缓冲。
- 不重新设计 TM1622 段码映射表，只移植平台 IO 层并保留现有显示填充逻辑。
- 不删除旧 `adc_cmp.c` 示例源文件，只从当前 Keil 编译列表移除。
- 不在规格中承诺板级模拟量校准精度；毫伏换算按默认 `BOARD_ADC_REF_MV` 完成。

## Decisions

- **板级资源集中在 `board_config`。**  
  这样业务层只调用 `Board_Init()`，不会散落配置 `PIOxxCFG`、UART、背光和外设初始化。替代方案是继续在 `main.c` 中直接初始化各外设，但会让业务代码和硬件细节耦合。

- **ADC 采样独立为 `adc_sample`。**  
  模块内部固定当前硬件通道顺序 `AIN7/AIN6/AIN5/AIN4`，对外只暴露 raw/mV 获取接口。替代方案是业务层直接调用 `ADC_ConfigChannel()`，但容易把 `P02-P05` 误写成 `AIN0-AIN3`。

- **TM1622 保留原公共显示 API，仅替换平台层。**  
  当前屏段映射已经在 `tm1622.c` 中固化，最小风险路径是把旧 `HC89F0431` 端口依赖替换为 `WY8S8002xx.h`、`P10/P11/P12` 和 GPIO 库。

- **P06 软件 UART 使用 GPIO 中断 + Timer2。**  
  手册表 4-2 中 PIO 复用 23/24 为保留值，不可按 INT0/INT1 设计。GPIO ISR 只启动接收状态机，Timer2 ISR 完成半位/整位采样，接收字节放入环形缓冲。

- **业务层使用 `g_app` 汇聚状态。**  
  业务层可通过 `g_app.adc_raw[]`、`g_app.adc_mv[]`、`g_app.display_ch[]`、`g_app.backlight_on` 等字段扩展逻辑，同时驱动层仍保持封装。

- **旧 `adc_cmp.c` 不参与当前构建。**  
  该文件包含 ADC 中断向量和 P11 测试输出，继续编译会与新 TM1622 `P11=WR` 语义冲突，也可能占用 ADC_VECTOR。

## Risks / Trade-offs

- **[Risk] Timer2 被软件 UART 独占。** → 后续新增功能如需 Timer2，必须先调整资源所有权或改用其他定时器。
- **[Risk] 软件 UART 对中断延迟敏感。** → 需要用逻辑分析仪验证 P06 波形、Timer2 采样点和目标波特率容差。
- **[Risk] ADC 毫伏换算默认使用 3300mV。** → 如果实际 AVDD 不是 3.3V，需要改 `BOARD_ADC_REF_MV` 或引入校准。
- **[Risk] TM1622 显示段码映射依赖现有屏线。** → 换屏或改线时必须修改 `tm1622.c` 的字模和映射表。
- **[Risk] Keil 构建会改动 Listings/Objects。** → 规格和代码评审时应聚焦源文件、工程文件和构建日志，构建产物可单独处理。

## Migration Plan

1. 保留原 ADC_CMP 示例源文件，新增业务化模块。
2. 将 `main.c` 切换到 `Board_Init()`、`App_Init()` 和任务循环。
3. 将新模块加入 Keil 工程，将旧 `adc_cmp.c` 从当前编译列表移除。
4. 执行 Keil 命令行构建，要求 `0 Error(s), 0 Warning(s)`。
5. 板级验证顺序：背光 P13、TM1622 清屏/刷新、P02-P05 ADC 数据、UART0 收发、P06 软件 UART 接收。

## Open Questions

- P06 软件 UART 的目标波特率是否固定为 9600，还是需要业务配置。
- TM1622 每路显示字段中 `cur/vol/powr` 与实际业务量纲的最终换算关系是否需要标定。
