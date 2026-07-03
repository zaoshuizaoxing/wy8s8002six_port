# Manual References

These Markdown files are extracted from the vendor PDFs located at `C:\Users\ThinkPadX390\Desktop\wy8s8002six_port` and are attached to this OpenSpec change for development traceability.

## Files

- `wy8s8002a-datasheet.md`: reference for WY8S8002A pin mux, GPIO interrupt support, UART0, Timer2, ADC channel mapping, clock, and electrical constraints.
- `tm1622-datasheet.md`: reference for TM1622 CS/RD/WR/DATA interface, command mode `100`, write mode `101`, timing, and display RAM behavior.

## Module Reference Map

- `board_config.*` MUST reference `wy8s8002a-datasheet.md` for pin mux and system resource ownership.
- `adc_sample.*` MUST reference `wy8s8002a-datasheet.md` for `P02/P03/P04/P05 = AIN7/AIN6/AIN5/AIN4` and ADC timing.
- `soft_uart_rx.*` MUST reference `wy8s8002a-datasheet.md` for GPIO interrupt support and Timer2 behavior. P06 MUST remain GPIO interrupt based; INT0/INT1 mux values are reserved on this chip.
- `tm1622.*` MUST reference `tm1622-datasheet.md` for command/data frame formats and bus timing, and `wy8s8002a-datasheet.md` for MCU GPIO electrical capability.
- `app_logic.*` SHOULD reference the OpenSpec specs first, then the manual files when business logic changes require hardware assumptions.
