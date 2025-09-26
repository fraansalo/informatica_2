#include "menus.h"
#include "config.h"
#include <stdint.h>


static int16_t targetTemp = 0;
static int16_t h = 0;
static bool heating = false;


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