#include "app_logic.h"

#include "board_config.h"
#include "key_input.h"
#include "soft_uart_rx.h"
#include "telemetry_protocol.h"

#define APP_DISPLAY_PERIOD_MS    (100U)
#define APP_DISPLAY_MAX_VALUE    (65535UL)

App_State_t xdata g_app;

void App_Init(void)
{
    uint8_t i;

    g_app.backlight_on = 1;
    TelemetryProtocol_Init();

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

    for(i = 0; i < APP_MEASUREMENT_COUNT; i++)
    {
        g_app.measurement[i].voltage_mv = 0;
        g_app.measurement[i].current_ma = 0;
        g_app.measurement[i].power_mw = 0;
        g_app.measurement[i].connected = 0;
    }

    TM1622_Clear();
}

void App_Task(void)
{
    uint8_t i;
    uint16_t now;
    static uint16_t last_display_ms;
    Telemetry_Measurement_t telemetry_measurement;

    for(i = 0; i < ADC_SAMPLE_CHANNEL_COUNT; i++)
    {
        g_app.adc_raw[i] = AdcSample_GetRaw(i);
        g_app.adc_mv[i] = AdcSample_GetMv(i);
    }

    for(i = 0; i < TELEMETRY_CHANNEL_COUNT; i++)
    {
        TelemetryProtocol_GetMeasurement(i, &telemetry_measurement);
        g_app.measurement[i].voltage_mv = telemetry_measurement.voltage_mv;
        g_app.measurement[i].current_ma = telemetry_measurement.current_ma;
        g_app.measurement[i].connected = telemetry_measurement.connected;
    }

    g_app.measurement[4].voltage_mv = AdcSample_GetMv(1U);
    g_app.measurement[4].current_ma = AdcSample_GetMv(3U);
    g_app.measurement[4].connected = 1;

    for(i = 0; i < APP_MEASUREMENT_COUNT; i++)
    {
        g_app.measurement[i].power_mw = ((uint32_t)g_app.measurement[i].voltage_mv
                                         * g_app.measurement[i].current_ma) / 1000UL;
        g_app.display_ch[i].cur = g_app.measurement[i].current_ma / 100U;
        g_app.display_ch[i].vol = g_app.measurement[i].voltage_mv / 100U;
        if((g_app.measurement[i].power_mw / 100UL) > APP_DISPLAY_MAX_VALUE)
        {
            g_app.display_ch[i].powr = (uint16_t)APP_DISPLAY_MAX_VALUE;
        }
        else
        {
            g_app.display_ch[i].powr = (uint16_t)(g_app.measurement[i].power_mw / 100UL);
        }
        g_app.display_ch[i].active = g_app.measurement[i].connected;
    }

    SoftUartRx_GetHealth(&g_app.soft_uart_health);
    TelemetryProtocol_GetHealth(&g_app.telemetry_health);

    if(KeyInput_GetPressEvent() != 0)
    {
        g_app.backlight_on = (g_app.backlight_on == 0) ? 1 : 0;
    }
    Board_BacklightSet(g_app.backlight_on);

    now = KeyInput_GetMilliseconds();
    if((uint16_t)(now - last_display_ms) >= APP_DISPLAY_PERIOD_MS)
    {
        last_display_ms = now;
        TM1622_UpdateAll(g_app.display_ch);
    }
}
