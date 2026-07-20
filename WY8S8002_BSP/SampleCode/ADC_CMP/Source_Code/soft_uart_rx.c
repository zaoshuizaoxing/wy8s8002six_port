#include "soft_uart_rx.h"

#include "gpio.h"
#include "key_input.h"
#include "timer.h"

#define SOFT_UART_RX_BUF_SIZE    (16U)
#define SOFT_UART_TIMER_DIV      (TIMER2_T2DIV_1DIV)
#define SOFT_UART_TIMER_DIV_VAL  (1UL)
#define SOFT_UART_STATE_IDLE     (0U)
#define SOFT_UART_STATE_START    (1U)
#define SOFT_UART_STATE_DATA     (2U)
#define SOFT_UART_STATE_STOP     (3U)
#define SOFT_UART_INVALID_PORT   (0xFFU)

static volatile uint8_t s_rx_state;
static volatile uint8_t s_active_port;
static volatile uint8_t s_rx_bit_index;
static volatile uint8_t s_rx_shift;
static volatile uint8_t s_rx_head[SOFT_UART_PORT_COUNT];
static volatile uint8_t s_rx_tail[SOFT_UART_PORT_COUNT];
static volatile uint8_t xdata s_rx_buf[SOFT_UART_PORT_COUNT][SOFT_UART_RX_BUF_SIZE];
static uint16_t s_bit_ticks;
static uint16_t s_half_bit_ticks;
static SoftUartRx_Health_t xdata s_health;

static uint8_t SoftUartRx_ReadPin(uint8_t port)
{
    return (port == SOFT_UART_PORT_C12) ? P01 : P06;
}

static void SoftUartRx_StartTimer(void)
{
    uint16_t reload_value;

    reload_value = 65536U - s_bit_ticks;
    TIMER2_RCMP_DATA_REG((reload_value >> 8) & 0xFF, reload_value & 0xFF);
    reload_value = 65536U - s_half_bit_ticks;
    TIMER2_DATA_REG((reload_value >> 8) & 0xFF, reload_value & 0xFF);
    CLR_TIME2_TF2_FLAG;
    ENABLE_TIMER2;
}

static void SoftUartRx_StopTimer(void)
{
    DISABLE_TIMER2;
    CLR_TIME2_TF2_FLAG;
}

static void SoftUartRx_PushByte(uint8_t port, uint8_t data_value)
{
    uint8_t next_head;

    next_head = s_rx_head[port] + 1;
    if(next_head >= SOFT_UART_RX_BUF_SIZE)
    {
        next_head = 0;
    }

    if(next_head != s_rx_tail[port])
    {
        s_rx_buf[port][s_rx_head[port]] = data_value;
        s_rx_head[port] = next_head;
    }
    else
    {
        s_health.overflow_count[port]++;
    }
}

void SoftUartRx_Init(uint32_t baud)
{
    uint32_t timer_clk;

    if(baud == 0)
    {
        baud = 9600UL;
    }

    timer_clk = g_u32SystemClock / SOFT_UART_TIMER_DIV_VAL;
    s_bit_ticks = (uint16_t)((timer_clk + (baud / 2UL)) / baud);
    if(s_bit_ticks < 4)
    {
        s_bit_ticks = 4;
    }
    s_half_bit_ticks = s_bit_ticks / 2;
    if(s_half_bit_ticks == 0)
    {
        s_half_bit_ticks = 1;
    }

    s_rx_state = SOFT_UART_STATE_IDLE;
    s_rx_bit_index = 0;
    s_rx_shift = 0;
    s_rx_head[SOFT_UART_PORT_C12] = 0;
    s_rx_head[SOFT_UART_PORT_C34] = 0;
    s_rx_tail[SOFT_UART_PORT_C12] = 0;
    s_rx_tail[SOFT_UART_PORT_C34] = 0;
    s_active_port = SOFT_UART_INVALID_PORT;
    s_health.overflow_count[SOFT_UART_PORT_C12] = 0;
    s_health.overflow_count[SOFT_UART_PORT_C34] = 0;
    s_health.stop_error_count[SOFT_UART_PORT_C12] = 0;
    s_health.stop_error_count[SOFT_UART_PORT_C34] = 0;
    s_health.busy_drop_count = 0;

    PORT_SET_MUX(PIO01CFG, GPIO_MUX_MODE);
    PORT_SET_MUX(PIO06CFG, GPIO_MUX_MODE);
    GPIO0_ConfigInput(GPIO_PIN_1, GPIO_PULLUP);
    GPIO0_ConfigInput(GPIO_PIN_6, GPIO_PULLUP);
    GPIO0_ConfigINT(GPIO_PIN_1, GPIO_INT_FALLING);
    GPIO0_ConfigINT(GPIO_PIN_6, GPIO_INT_FALLING);

    DISABLE_TIMER2;
    TIMER2_T2MOD_T2DIV_SET(SOFT_UART_TIMER_DIV);
    TIMER2_SET_RELOAD_MODE;
    ENABLE_TIMER2_RELOAD;
    DISABLE_TIMER2_CMPCR;
    CLR_TIME2_TF2_FLAG;
    ENABLE_TIME2_INT;

    CLR_GPIO0_FLAG(GPIO_PIN_1);
    CLR_GPIO0_FLAG(GPIO_PIN_6);
    ENABLE_GPIO_INT;
    ENABLE_ALL_INT;
}

void SoftUartRx_Task(void)
{
}

uint8_t SoftUartRx_Available(uint8_t port)
{
    if(port >= SOFT_UART_PORT_COUNT)
    {
        return 0;
    }
    return (s_rx_head[port] != s_rx_tail[port]) ? 1 : 0;
}

uint8_t SoftUartRx_ReadByte(uint8_t port)
{
    uint8_t data_value;

    if((port >= SOFT_UART_PORT_COUNT) || (s_rx_head[port] == s_rx_tail[port]))
    {
        return 0;
    }

    data_value = s_rx_buf[port][s_rx_tail[port]];
    s_rx_tail[port]++;
    if(s_rx_tail[port] >= SOFT_UART_RX_BUF_SIZE)
    {
        s_rx_tail[port] = 0;
    }
    return data_value;
}

void SoftUartRx_GetHealth(SoftUartRx_Health_t *health)
{
    if(health != 0)
    {
        *health = s_health;
    }
}

static void _GPIO_IRQHandler(void) interrupt GPIO_VECTOR
{
    if(IS_GPIO0_FLAG(GPIO_PIN_1))
    {
        CLR_GPIO0_FLAG(GPIO_PIN_1);
        if(s_rx_state == SOFT_UART_STATE_IDLE)
        {
            s_active_port = SOFT_UART_PORT_C12;
            s_rx_state = SOFT_UART_STATE_START;
            s_rx_bit_index = 0;
            s_rx_shift = 0;
            SoftUartRx_StartTimer();
        }
        else
        {
            s_health.busy_drop_count++;
        }
    }

    if(IS_GPIO0_FLAG(GPIO_PIN_6))
    {
        CLR_GPIO0_FLAG(GPIO_PIN_6);
        if(s_rx_state == SOFT_UART_STATE_IDLE)
        {
            s_active_port = SOFT_UART_PORT_C34;
            s_rx_state = SOFT_UART_STATE_START;
            s_rx_bit_index = 0;
            s_rx_shift = 0;
            SoftUartRx_StartTimer();
        }
        else
        {
            s_health.busy_drop_count++;
        }
    }

    if(IS_GPIO1_FLAG(GPIO_PIN_7))
    {
        CLR_GPIO1_FLAG(GPIO_PIN_7);
        KeyInput_OnFallingEdge();
    }
}

static void _TIMER2_IRQHandler(void) interrupt TIMER2_VECTOR
{
    if(IS_TIME2_TF2_FLAG)
    {
        CLR_TIME2_TF2_FLAG;

        switch(s_rx_state)
        {
            case SOFT_UART_STATE_START:
                if(SoftUartRx_ReadPin(s_active_port) == 0)
                {
                    s_rx_state = SOFT_UART_STATE_DATA;
                    s_rx_bit_index = 0;
                    s_rx_shift = 0;
                }
                else
                {
                    s_rx_state = SOFT_UART_STATE_IDLE;
                    s_active_port = SOFT_UART_INVALID_PORT;
                    SoftUartRx_StopTimer();
                }
                break;

            case SOFT_UART_STATE_DATA:
                if(SoftUartRx_ReadPin(s_active_port) != 0)
                {
                    s_rx_shift |= (1U << s_rx_bit_index);
                }
                s_rx_bit_index++;
                if(s_rx_bit_index >= 8)
                {
                    s_rx_state = SOFT_UART_STATE_STOP;
                }
                break;

            case SOFT_UART_STATE_STOP:
                if(SoftUartRx_ReadPin(s_active_port) != 0)
                {
                    SoftUartRx_PushByte(s_active_port, s_rx_shift);
                }
                else
                {
                    s_health.stop_error_count[s_active_port]++;
                }
                s_rx_state = SOFT_UART_STATE_IDLE;
                s_active_port = SOFT_UART_INVALID_PORT;
                SoftUartRx_StopTimer();
                break;

            default:
                s_rx_state = SOFT_UART_STATE_IDLE;
                s_active_port = SOFT_UART_INVALID_PORT;
                SoftUartRx_StopTimer();
                break;
        }
    }
}
