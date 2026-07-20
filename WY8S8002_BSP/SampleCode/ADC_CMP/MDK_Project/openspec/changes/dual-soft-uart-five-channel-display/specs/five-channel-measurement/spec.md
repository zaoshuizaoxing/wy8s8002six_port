## ADDED Requirements

### Requirement: Business state exposes five measurements
The system SHALL expose C1, C2, C3, C4 and wired measurement records through the global business state, each containing voltage mV, current mA, power mW and connected state.

#### Scenario: Application initializes
- **WHEN** `App_Init()` runs
- **THEN** all five measurement records are cleared and marked inactive.

### Requirement: Wired measurement uses P03 and P05
The system SHALL use P03 AIN6 millivolts for wired voltage and P05 AIN4 millivolts as wired current in mA.

#### Scenario: ADC values update
- **WHEN** the application refreshes its measurement state
- **THEN** the wired record reflects the latest P03 and P05 converted values.

### Requirement: Power is calculated in milliwatts
The system SHALL calculate every active-channel power as `voltage_mv * current_ma / 1000` using a 32-bit intermediate result.

#### Scenario: A measurement is refreshed
- **WHEN** an active record has voltage and current values
- **THEN** its power value equals their millivolt-milliampere product divided by 1000.

### Requirement: Five measurements map to five display channels
The system SHALL map C1, C2, C3, C4 and wired records in that order to TM1622 display channels 0, 1, 2, 3 and 4.

#### Scenario: A disconnected channel is displayed
- **WHEN** a measurement record is inactive
- **THEN** its TM1622 channel is passed with `active` cleared.
