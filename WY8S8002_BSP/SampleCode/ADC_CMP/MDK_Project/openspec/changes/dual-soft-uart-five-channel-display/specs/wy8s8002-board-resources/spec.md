## MODIFIED Requirements

### Requirement: Board initialization owns fixed hardware resources
The system SHALL initialize WY8S8002A board resources through a dedicated board configuration layer, configuring P01/P06 as software UART RX GPIO inputs, P17 as a backlight-key input, P13 as backlight output, TM1622, four-channel ADC sampling, Timer2 software-UART timing, and Timer3 application timing.

#### Scenario: Board initialization configures required pins
- **WHEN** `Board_Init()` runs
- **THEN** it initializes the declared GPIO, display, ADC and timer resources without configuring hardware UART0.

## REMOVED Requirements

### Requirement: UART0 uses P00 and P01
**Reason**: Hardware UART0 cannot provide the required 115200 baud receive operation.
**Migration**: P01 is configured as a GPIO software UART RX input; no UART0 TX or RX function is provided.
