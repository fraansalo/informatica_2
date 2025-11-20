#include "menus.h"
#include "config.h"
#include "gpio_setting.h"
#include "avr_Gpio.h"
#include <avr/io.h>

volatile static Button_t last_button = BTN_NONE;
static uint16_t debounce_timer = 0;
static Button_t boton_previo = BTN_NONE;

void buttons_set(Button_t btn){
    last_button = btn;
    leds_setter(false);
    leds1_setter(false);
    leds2_setter(false);
    leds3_setter(false);

    switch(btn){
        case BTN_UP: leds_setter(true); break;
        case BTN_DOWN: leds1_setter(true); break;
        case BTN_ENTER: leds2_setter(true); break;
        case BTN_SELECT: leds3_setter(true); break;
        default: break;
    }
}

Button_t buttons_get(void){
    Button_t btn_temp= last_button; //guarda en variable temporal el ultimo presionado
    last_button = BTN_NONE;         //resetea el ultimo presionado
    return btn_temp;                //devuelve el boton que se presiono
}

//funcion para efectuar el control de los gpios de los botones.
void buttons_polling(void){

    if(last_button != BTN_NONE)return;
    Button_t current = BTN_NONE;
    
    if (!(avr_GPIOD_IN & BTN_UP_PIN))current = BTN_UP;
    if (!(avr_GPIOD_IN & BTN_DOWN_PIN))current = BTN_DOWN;
    if (!(avr_GPIOD_IN & BTN_ENTER_PIN))current = BTN_ENTER;
    if (!(avr_GPIOD_IN & BTN_SELECT_PIN))current = BTN_SELECT;
    
    if(current != boton_previo && debounce_timer == 0){
        boton_previo = current;
        debounce_timer = DEBOUNCE_DELAY_MS;
        if(current != BTN_NONE){
            buttons_set(current);
        }
    }
}