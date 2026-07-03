#include "app_logic.h"

#include "board_config.h"
#include "soft_uart_rx.h"

App_State_t xdata g_app;

void App_Init(void)
{
    uint8_t i;

    g_app.backlight_on = 1;
    g_app.soft_uart_rx_ready = 0;
    g_app.soft_uart_rx_byte = 0;

    for(i = 0; i < ADC_SAMPLE_CHANNEL_COUNT; i++)
    {
        g_app.adc_raw[i] = 0;
        g_app.adc_mv[i] = 0;
    }

    for(i = 0; i < TM1622_CH_COUNT; i++)
    {
        g_app.display_ch[i].cur = 0;
        g_app.display_ch[i].vol = 0;
        g_app.display_ch[i].powr = 0;
        g_app.display_ch[i].active = 0;
    }

    TM1622_Clear();
}

void App_Task(void)
{
    uint8_t i;
    static uint8_t display_divider;

    for(i = 0; i < ADC_SAMPLE_CHANNEL_COUNT; i++)
    {
        g_app.adc_raw[i] = AdcSample_GetRaw(i);
        g_app.adc_mv[i] = AdcSample_GetMv(i);
        g_app.display_ch[i].cur = g_app.adc_raw[i] / 10;
        g_app.display_ch[i].vol = g_app.adc_mv[i] / 10;
        g_app.display_ch[i].powr = g_app.adc_mv[i] / 10;
        g_app.display_ch[i].active = 1;
    }

    g_app.display_ch[4].active = 0;
    Board_BacklightSet(g_app.backlight_on);

    if(SoftUartRx_Available() != 0)
    {
        g_app.soft_uart_rx_byte = SoftUartRx_ReadByte();
        g_app.soft_uart_rx_ready = 1;
    }

    display_divider++;
    if(display_divider >= 16)
    {
        display_divider = 0;
        TM1622_UpdateAll(g_app.display_ch);
    }
}
