#include "key_input.h"

#include "gpio.h"
#include "timer.h"

#define KEY_DEBOUNCE_MS        (20U)
#define KEY_TIMER3_DIV          (TIMER3_DIV_2)
#define KEY_TIMER3_DIV_VALUE    (2UL)
#define KEY_TIMER3_PERIOD_MS    (1UL)

static volatile uint16_t s_milliseconds;
static volatile uint8_t s_debounce_ms;
static volatile uint8_t s_debounce_ready;
static uint8_t s_press_event;

void KeyInput_Init(void)
{
    uint32_t timer_ticks;
    uint16_t reload_value;

    PORT_SET_MUX(PIO17CFG, GPIO_MUX_MODE);
    GPIO1_ConfigInput(GPIO_PIN_7, GPIO_PULLUP);
    GPIO1_ConfigINT(GPIO_PIN_7, GPIO_INT_FALLING);
    CLR_GPIO1_FLAG(GPIO_PIN_7);

    timer_ticks = (g_u32SystemClock / KEY_TIMER3_DIV_VALUE) / (1000UL / KEY_TIMER3_PERIOD_MS);
    reload_value = (uint16_t)(65536UL - timer_ticks);
    DISABLE_TIMER3;
    TIMER3_T3CON_DIV_SET(KEY_TIMER3_DIV);
    TIMER3_DATA_REG((reload_value >> 8) & 0xFF, reload_value & 0xFF);
    T3CON &= ~(1 << 7);
    ENABLE_TIME3_INT;
    ENABLE_TIMER3;
    ENABLE_GPIO_INT;
    ENABLE_ALL_INT;

    s_milliseconds = 0;
    s_debounce_ms = 0;
    s_debounce_ready = 0;
    s_press_event = 0;
}

void KeyInput_OnFallingEdge(void)
{
    if(s_debounce_ms == 0)
    {
        s_debounce_ms = KEY_DEBOUNCE_MS;
        s_debounce_ready = 0;
    }
}

void KeyInput_Task(void)
{
    if(s_debounce_ready != 0)
    {
        s_debounce_ready = 0;
        if(P17 == 0)
        {
            s_press_event = 1;
        }
    }
}

uint8_t KeyInput_GetPressEvent(void)
{
    uint8_t event;

    event = s_press_event;
    s_press_event = 0;
    return event;
}

uint16_t KeyInput_GetMilliseconds(void)
{
    uint8_t interrupt_enabled;
    uint16_t milliseconds;

    interrupt_enabled = EA;
    DISABLE_ALL_INT;
    milliseconds = s_milliseconds;
    EA = interrupt_enabled;
    return milliseconds;
}

static void _TIMER3_IRQHandler(void) interrupt TIMER3_VECTOR
{
    s_milliseconds++;
    if(s_debounce_ms != 0)
    {
        s_debounce_ms--;
        if(s_debounce_ms == 0)
        {
            s_debounce_ready = 1;
        }
    }
}
