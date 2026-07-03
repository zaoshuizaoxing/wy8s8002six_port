# business-logic-layer Specification

## Purpose
TBD - created by archiving change modular-adc-tm1622-business-layer. Update Purpose after archive.
## Requirements
### Requirement: Business state is centralized
The system SHALL provide a global business state object for ADC values, display channels, backlight state, and software UART receive state.

#### Scenario: Business state is initialized
- **WHEN** `App_Init()` runs
- **THEN** the system clears ADC values, display channel records, software UART flags, and enables the default backlight state.

### Requirement: Main loop runs modular tasks
The system SHALL run ADC sampling, software UART processing, and business logic from the main loop.

#### Scenario: Main loop iteration
- **WHEN** the firmware enters the main loop
- **THEN** it repeatedly calls ADC sampling, software UART task handling, and business logic task handling.

### Requirement: Business logic updates display from sampled values
The system SHALL translate sampled ADC state into display channel records before refreshing TM1622.

#### Scenario: Display task refreshes periodically
- **WHEN** `App_Task()` runs repeatedly
- **THEN** it copies ADC raw and millivolt values into `g_app` and periodically calls `TM1622_UpdateAll()`.

