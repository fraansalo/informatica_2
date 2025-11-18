#include "menus.h"
#include "config.h"
#include <stdint.h>
#include "gpio_setting.h"


static int16_t targetTemp = TEMP_COOLED;
static int16_t temp_current = TEMP_COOLED;
static int16_t h = TEMP_HYSTERESIS;
static bool heating = false;

//Me resetea la temperatura actual a temperatura ambiente
void control_reset(void){
    targetTemp = TEMP_COOLED;
    h = TEMP_HYSTERESIS;
    heating = false;
    temp_current = TEMP_COOLED; 
    heater_setter(false);
}

//Setter y getter de la temperatura objetivo
void control_setTarget(int16_t temp, int16_t hysteresis) {
    targetTemp = temp;
    h = hysteresis;
    // heating = true; // arranca a calentar.
    // heater_setter(heating);
}
int16_t control_getTargetTemp(void){
    return targetTemp;
}


void control_setCurrentTemp(int16_t temp){
    temp_current =temp;
}
int16_t control_getCurrentTemp(void){
    return temp_current;
}

//hace el control recurrente para verificar si se calentó lo suficiente por hysteresis
void control_update(){
    if (temp_current <= (targetTemp - h)) {
        heating = true;  
    } else if (temp_current >= (targetTemp + h)) {
        heating = false;  
    }
    heater_setter(heating);
}

bool control_isHeating(void) {
    return heating;
}

