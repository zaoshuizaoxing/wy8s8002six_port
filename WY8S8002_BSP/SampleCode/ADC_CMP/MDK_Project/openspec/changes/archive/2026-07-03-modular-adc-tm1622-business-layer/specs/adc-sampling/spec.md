## ADDED Requirements

### Requirement: ADC samples four fixed input pins
The system SHALL sample four ADC input pins using the WY8S8002A mapping `P02=AIN7`, `P03=AIN6`, `P04=AIN5`, and `P05=AIN4`.

#### Scenario: ADC channel order is initialized
- **WHEN** `AdcSample_Init()` runs
- **THEN** the ADC module prepares the four channels in the order AIN7, AIN6, AIN5, AIN4.

### Requirement: ADC task updates raw and millivolt values
The system SHALL provide raw 12-bit ADC values and millivolt-converted values through accessor functions.

#### Scenario: ADC task completes one conversion
- **WHEN** `AdcSample_Task()` runs
- **THEN** one configured channel is sampled and its raw and millivolt cached values are updated.

### Requirement: Invalid ADC index returns zero
The system SHALL return zero when business code requests an ADC index outside the configured channel count.

#### Scenario: Out-of-range ADC read
- **WHEN** `AdcSample_GetRaw()` or `AdcSample_GetMv()` is called with an invalid index
- **THEN** the function returns `0`.
