/**
 * @file      main.c
 * @brief     Main function of the project
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "adc.h"
#include "adc_cmp.h"
#include "common.h"
#include "delay.h"

/**
 * ADC test mode enumeration
 */
typedef enum {
    TEST_ADC_CMP = 0, /*!< Comparison mode */
    TEST_ADC_FB,      /*!< PWM brake generation from comparison mode */
} ADC_Test_Mode_e;

/**
 * This routine implements tests for ADC comparison mode and PWM brake generation from comparison mode.
 *
 * ADC comparison mode test:
 * --------------------------------------------------------------------------------------------
 * Configure P16 as AIN0   \n
 * P11 as output IO, in the interrupt, assign the comparison output result (ADCMPO) to P11 to detect the comparison
 * result.   \n
 * Compare the voltage at pin P16 with the voltage set in the ADC comparison registers {ADCMPH[7:0]
 * ADCMPL[3:0]}   \n
 * In this routine, the comparison voltage is set to 2V when the MCU is powered at 3.3V. If the voltage at pin P16 is
 * the value configured in the ADC comparison registers, then P11 outputs a high level; if greater, P11 outputs a low
 * level.
 *
 * ADC comparison mode generating PWM brake test:
 * --------------------------------------------------------------------------------------------
 * In this routine, P15 outputs a PWM signal (period: 1ms, duty cycle 50%). When the voltage at pin P16 is < the value
 * configured in the ADC comparison registers, PWM braking occurs.
 */
int main(void)
{
    ADC_Test_Mode_e e_ADCTestMode = TEST_ADC_FB;

    System_ConfigCLK(SYSCLK_HRC, CLK_DIV_2, WAITS_INST_VDD_LT3600MV_CLK_GE15_LT20M);
    switch(e_ADCTestMode)
    {
        case TEST_ADC_CMP: /* Comparison mode */
            ADC_ConfigCMPInit();
            while(1)
            {
                ADC_StartSWCVT(); /* Start software conversion, the result is obtained within the interrupt */
            }
            break;
        case TEST_ADC_FB: /* PWM brake generation from comparison mode */
            ADC_ConfigCMPFBInit();
            while(1)
            {
                ADC_StartSWCVT(); /* Start software conversion, the result is obtained within the interrupt */
            }
            break;
        default:
            break;
    }
    return 0;
}
