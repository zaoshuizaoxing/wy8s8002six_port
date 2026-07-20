#ifndef __KEY_INPUT_H__
#define __KEY_INPUT_H__

#include "common.h"

void KeyInput_Init(void);
void KeyInput_Task(void);
void KeyInput_OnFallingEdge(void);
uint8_t KeyInput_GetPressEvent(void);
uint16_t KeyInput_GetMilliseconds(void);

#endif /* __KEY_INPUT_H__ */
