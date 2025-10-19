#ifndef GPIO_SETTING
#define GPIO_SETTING
#include "avr_Gpio.h"
#include "menus.h"

void gpio_init(void);
void buttons_init(void);
void outputs_init(void);

Button_t buttons_getter(void);
void heater_setter(bool on);
void leds_setter(bool on);

#endif