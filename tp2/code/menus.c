#include <stdio.h>
#include <menus.h>
#include <config.h>
#include <stdbool.h>
#include <stdint.h>
#include <control.c>

ManualState_t currentManualState = MANUAL_SETPOINT;
ReflowState_t currentReflowState = REFLOW_PREHEAT;

void menuIdle(void) {
    Button_t btn = buttons_get();

    if (btn == BTN_SELECT) {
        currentMenu = (currentMenu + 1) % MENU_COUNT;
    }
    if (btn == BTN_ENTER) {
        if (currentMenu == MENU_MANUAL) currentMenu = MENU_MANUAL;
        else if (currentMenu == MENU_REFLOW) currentMenu = MENU_REFLOW;
    }
}


void menuManual(void) {
    manualStateTable[currentManualState]();
}

ManualHandler_t manualStateTable[MANUAL_STATE_COUNT] = {
    stateManualSetpoint,
    stateManualHold,
    stateManualCooling
};

void stateManualSetpoint(void){
    Button_t btn = buttons_get();
    if(btn == BTN_UP){
        targetTemp += 10;
    }
    else if(btn == BTN_DOWN){
        targetTemp -= 10;
    }
    else if(btn == BTN_ENTER){
        //se configuraria un timer
        currentManualState = MANUAL_HOLD;
    }
}

void stateManualHold(void){
    control_setTarget(targetTemp,TEMP_HYSTERESIS);
    control_update(temp_current);
    //se verifica el tiempo transcurrido del timer.
    //deberia encontrarse la manera de simular el crecimiento y decrecimiento de temp
    //una vez acabado el manualHold currentManualState pasaría a MANUAL_COOLING.
}

void stateManualCooling(void){
    control_reset();//setea las temperaturas a default
    //deberia encontrarse la manera de simular el crecimiento y decrecimiento de temp
    currentManualState = MANUAL_SETPOINT;
    currentMenu = MENU_IDLE;
}


void menuReflow(void) {
    reflowStateTable[currentReflowState]();
}