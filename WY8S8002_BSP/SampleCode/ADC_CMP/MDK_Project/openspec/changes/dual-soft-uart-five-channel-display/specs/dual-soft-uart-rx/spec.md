## ADDED Requirements

### Requirement: P01 and P06 receive 115200 8N1 software UART data
The system SHALL configure P01 and P06 as pull-up GPIO falling-edge interrupt inputs and receive 115200 baud, 8N1 frames without configuring hardware UART0.

#### Scenario: A start bit arrives on an idle port
- **WHEN** P01 or P06 falls while no software frame is active
- **THEN** the receiver locks that port and starts its frame sampling state machine.

### Requirement: Timer2 uses automatic reload for data-bit sampling
The system SHALL confirm the start bit at its half-bit center and use Timer2 automatic reload at one-bit intervals to sample eight data bits and one stop bit.

#### Scenario: A valid 8N1 frame arrives
- **WHEN** the locked input remains low at start-bit confirmation and high at stop-bit confirmation
- **THEN** the received byte is appended to that port's receive buffer.

### Requirement: Overlapping port start requests are observable
The system SHALL reject a P01 or P06 start request received while the other port frame is active and increment a busy-drop counter.

#### Scenario: A second port starts during a frame
- **WHEN** the non-active port produces a falling edge before the active frame finishes
- **THEN** the active frame continues unchanged and the busy-drop counter increases.
