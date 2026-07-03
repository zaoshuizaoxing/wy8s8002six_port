# soft-uart-rx Specification

## Purpose
TBD - created by archiving change modular-adc-tm1622-business-layer. Update Purpose after archive.
## Requirements
### Requirement: P06 software UART uses GPIO interrupt
The system SHALL use `P06` GPIO falling-edge interrupt to detect software UART receive start bits.

#### Scenario: Start bit edge is detected
- **WHEN** `P06` produces a falling edge while the receiver is idle
- **THEN** the GPIO interrupt starts the software UART receive state machine.

### Requirement: Timer2 samples software UART bits
The system SHALL use Timer2 to sample the start bit, eight data bits, and stop bit after start detection.

#### Scenario: Valid byte is received
- **WHEN** a valid 8N1 UART frame arrives on `P06`
- **THEN** Timer2 samples the bits and stores the received byte in the software UART receive buffer.

### Requirement: Software UART exposes nonblocking read API
The system SHALL expose nonblocking availability and byte-read functions for received software UART data.

#### Scenario: Business reads received byte
- **WHEN** `SoftUartRx_Available()` reports data available
- **THEN** `SoftUartRx_ReadByte()` returns the next buffered byte.

### Requirement: INT0 and INT1 mux are not used for P06
The system SHALL NOT configure P06 as INT0 or INT1 because the WY8S8002A pin mux table reserves those mux values.

#### Scenario: P06 receiver initialization
- **WHEN** `SoftUartRx_Init()` runs
- **THEN** it configures `PIO06CFG` as GPIO mode rather than INT0 or INT1 mode.

