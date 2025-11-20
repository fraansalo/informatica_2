#ifndef GPIO_SETTING_H
#define GPIO_SETTING_H
#include "avr_Gpio.h"
#include <stdbool.h>

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

#define LED1_PORT       avr_GPIOB_OUT
#define LED1_PIN        avr_GPIO_PIN_2

#define LED2_PORT       avr_GPIOB_OUT
#define LED2_PIN        avr_GPIO_PIN_3

#define LED3_PORT       avr_GPIOB_OUT
#define LED3_PIN        avr_GPIO_PIN_4


void buttons_init(void);
void outputs_init(void);

void buttons_polling(void);
void heater_setter(bool on);
void leds_setter(bool on);
void leds1_setter(bool on);
void leds2_setter(bool on);
void leds3_setter(bool on);


#endif