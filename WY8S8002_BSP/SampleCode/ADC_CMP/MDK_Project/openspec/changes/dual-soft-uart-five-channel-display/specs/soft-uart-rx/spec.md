## MODIFIED Requirements

### Requirement: P06 software UART uses GPIO interrupt
The system SHALL use P01 and P06 GPIO falling-edge interrupts to detect software UART receive start bits at 115200 baud.

#### Scenario: Start bit edge is detected
- **WHEN** P01 or P06 produces a falling edge while the receiver is idle
- **THEN** the GPIO interrupt starts the receive state machine for that port.

### Requirement: Timer2 samples software UART bits
The system SHALL use Timer2 automatic reload to sample the start bit, eight data bits, and stop bit for the currently active P01 or P06 frame.

#### Scenario: Valid byte is received
- **WHEN** a valid 115200 8N1 UART frame arrives on P01 or P06
- **THEN** Timer2 stores the byte in the matching port receive buffer.

### Requirement: Software UART exposes nonblocking read API
The system SHALL expose nonblocking availability and byte-read functions for each received software UART port.

#### Scenario: Protocol reads received byte
- **WHEN** a port reports data available
- **THEN** its byte-read function returns the next buffered byte without blocking.

## REMOVED Requirements

### Requirement: INT0 and INT1 mux are not used for P06
**Reason**: The replacement receiver continues to use GPIO interrupts and adds P01; the old P06-only requirement is superseded.
**Migration**: Both P01 and P06 remain in GPIO mux mode and never use INT0 or INT1 mux values.
