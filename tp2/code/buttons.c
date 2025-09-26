#include <stdio.h>
#include <menus.h>
#include <config.h>

static Button_t last_button = BTN_NONE;

void buttons_set(Button_t btn){
    last_button = btn;
}

Button_t buttons_get(void){
    Button_t btn_temp= last_button; //guarda en variable temporal el ultimo presionado
    last_button = BTN_NONE;         //resetea el ultimo presionado
    return btn_temp;                //devuelve el boton que se presiono
}