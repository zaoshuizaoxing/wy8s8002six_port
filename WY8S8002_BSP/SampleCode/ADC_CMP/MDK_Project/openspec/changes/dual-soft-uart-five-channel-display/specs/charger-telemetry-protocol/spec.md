## ADDED Requirements

### Requirement: Each UART stream parses fixed telemetry frames
The system SHALL parse an 11-byte frame starting with `0xA5`, ending with `0x5A`, and containing a connection byte followed by two big-endian voltage/current pairs.

#### Scenario: A complete C1/C2 frame is received
- **WHEN** P01 supplies a valid 11-byte frame
- **THEN** the parser publishes C1 and C2 voltage values in mV and current values in mA.

### Requirement: C3 and C4 use the second software UART stream
The system SHALL apply the same frame format to P06 and publish its two values as C3 and C4.

#### Scenario: A complete C3/C4 frame is received
- **WHEN** P06 supplies a valid 11-byte frame
- **THEN** the parser publishes C3 and C4 voltage values in mV and current values in mA.

### Requirement: Connection flags control active state
The system SHALL accept only connection values 1, 2, or 3 and use bit 0 and bit 1 to indicate the first and second port in the corresponding pair.

#### Scenario: A frame reports only its second port connected
- **WHEN** a valid frame has connection byte `2`
- **THEN** its first channel is inactive and its second channel is active.

### Requirement: Invalid frame data resynchronizes safely
The system SHALL not update published values for a frame with an invalid tail or connection byte and SHALL resume searching for the next `0xA5` header.

#### Scenario: A malformed frame arrives
- **WHEN** the parser reaches byte 11 without a valid tail or connection value
- **THEN** the previously published measurements remain unchanged and parsing resumes.
