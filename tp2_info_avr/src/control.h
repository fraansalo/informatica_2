#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>
#include <stdbool.h>

void control_setTarget(int16_t temp, int16_t h);
int16_t control_getTargetTemp(void);

void control_setCurrentTemp(int16_t temp);
int16_t control_getCurrentTemp(void);

void control_update();
bool control_isHeating(void);
void control_reset(void);

#endif
