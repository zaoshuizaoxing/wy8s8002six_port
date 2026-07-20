## ADDED Requirements

### Requirement: P17 toggles backlight after debounce
The system SHALL configure P17 as a pull-up GPIO falling-edge input and toggle the P13 backlight state once after a 20 ms debounce interval for each valid press.

#### Scenario: A valid key press occurs
- **WHEN** P17 falls and remains low through the debounce interval
- **THEN** the business backlight state toggles and the board drives P13 to the corresponding level.

#### Scenario: Key bounce occurs
- **WHEN** P17 produces multiple edges within one debounce interval
- **THEN** the system performs at most one backlight toggle.
