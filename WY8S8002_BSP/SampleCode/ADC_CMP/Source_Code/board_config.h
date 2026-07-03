#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include "common.h"

#define BOARD_UART0_BAUD        (9600UL)
#define BOARD_SOFT_UART_BAUD    (9600UL)
#define BOARD_ADC_REF_MV        (3300UL)

void Board_Init(void);
void Board_BacklightSet(uint8_t on);

#endif /* __BOARD_CONFIG_H__ */
