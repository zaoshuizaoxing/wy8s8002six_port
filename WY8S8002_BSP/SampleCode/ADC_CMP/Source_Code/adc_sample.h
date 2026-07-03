#ifndef __ADC_SAMPLE_H__
#define __ADC_SAMPLE_H__

#include "common.h"

#define ADC_SAMPLE_CHANNEL_COUNT    (4U)

void     AdcSample_Init(void);
void     AdcSample_Task(void);
uint16_t AdcSample_GetRaw(uint8_t index);
uint16_t AdcSample_GetMv(uint8_t index);

#endif /* __ADC_SAMPLE_H__ */
