#include <stdio.h>
#include <stdint.h>
#include "menus.h"
#include "config.h"

int main(void) {

    ManualState_t currentManualState = MANUAL_SETPOINT;
    ReflowState_t currentReflowState = REFLOW_PREHEAT;


    system_init();
    while (1) {
        menuTable[currentMenu]();  // ejecuta el handler del menú actual
    }
}