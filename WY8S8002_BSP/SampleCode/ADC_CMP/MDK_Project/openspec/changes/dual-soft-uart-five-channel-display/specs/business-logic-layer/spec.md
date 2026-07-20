## MODIFIED Requirements

### Requirement: Business state is centralized
The system SHALL provide a global business state object for five measurement records, five display channels, backlight state, and software UART health state.

#### Scenario: Business state is initialized
- **WHEN** `App_Init()` runs
- **THEN** it clears measurements, display records and UART health state, and enables the default backlight state.

### Requirement: Main loop runs modular tasks
The system SHALL run ADC sampling, dual software UART processing, telemetry processing, key processing and business logic from the main loop.

#### Scenario: Main loop iteration
- **WHEN** the firmware enters the main loop
- **THEN** it repeatedly executes the declared driver and business tasks without blocking on a UART frame.

### Requirement: Business logic updates display from sampled values
The system SHALL translate the five centralized measurement records into TM1622 display records before periodic refresh.

#### Scenario: Display task refreshes periodically
- **WHEN** `App_Task()` runs repeatedly
- **THEN** it updates display records in C1, C2, C3, C4, wired order and periodically calls `TM1622_UpdateAll()`.
