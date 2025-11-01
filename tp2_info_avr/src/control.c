#include "menus.h"
#include "config.h"
#include <stdint.h>


int16_t targetTemp = TEMP_COOLED;
int16_t temp_current = TEMP_COOLED;
int16_t h = TEMP_HYSTERESIS;
bool heating = false;

//Me resetea la temperatura actual a temperatura ambiente
void control_reset(void){
    targetTemp = TEMP_COOLED;
    h = TEMP_HYSTERESIS;
    heating = false;
    temp_current = TEMP_COOLED; 
    heater_setter(false);
}

//seteo la temperatura a alcanzar en la etapa correspondiente.
void control_setTarget(int16_t temp, int16_t hysteresis) {
    targetTemp = temp;
    h = hysteresis;
    heating = true; // arranca a calentar.
    heater_setter(heating);
}

//hace el control recurrente para verificar si se calentó lo suficiente por hysteresis
void control_update(int16_t temp_current) {
    if (temp_current <= (targetTemp - h)) {
        heating = true;  
        heater_setter(heating);
    } else if (temp_current >= (targetTemp + h)) {
        heating = false;  
        heater_setter(heating);
    }
}

bool control_isHeating(void) {
    return heating;
}

void system_reset(void) {
    currentMenu = MENU_IDLE;
    currentManualState = MANUAL_SETPOINT;
    currentReflowState = REFLOW_PREHEAT;
    control_reset();
}