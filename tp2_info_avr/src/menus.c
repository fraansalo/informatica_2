#include "menus.h"
#include "control.h"

Menu_t currentMenu = MENU_IDLE;
ManualState_t currentManualState = MANUAL_SETPOINT;
ReflowState_t currentReflowState = REFLOW_PREHEAT;
static int16_t manualSetpoint = TEMP_COOLED;

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
    if(btn == BTN_UP) manualSetpoint += 10;
    if(btn == BTN_DOWN)manualSetpoint -= 10;
    if(btn == BTN_ENTER){
        control_setTarget(manualSetpoint, TEMP_HYSTERESIS);
        return MANUAL_HOLD;
    }
    return MANUAL_SETPOINT;
}

ManualState_t stateManualHold(void){
    static uint16_t hold_seconds = 0;
    if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    control_update();
    
    if(timer_seconds()){
        hold_seconds++;
        if(hold_seconds>=MANUAL_HOLD){
            hold_seconds=0;
            return MANUAL_COOLING;
        }
    }
    return MANUAL_HOLD;
}

ManualState_t stateManualCooling(void){
    static uint16_t manual_cooled_seconds = 0;
    if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    control_reset();//setea las temperaturas a default

    if(timer_seconds()){
        manual_cooled_seconds++;
        if(control_getCurrentTemp() <=TEMP_COOLED && manual_cooled_seconds >= TIM_COOLED){ 
            manual_cooled_seconds = 0;
            return MANUAL_EXIT;
            }
        }
    return MANUAL_COOLING;
}



//*****************************************************
//FUNCIONES DEDICADAS AL FUNCIONAMIENTO DEL MODO REFLOW
//*****************************************************
void menuReflow(void) {     
    ReflowState_t estado = reflowStateTable[currentReflowState]();
    if(estado == REFLOW_EXIT){
        system_reset();                       //lo hacemos para asegurar por si hubo alguna particularidad en el reseteo del modo.
    }else{
        currentReflowState = estado;
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
   if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    control_setTarget(TEMP_PREHEAT_TARGET,TEMP_HYSTERESIS);
    control_update();

    if(control_getCurrentTemp()>=TEMP_PREHEAT_TARGET){
        return REFLOW_SOAK;
    }return REFLOW_PREHEAT;
}

ReflowState_t stateReflowSoak(void){
    static uint16_t reflowsoak_seconds = 0;
    if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    
    control_setTarget(TEMP_SOAK_TARGET,TEMP_HYSTERESIS);
    control_update();
    
    if(timer_seconds()){
        reflowsoak_seconds++;
        if(reflowsoak_seconds > TIM_SOAK_TARGET){
            reflowsoak_seconds = 0;
            return REFLOW_RAMP;
        }
    }
    return REFLOW_SOAK;
}

ReflowState_t stateReflowRamp(void){
   if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    control_setTarget(TEMP_RAMP_TARGET, TEMP_HYSTERESIS);
    control_update();

    if (control_getCurrentTemp() >= TEMP_RAMP_TARGET) {
        return REFLOW_PEAK;
    }
    return REFLOW_RAMP;
}

ReflowState_t stateReflowPeak(void){
    if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    static uint16_t reflowpeak_seconds = 0;
    control_setTarget(TEMP_PEAK_TARGET,TEMP_HYSTERESIS);
    control_update();
    
    if(timer_seconds()){
        reflowpeak_seconds++;
        if(reflowpeak_seconds >= TIM_PEAK_TARGET){
            reflowpeak_seconds = 0;
            return REFLOW_COOLING;
        }
    }
    return REFLOW_PEAK;
}

ReflowState_t stateReflowCooling(void){
    if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    static uint16_t reflow_cooling_seconds = 0;
    control_reset();//setea las temperaturas a default

    if(timer_seconds()){
        reflow_cooling_seconds++;
        if(reflow_cooling_seconds>=TIM_COOLED && control_getCurrentTemp() <= TEMP_COOLED){
            reflow_cooling_seconds = 0;
            return REFLOW_EXIT;
        }
    }
    return REFLOW_COOLING;
}

void system_reset(void) {
    currentMenu = MENU_IDLE;
    currentManualState = MANUAL_SETPOINT;
    currentReflowState = REFLOW_PREHEAT;
    control_reset();
}