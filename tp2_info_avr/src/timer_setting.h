#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

#include <stdint.h>
#include <stdbool.h>


void timer_init(void);
bool timer_tick(void);
bool timer_seconds(void);


#endif