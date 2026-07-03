#ifndef __APP_LOGIC_H__
#define __APP_LOGIC_H__

#include "adc_sample.h"
#include "tm1622.h"

typedef struct {
    uint16_t adc_raw[ADC_SAMPLE_CHANNEL_COUNT];
    uint16_t adc_mv[ADC_SAMPLE_CHANNEL_COUNT];
    TM1622_Channel_t display_ch[TM1622_CH_COUNT];
    uint8_t backlight_on;
    uint8_t soft_uart_rx_ready;
    uint8_t soft_uart_rx_byte;
} App_State_t;

extern App_State_t xdata g_app;

void App_Init(void);
void App_Task(void);

#endif /* __APP_LOGIC_H__ */
