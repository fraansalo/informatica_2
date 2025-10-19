#include "gpio_setting.h"
#include "avr_Gpio.h"
#include "config.h"


void gpio_init(void) {
    buttons_init();
    outputs_init();
}

void buttons_init(void){
    GpioInitStructure_AVR mi_gpio;

    mi_gpio.modo = avr_GPIO_mode_Input;
    mi_gpio.port = avr_GPIO_D;
    mi_gpio.pines = avr_GPIO_PIN_2 | avr_GPIO_PIN_3 | avr_GPIO_PIN_4 | avr_GPIO_PIN_5;

    init_gpio(mi_gpio);
    
}

Button_t buttons_getter(void){
    
}

void outputs_init(void){
    GpioInitStructure_AVR mi_gpio;
    mi_gpio.modo = avr_GPIO_mode_Output;
    mi_gpio.port = avr_GPIO_B;
    mi_gpio.pines = avr_GPIO_PIN_0 | avr_GPIO_PIN_1;
    init_gpio(mi_gpio);
};
