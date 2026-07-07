#include "adc_sample.h"
#include "adc.h"
#include "board_config.h"
#include "delay.h"
static uint8_t  s_sample_index;
static uint16_t xdata s_adc_raw[ADC_SAMPLE_CHANNEL_COUNT];
static uint16_t xdata s_adc_mv[ADC_SAMPLE_CHANNEL_COUNT];
static const uint8_t code s_adc_channels[ADC_SAMPLE_CHANNEL_COUNT] = {
    ADC_AIN7, /* P02 */
    ADC_AIN6, /* P03 */
    ADC_AIN5, /* P04 */
    ADC_AIN4  /* P05 */
};
void AdcSample_Init(void)
{
    uint8_t i;
    s_sample_index = 0;
    for(i = 0; i < ADC_SAMPLE_CHANNEL_COUNT; i++)
    {
        s_adc_raw[i] = 0;
        s_adc_mv[i] = 0;
        ADC_ConfigChannel(s_adc_channels[i], ADC_DIV_4);
    }
    ADC_SMP_SEL(ADC_CLKP_8);
    ADC_ConfigSWCVT();
    ENABLE_ADC;
    Timer0_Delay_ms(1);
}
void AdcSample_Task(void)
{
    uint16_t raw;
    ADC_ConfigChannel(s_adc_channels[s_sample_index], ADC_DIV_4);
    ADC_StartSWCVT();
    raw = ADC_GetResultQueryMode();
    s_adc_raw[s_sample_index] = raw;
    s_adc_mv[s_sample_index] = (uint16_t)(((uint32_t)raw * BOARD_ADC_REF_MV) / 4095UL);

    s_sample_index++;
    if(s_sample_index >= ADC_SAMPLE_CHANNEL_COUNT)
    {
        s_sample_index = 0;
    }
}
uint16_t AdcSample_GetRaw(uint8_t index)
{
    if(index >= ADC_SAMPLE_CHANNEL_COUNT)
    {
        return 0;
    }
    return s_adc_raw[index];
}
uint16_t AdcSample_GetMv(uint8_t index)
{
    if(index >= ADC_SAMPLE_CHANNEL_COUNT)
    {
        return 0;
    }
    return s_adc_mv[index];
}
