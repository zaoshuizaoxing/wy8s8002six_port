## 1. OpenSpec and Board Resources

- [x] 1.1 Replace UART0/P01 board ownership with P01/P06/P17 GPIO, Timer2 and Timer3 initialization.
- [x] 1.2 Update the Keil C51 project to remove the active UART0 driver and add required modules.

## 2. Dual Software UART

- [x] 2.1 Replace the single-port 9600 receiver with per-port P01/P06 buffers and nonblocking interfaces.
- [x] 2.2 Implement GPIO start detection, Timer2 half-bit validation and automatic-reload 115200 8N1 sampling.
- [x] 2.3 Record receiver overflow, stop-bit failure and overlapping-start busy-drop health counters.

## 3. Telemetry and Input Modules

- [x] 3.1 Add two-stream 11-byte telemetry parser with validation, resynchronization and C1-C4 publication.
- [x] 3.2 Add Timer3 1 ms tick and P17 active-low key event/debounce module.

## 4. Business and Display Integration

- [x] 4.1 Extend `g_app` with five business measurement records and UART health state.
- [x] 4.2 Integrate protocol and P03/P05 ADC data, calculate mW power, and map five channels to TM1622.
- [x] 4.3 Integrate debounced key events with P13 backlight state.

## 5. Verification

- [x] 5.1 Build with Keil C51 and resolve all compiler warnings/errors.
- [x] 5.2 Run OpenSpec strict validation and targeted resource/interface searches.
- [x] 5.3 Document required board-level UART waveform, packet and backlight verification.
