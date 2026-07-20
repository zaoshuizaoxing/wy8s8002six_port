/**
 * @file      main.c
 * @brief     Main function of the project
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */
#include "adc_sample.h"
#include "app_logic.h"
#include "board_config.h"
#include "common.h"
#include "key_input.h"
#include "soft_uart_rx.h"
#include "telemetry_protocol.h"

int main(void)
{
    Board_Init();
    App_Init();
    while(1)
    {
        AdcSample_Task();
        SoftUartRx_Task();
        TelemetryProtocol_Task();
        KeyInput_Task();
        App_Task();
    }
}
