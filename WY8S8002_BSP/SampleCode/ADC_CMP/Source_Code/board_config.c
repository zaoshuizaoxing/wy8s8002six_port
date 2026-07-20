#include "board_config.h"
#include "adc_sample.h"
#include "gpio.h"
#include "key_input.h"
#include "soft_uart_rx.h"
#include "tm1622.h"

static void Board_ConfigBacklight(void)
{
    PORT_SET_MUX(PIO13CFG, GPIO_MUX_MODE);
    GPIO1_ConfigOutput(GPIO_PIN_3, GPIO_PP, GPIO_PULLUP, CURRENT_00);
    Board_BacklightSet(1);
}

void Board_Init(void)
{
    System_ConfigCLK(SYSCLK_HRC, CLK_DIV_2, WAITS_INST_VDD_LT3600MV_CLK_GE15_LT20M);

    Board_ConfigBacklight();
    init_tm1622();
    AdcSample_Init();
    SoftUartRx_Init(BOARD_SOFT_UART_BAUD);
    KeyInput_Init();
}
void Board_BacklightSet(uint8_t on)
{
    P13 = (on != 0) ? 1 : 0;
}
