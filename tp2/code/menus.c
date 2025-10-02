#include "menus.h"
#include "config.h"
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

//*****************************************************
//FUNCIONES DEDICADAS AL FUNCIONAMIENTO DEL MODO MANUAL
//*****************************************************
void menuManual(void) {
    ManualState_t estado = manualStateTable[currentManualState]();
    if(estado == MANUAL_EXIT){
        system_reset();
    }else{
        currentManualState = estado;
    }
}

ManualHandler_t manualStateTable[MANUAL_STATE_COUNT] = {
    stateManualSetpoint,
    stateManualHold,
    stateManualCooling,
    NULL
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



//*****************************************************
//FUNCIONES DEDICADAS AL FUNCIONAMIENTO DEL MODO REFLOW
//*****************************************************
void menuReflow(void) {     
    ManualState_t estado = reflowStateTable[currentReflowState]();
    if(estado == REFLOW_EXIT){
        system_reset();                       //lo hacemos para asegurar por si hubo alguna particularidad en el reseteo del modo.
    }else{
        currentManualState = estado;
    }
}

ReflowHandler_t reflowStateTable[REFLOW_STATE_COUNT] = {
    stateReflowPreheat,
    stateReflowSoak,
    stateReflowRamp,
    stateReflowPeak,
    stateReflowCooling,
    NULL
};

ReflowState_t stateReflowPreheat(void){
    control_setTarget(TEMP_PREHEAT_TARGET,TEMP_HYSTERESIS);
    control_update(temp_current);
    if(temp_current>=TEMP_PREHEAT_TARGET){
        return REFLOW_SOAK;
    }return REFLOW_PREHEAT;
}

ReflowState_t stateReflowSoak(void){
    control_setTarget(TEMP_SOAK_TARGET,TEMP_HYSTERESIS);
    control_update(temp_current);
    //se verifica el tiempo transcurrido del timer.

    // if (state_timer == 0) return REFLOW_RAMP; Una vez configurado el timer
    // return REFLOW_SOAK;
}

ReflowState_t stateReflowRamp(void){
    control_setTarget(TEMP_RAMP_TARGET, TEMP_HYSTERESIS);
    control_update(temp_current);

    if (temp_current >= TEMP_RAMP_TARGET) {
        return REFLOW_PEAK;
    }
    return REFLOW_RAMP;
}

ReflowState_t stateReflowPeak(void){
    control_setTarget(TEMP_PEAK_TARGET,TEMP_HYSTERESIS);
    control_update(temp_current);
    //se verifica el tiempo transcurrido del timer.

    // if (state_timer == 0) return REFLOW_COOLING; Una vez configurado el timer
    // return REFLOW_PEAK;
}

ReflowState_t stateReflowCooling(void){
    control_reset();//setea las temperaturas a default
    if(temp_current<=TEMP_COOLED) return REFLOW_EXIT;
    return REFLOW_COOLING;
}
