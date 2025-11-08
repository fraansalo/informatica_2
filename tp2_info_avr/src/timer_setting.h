#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

#include "menus.h"
#include <avr/interrupt.h>
#include "avr_Timers.h"
#include "gpio_setting.h"



void timer_init(void);
bool timer_tick(void);
bool timer_seconds(void);


#endif