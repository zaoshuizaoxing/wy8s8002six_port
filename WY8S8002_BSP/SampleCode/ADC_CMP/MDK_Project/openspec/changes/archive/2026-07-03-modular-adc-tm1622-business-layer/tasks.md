## 1. Board Resource Layer

- [x] 1.1 Add `board_config` module for system clock, UART0, backlight, TM1622, ADC, and software UART initialization.
- [x] 1.2 Configure UART0 on `P00/P01`.
- [x] 1.3 Configure backlight control on `P13` active high.

## 2. ADC Sampling

- [x] 2.1 Add `adc_sample` module.
- [x] 2.2 Implement four-channel ADC order `AIN7/AIN6/AIN5/AIN4` for `P02/P03/P04/P05`.
- [x] 2.3 Provide raw and millivolt accessor functions.

## 3. TM1622 Display

- [x] 3.1 Replace old HC89F0431 platform dependency in `tm1622.h`.
- [x] 3.2 Configure TM1622 pins as `P10=CS`, `P11=WR`, `P12=DATA`.
- [x] 3.3 Preserve existing TM1622 command, data-write, clear, and five-channel update APIs.

## 4. P06 Software UART Receive

- [x] 4.1 Add `soft_uart_rx` module.
- [x] 4.2 Configure `P06` as GPIO falling-edge interrupt input.
- [x] 4.3 Implement Timer2-based 8N1 bit sampling and receive ring buffer.

## 5. Business Logic Layer

- [x] 5.1 Add `app_logic` module and global `g_app` state.
- [x] 5.2 Update `main.c` to call board init, app init, and task loop.
- [x] 5.3 Map sampled ADC state into display channel records and periodic TM1622 refresh.

## 6. Project Integration and Verification

- [x] 6.1 Add new modules to `WY8S8002XX.uvproj`.
- [x] 6.2 Remove old `adc_cmp.c` from the active Keil compile list.
- [x] 6.3 Build with Keil C51 and verify `0 Error(s), 0 Warning(s)`.
- [x] 6.4 Record WY8S8002A pin-mux lesson in the embedded project skill ledger.
