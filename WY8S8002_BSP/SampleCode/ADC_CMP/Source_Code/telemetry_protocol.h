#ifndef __TELEMETRY_PROTOCOL_H__
#define __TELEMETRY_PROTOCOL_H__

#include "common.h"

#define TELEMETRY_CHANNEL_COUNT    (4U)

typedef struct {
    uint16_t voltage_mv;
    uint16_t current_ma;
    uint8_t connected;
} Telemetry_Measurement_t;

typedef struct {
    uint16_t invalid_frame_count[2];
} Telemetry_Health_t;

void TelemetryProtocol_Init(void);
void TelemetryProtocol_Task(void);
uint8_t TelemetryProtocol_GetMeasurement(uint8_t channel, Telemetry_Measurement_t *measurement);
void TelemetryProtocol_GetHealth(Telemetry_Health_t *health);

#endif /* __TELEMETRY_PROTOCOL_H__ */
