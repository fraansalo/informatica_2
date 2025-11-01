#ifndef GPIO_SETTING_H
#define GPIO_SETTING_H
#include "avr_Gpio.h"
#include "menus.h"

#define BTN_UP_PORT    avr_GPIOD_OUT
#define BTN_UP_PIN     avr_GPIO_PIN_2

#define BTN_DOWN_PORT  avr_GPIOD_OUT
#define BTN_DOWN_PIN   avr_GPIO_PIN_3

#define BTN_ENTER_PORT avr_GPIOD_OUT
#define BTN_ENTER_PIN  avr_GPIO_PIN_4

#define BTN_SELECT_PORT avr_GPIOD_OUT
#define BTN_SELECT_PIN  avr_GPIO_PIN_5

#define HEATER_PORT    avr_GPIOB_OUT
#define HEATER_PIN     avr_GPIO_PIN_0

#define LED_PORT       avr_GPIOB_OUT
#define LED_PIN        avr_GPIO_PIN_1


void system_init(void);
void buttons_init(void);
void outputs_init(void);

Button_t buttons_polling(void);
void heater_setter(bool on);
void leds_setter(bool on);

#endif