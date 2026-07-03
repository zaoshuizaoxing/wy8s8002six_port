# tm1622-display Specification

## Purpose
TBD - created by archiving change modular-adc-tm1622-business-layer. Update Purpose after archive.
## Requirements
### Requirement: TM1622 uses WY8S8002A three-wire GPIO interface
The system SHALL drive TM1622 using `P10` as `CS`, `P11` as `WR`, and `P12` as `DATA`.

#### Scenario: TM1622 GPIO initialization
- **WHEN** `init_tm1622()` runs
- **THEN** `P10`, `P11`, and `P12` are configured as GPIO outputs and set to a safe idle state before commands are written.

### Requirement: TM1622 command mode is supported
The system SHALL support TM1622 command mode using type code `100`.

#### Scenario: TM1622 command write
- **WHEN** `write_cmd_100()` is called with a command byte
- **THEN** the driver sends type code `100`, shifts the command MSB first, and returns `CS` high at the end of the transaction.

### Requirement: TM1622 data write mode is supported
The system SHALL support TM1622 write mode using type code `101` with a 6-bit address and 4-bit data.

#### Scenario: TM1622 data write
- **WHEN** `write_101()` is called with an address and nibble data
- **THEN** the driver sends type code `101`, shifts address bits and data bits according to TM1622 timing, and ends the transaction.

### Requirement: Business display update uses five channel records
The system SHALL refresh display content from `TM1622_Channel_t` records without exposing TM1622 register writes to business logic.

#### Scenario: Business display refresh
- **WHEN** `TM1622_UpdateAll()` receives five channel records
- **THEN** it updates the internal display buffer and writes the full buffer to TM1622.

