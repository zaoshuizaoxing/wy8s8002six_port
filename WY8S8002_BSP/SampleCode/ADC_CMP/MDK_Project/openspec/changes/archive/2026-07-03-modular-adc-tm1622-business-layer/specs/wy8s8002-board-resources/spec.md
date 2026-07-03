## ADDED Requirements

### Requirement: Board initialization owns fixed hardware resources
The system SHALL initialize WY8S8002A board resources through a dedicated board configuration layer.

#### Scenario: Board initialization configures required pins
- **WHEN** `Board_Init()` runs
- **THEN** the system configures `P00/P01` for UART0, `P13` for backlight output, initializes TM1622, initializes four-channel ADC sampling, and initializes P06 software UART receive.

### Requirement: UART0 uses P00 and P01
The system SHALL configure `P00` as UART0 RXD and `P01` as UART0 TXD for hardware UART0.

#### Scenario: UART0 mux is applied
- **WHEN** board initialization configures UART0
- **THEN** `PIO00CFG` is set to UART0 RXD mode and `PIO01CFG` is set to UART0 TXD mode.

### Requirement: Backlight uses P13 active high
The system SHALL control display backlight using `P13` as a GPIO output where high level enables the backlight.

#### Scenario: Backlight is enabled by business state
- **WHEN** the business layer sets backlight state on
- **THEN** the board layer drives `P13` high.
