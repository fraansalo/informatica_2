#include "menus.h"
#include "config.h"
#include <stdint.h>


extern int16_t targetTemp = TEMP_COOLED;
extern int16_t temp_current = TEMP_COOLED;
extern int16_t h = TEMP_HYSTERESIS;
extern bool heating = false;

void control_reset(void){
    targetTemp = TEMP_COOLED;
    h = TEMP_HYSTERESIS;
    heating = false;
}

void control_setTarget(int16_t temp, int16_t hysteresis) {
    targetTemp = temp;
    h = hysteresis;
    heating = true; // arranca calentando
}

void control_update(int16_t temp_current) {
    if (temp_current < (targetTemp - h)) {
        heating = true;   
    } else if (temp_current > (targetTemp + h)) {
        heating = false;  
    }
}

bool control_isHeating(void) {
    return heating;
}