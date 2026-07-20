#ifndef __APP_LOGIC_H__
#define __APP_LOGIC_H__

#include "adc_sample.h"
#include "soft_uart_rx.h"
#include "telemetry_protocol.h"
#include "tm1622.h"

#define APP_MEASUREMENT_COUNT    (5U)

typedef struct {
    uint16_t voltage_mv;
    uint16_t current_ma;
    uint32_t power_mw;
    uint8_t connected;
} App_Measurement_t;

typedef struct {
    uint16_t adc_raw[ADC_SAMPLE_CHANNEL_COUNT];
    uint16_t adc_mv[ADC_SAMPLE_CHANNEL_COUNT];
    App_Measurement_t measurement[APP_MEASUREMENT_COUNT];
    TM1622_Channel_t display_ch[TM1622_CH_COUNT];
    uint8_t backlight_on;
    SoftUartRx_Health_t soft_uart_health;
    Telemetry_Health_t telemetry_health;
} App_State_t;

extern App_State_t xdata g_app;

void App_Init(void);
void App_Task(void);

#endif /* __APP_LOGIC_H__ */
