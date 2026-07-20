#ifndef __SOFT_UART_RX_H__
#define __SOFT_UART_RX_H__

#include "common.h"

#define SOFT_UART_PORT_C12    (0U)
#define SOFT_UART_PORT_C34    (1U)
#define SOFT_UART_PORT_COUNT  (2U)

typedef struct {
    uint16_t overflow_count[SOFT_UART_PORT_COUNT];
    uint16_t stop_error_count[SOFT_UART_PORT_COUNT];
    uint16_t busy_drop_count;
} SoftUartRx_Health_t;

void    SoftUartRx_Init(uint32_t baud);
void    SoftUartRx_Task(void);
uint8_t SoftUartRx_Available(uint8_t port);
uint8_t SoftUartRx_ReadByte(uint8_t port);
void    SoftUartRx_GetHealth(SoftUartRx_Health_t *health);

#endif /* __SOFT_UART_RX_H__ */
