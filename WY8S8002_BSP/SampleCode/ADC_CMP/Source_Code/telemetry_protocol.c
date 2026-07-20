#include "telemetry_protocol.h"

#include "soft_uart_rx.h"

#define TELEMETRY_FRAME_SIZE    (11U)
#define TELEMETRY_FRAME_HEADER  (0xA5U)
#define TELEMETRY_FRAME_TAIL    (0x5AU)

static uint8_t xdata s_frame[SOFT_UART_PORT_COUNT][TELEMETRY_FRAME_SIZE];
static uint8_t s_frame_count[SOFT_UART_PORT_COUNT];
static Telemetry_Measurement_t xdata s_measurement[TELEMETRY_CHANNEL_COUNT];
static Telemetry_Health_t xdata s_health;

static uint16_t TelemetryProtocol_ReadU16(uint8_t xdata *bytes)
{
    return (uint16_t)(((uint16_t)bytes[0] << 8) | bytes[1]);
}

static void TelemetryProtocol_UpdatePair(uint8_t port)
{
    uint8_t base_channel;
    uint8_t connection;
    uint8_t xdata *frame;

    frame = s_frame[port];
    connection = frame[1];
    base_channel = (uint8_t)(port * 2U);

    s_measurement[base_channel].voltage_mv = TelemetryProtocol_ReadU16(&frame[2]);
    s_measurement[base_channel].current_ma = TelemetryProtocol_ReadU16(&frame[4]);
    s_measurement[base_channel].connected = (connection & 0x01U) ? 1 : 0;
    s_measurement[base_channel + 1U].voltage_mv = TelemetryProtocol_ReadU16(&frame[6]);
    s_measurement[base_channel + 1U].current_ma = TelemetryProtocol_ReadU16(&frame[8]);
    s_measurement[base_channel + 1U].connected = (connection & 0x02U) ? 1 : 0;
}

static void TelemetryProtocol_ProcessByte(uint8_t port, uint8_t data_value)
{
    uint8_t count;

    count = s_frame_count[port];
    if(count == 0)
    {
        if(data_value == TELEMETRY_FRAME_HEADER)
        {
            s_frame[port][0] = data_value;
            s_frame_count[port] = 1;
        }
        return;
    }

    s_frame[port][count] = data_value;
    count++;
    if(count < TELEMETRY_FRAME_SIZE)
    {
        s_frame_count[port] = count;
        return;
    }

    if((s_frame[port][10] == TELEMETRY_FRAME_TAIL)
       && (s_frame[port][1] >= 1U) && (s_frame[port][1] <= 3U))
    {
        TelemetryProtocol_UpdatePair(port);
        s_frame_count[port] = 0;
    }
    else
    {
        s_health.invalid_frame_count[port]++;
        s_frame_count[port] = (data_value == TELEMETRY_FRAME_HEADER) ? 1 : 0;
        if(s_frame_count[port] != 0)
        {
            s_frame[port][0] = data_value;
        }
    }
}

void TelemetryProtocol_Init(void)
{
    uint8_t i;

    for(i = 0; i < SOFT_UART_PORT_COUNT; i++)
    {
        s_frame_count[i] = 0;
        s_health.invalid_frame_count[i] = 0;
    }
    for(i = 0; i < TELEMETRY_CHANNEL_COUNT; i++)
    {
        s_measurement[i].voltage_mv = 0;
        s_measurement[i].current_ma = 0;
        s_measurement[i].connected = 0;
    }
}

void TelemetryProtocol_Task(void)
{
    uint8_t port;

    for(port = 0; port < SOFT_UART_PORT_COUNT; port++)
    {
        while(SoftUartRx_Available(port) != 0)
        {
            TelemetryProtocol_ProcessByte(port, SoftUartRx_ReadByte(port));
        }
    }
}

uint8_t TelemetryProtocol_GetMeasurement(uint8_t channel, Telemetry_Measurement_t *measurement)
{
    if((channel >= TELEMETRY_CHANNEL_COUNT) || (measurement == 0))
    {
        return 0;
    }

    *measurement = s_measurement[channel];
    return 1;
}

void TelemetryProtocol_GetHealth(Telemetry_Health_t *health)
{
    if(health != 0)
    {
        *health = s_health;
    }
}
