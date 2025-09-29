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


//FUNCIONES DEDICADAS AL FUNCIONAMIENTO DEL MODO MANUAL
void menuManual(void) {
    ManualState_t estado = manualStateTable[currentManualState]();
    if(estado == MANUAL_EXIT){
        currentManualState = MANUAL_SETPOINT;   //si termino, volvemos al estado inicial de manual
        currentMenu = MENU_IDLE;                //si termino, retornamos al modo espera del menu.
    }else{
        currentManualState = estado;
    }

}

ManualHandler_t manualStateTable[MANUAL_STATE_COUNT] = {
    stateManualSetpoint,
    stateManualHold,
    stateManualCooling
};

ManualState_t stateManualSetpoint(void){
    Button_t btn = buttons_get();
    if(btn == BTN_UP) targetTemp += 10;
    if(btn == BTN_DOWN)targetTemp -= 10;
    if(btn == BTN_ENTER){
        //se configuraria un timer
        return MANUAL_HOLD;
    }
    return MANUAL_SETPOINT;
}

ManualState_t stateManualHold(void){
    control_setTarget(targetTemp,TEMP_HYSTERESIS);
    control_update(temp_current);
    //se verifica el tiempo transcurrido del timer.

    // if (state_timer == 0) return MANUAL_COOLING; Una vez configurado el timer
    // return MANUAL_HOLD;
}

ManualState_t stateManualCooling(void){
    control_reset();//setea las temperaturas a default
    if(temp_current<=TEMP_COOLED) return MANUAL_EXIT;
    return MANUAL_COOLING;
}


//FUNCIONES DEDICADAS AL FUNCIONAMIENTO DEL MODO REFLOW
void menuReflow(void) {     //queda pendiente de cambio y modificacion
    reflowStateTable[currentReflowState]();
}