#ifndef __SOFT_UART_RX_H__
#define __SOFT_UART_RX_H__

#include "common.h"

void    SoftUartRx_Init(uint32_t baud);
void    SoftUartRx_Task(void);
uint8_t SoftUartRx_Available(void);
uint8_t SoftUartRx_ReadByte(void);

#endif /* __SOFT_UART_RX_H__ */
