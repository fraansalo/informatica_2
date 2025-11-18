#include "gpio_setting.h"
#include "avr_Gpio.h"
#include "timer_setting.h"
#include "extint_setting.h"
#include "config.h"
#include "menus.h"
#include <avr/io.h>

void buttons_init(void){
    GpioInitStructure_AVR mi_gpio;
    mi_gpio.modo = avr_GPIO_mode_Input;
    mi_gpio.port = avr_GPIO_D;
    mi_gpio.pines = avr_GPIO_PIN_2 | avr_GPIO_PIN_3 | avr_GPIO_PIN_4 | avr_GPIO_PIN_5;
    init_gpio(mi_gpio);
    set_pin(avr_GPIOD_OUT,BTN_UP_PIN|BTN_DOWN_PIN|BTN_ENTER_PIN|BTN_SELECT_PIN);
}

void outputs_init(void){
    GpioInitStructure_AVR mi_gpio;
    mi_gpio.modo = avr_GPIO_mode_Output;
    mi_gpio.port = avr_GPIO_C;
    mi_gpio.pines = avr_GPIO_PIN_3 | avr_GPIO_PIN_4;
    init_gpio(mi_gpio);
    clear_pin(HEATER_PORT,HEATER_PIN);
};

void heater_setter(bool on){
    if(on){
        set_pin(HEATER_PORT,HEATER_PIN);
    }else clear_pin(HEATER_PORT,HEATER_PIN);
}

void leds_setter(bool on){
    if(on){
        set_pin(LED_PORT,LED_PIN);
    }else clear_pin(LED_PORT,LED_PIN);
}
