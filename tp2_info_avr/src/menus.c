#include "menus.h"
#include "control.h"
#include "avr_Uart.h"
#include "config.h"


Menu_t currentMenu = MENU_IDLE;
ManualState_t currentManualState = MANUAL_SETPOINT;
ReflowState_t currentReflowState = REFLOW_PREHEAT;
static int16_t manualSetpoint = TEMP_COOLED;

static bool manualRunning = false;
static bool reflowRunning = false;

MenuHandler_t menuTable[MENU_COUNT] = {
    menuIdle,
    menuManual,
    menuReflow
};


void menuIdle(void) {
    static Menu_t lastMenu = MENU_COUNT;
     if (lastMenu != MENU_IDLE) {
        uart_puts("MENU: IDLE\r\n");
        lastMenu = MENU_IDLE;
    }

    Button_t btn = buttons_get();
    if(btn == BTN_NONE) return;

    if (btn == BTN_SELECT) {
        currentMenu = (currentMenu + 1) % MENU_COUNT;
        lastMenu = MENU_COUNT;
    }
    if (btn == BTN_ENTER) {
        uart_puts("Info:\r\n");
        uart_puts("  T_amb = "); uart_putint(control_getCurrentTemp()); uart_puts(" C\r\n");
        uart_puts("  SP     = "); uart_putint(control_getTargetTemp());   uart_puts(" C\r\n");
        uart_puts("  Hyst   = "); uart_putint(TEMP_HYSTERESIS); uart_puts(" C\r\n");
        return;
        return;
    }
}

//*****************************************************
//FUNCIONES DEDICADAS AL FUNCIONAMIENTO DEL MODO MANUAL
//*****************************************************
void menuManual(void) {
    static Menu_t lastMenu = MENU_COUNT;
     if (lastMenu != MENU_MANUAL) {
        uart_puts("MENU: MANUAL\r\n");
        lastMenu = MENU_MANUAL;
    }

    Button_t btn = buttons_get();
  
    if (btn == BTN_SELECT) {
        currentMenu = (currentMenu + 1) % MENU_COUNT;
        lastMenu = MENU_COUNT;
        return;
    }
    //reinyeccion de boton.
    if (btn != BTN_NONE) {
        buttons_set(btn);
    }

    ManualState_t estado = manualStateTable[currentManualState]();
    if(estado == MANUAL_EXIT){
        uart_puts("MANUAL: EXIT -> RESET\r\n");
        system_reset();
        lastMenu = MENU_COUNT;
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
    static bool printed = false;
    Button_t btn = buttons_get();
     if (!printed) {
        uart_puts("MANUAL STATE: SETPOINT\r\n");
        printed = true;
    }

    if(btn == BTN_UP){
        manualSetpoint += 10;
        uart_puts("SetPoint = "); 
        uart_putint(manualSetpoint); 
        uart_puts(" C\r\n");
    }
    if(btn == BTN_DOWN){
        manualSetpoint -= 10;
        uart_puts("SetPoint = "); 
        uart_putint(manualSetpoint); 
        uart_puts(" C\r\n");
    }
    if(btn == BTN_ENTER){
        control_setTarget(manualSetpoint, TEMP_HYSTERESIS);
        // manualRunning = true;
        uart_puts("Manual: starting (HOLD)"); 
        printed = false;
        return MANUAL_HOLD;
    }
    return MANUAL_SETPOINT;
}

ManualState_t stateManualHold(void){
    static bool printed = false;
    static uint16_t hold_seconds = 0;
    static bool reached_setpoint = false;

     if (!printed) {
        uart_puts("MANUAL STATE: HOLD\r\n");
        printed = true;
    }
    
    if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    control_update();

    if(!reached_setpoint){
        if(control_getCurrentTemp() >= (control_getTargetTemp() - TEMP_HYSTERESIS)){
            reached_setpoint = true;
            hold_seconds = 0;
            uart_puts("HOLD: reached SP, starting timer\r\n");
            control_update();
        }
        if(timer_seconds()){
            uart_puts("Temperatura = ");
            uart_putint(control_getCurrentTemp());
            uart_puts(" C\r\n");
        }
        return MANUAL_HOLD;
    }
    
    if(timer_seconds()){
        control_update();
        if(control_getCurrentTemp() >= (control_getTargetTemp() - TEMP_HYSTERESIS) && control_getCurrentTemp() <= (control_getTargetTemp() + TEMP_HYSTERESIS)){
            hold_seconds++;
            uart_puts("TIM HOLD = ");
            uart_putint(hold_seconds);
            uart_puts("s Temp =");
            uart_putint(control_getCurrentTemp());
            uart_puts(" C\r\n");
        }else{
            uart_puts("HOLD: out of range, no time counted. T=");
            uart_putint(control_getCurrentTemp());
            uart_puts(" C  SetPoint=");
            uart_putint(control_getTargetTemp());
            uart_puts(" C\r\n");
        }
        if(hold_seconds>=TIM_MANUAL_HOLD){
            printed = false;
            hold_seconds=0;
            reached_setpoint = false;
            return MANUAL_COOLING;
        }
    }
    return MANUAL_HOLD;
}

ManualState_t stateManualCooling(void){
    static bool printed = false;
    static uint16_t manual_cooled_seconds = 0;
     
    if (!printed) {
        uart_puts("MANUAL STATE: COOLING\r\n");
        printed = true;
    }

    
    if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    control_reset();//setea las temperaturas a default

    if(timer_seconds()){
        manual_cooled_seconds++;
        uart_puts("TIM COOLING = ");
        uart_putint(manual_cooled_seconds);
        uart_puts("s Temp = ");
        uart_putint(control_getCurrentTemp());
        uart_puts(" C\r\n");

        if(control_getCurrentTemp() <=TEMP_COOLED && manual_cooled_seconds >= TIM_COOLED){ 
            manual_cooled_seconds = 0;
            printed = false;
            return MANUAL_EXIT;
            }
        }

    return MANUAL_COOLING;
}



//*****************************************************
//FUNCIONES DEDICADAS AL FUNCIONAMIENTO DEL MODO REFLOW
//*****************************************************
void menuReflow(void) {
    static Menu_t lastMenu = MENU_COUNT;
     if (lastMenu != MENU_REFLOW) {
        uart_puts("MENU: REFLOW\r\n");
        lastMenu = MENU_REFLOW;
    }    

    Button_t btn = buttons_get();
   
    if (!reflowRunning) {
        if (btn == BTN_SELECT) {
            currentMenu = (currentMenu + 1) % MENU_COUNT;
            lastMenu = MENU_COUNT;
        }

        if (btn == BTN_ENTER) {
            uart_puts("REFLOW: START\r\n");
            currentReflowState = REFLOW_PREHEAT;
            reflowRunning = true;
        }
        return;
    }

    ReflowState_t estado = reflowStateTable[currentReflowState]();
    if(estado == REFLOW_EXIT){
        uart_puts("REFLOW: EXIT -> RESET\r\n");
        system_reset();
        lastMenu = MENU_COUNT;                       
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
    static bool printed = false;
    if (!printed) {
        uart_puts("REFLOW STATE: PREHEAT\r\n");
        control_setTarget(TEMP_PREHEAT_TARGET, TEMP_HYSTERESIS);
        printed = true;
    }

    if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    control_update();

     if (timer_seconds()) {
        uart_puts("[PREHEAT] T= ");
        uart_putint(control_getCurrentTemp());
        uart_puts(" C  SetPoint= ");
        uart_putint(control_getTargetTemp());
        uart_puts(" C\r\n");
    }

    if(control_getCurrentTemp() >=(TEMP_PREHEAT_TARGET-TEMP_HYSTERESIS)){
        printed = false;
        return REFLOW_SOAK;
    }return REFLOW_PREHEAT;
}

ReflowState_t stateReflowSoak(void){
    static uint16_t reflowsoak_seconds = 0;
    static bool printed = false;
    static bool soak_started = false;

    if (!printed) {
        uart_puts("REFLOW STATE: SOAK\r\n");
        control_setTarget(TEMP_SOAK_TARGET, TEMP_HYSTERESIS);
        printed = true;
        reflowsoak_seconds = 0;
        soak_started = false;
    }

    if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    control_update();
    
    if (!soak_started) {
        if (control_getCurrentTemp() >= (TEMP_SOAK_TARGET - TEMP_HYSTERESIS)) {
            soak_started = true;
            reflowsoak_seconds = 0;
            uart_puts("SOAK: reached SP, starting timer\r\n");
        }
        if (timer_seconds()) {
        uart_puts("[SOAK] T= ");
        uart_putint(control_getCurrentTemp());
        uart_puts(" C  SetPoint= ");
        uart_putint(control_getTargetTemp());
        uart_puts(" C\r\n");
        }
        return REFLOW_SOAK;
    }

    if(timer_seconds()){
        control_update();
        if(control_getCurrentTemp() >= (control_getTargetTemp() - TEMP_HYSTERESIS) && control_getCurrentTemp() <= (control_getTargetTemp() + TEMP_HYSTERESIS)){
            reflowsoak_seconds++;
            uart_puts("TIM SOAK = ");
            uart_putint(reflowsoak_seconds);
            uart_puts("s Temp = ");
            uart_putint(control_getCurrentTemp());
            uart_puts(" C\r\n");
        }else{
            uart_puts("HOLD: out of range, no time counted. T= ");
            uart_putint(control_getCurrentTemp());
            uart_puts(" C  SetPoint= ");
            uart_putint(control_getTargetTemp());
            uart_puts(" C\r\n");
        }
        if (reflowsoak_seconds >= TIM_SOAK_TARGET) {
            printed = false;
            return REFLOW_RAMP;
        }
    }return REFLOW_SOAK;
}

ReflowState_t stateReflowRamp(void){
    static bool printed = false;
    if (!printed) {
        uart_puts("REFLOW STATE: RAMP\r\n");
        control_setTarget(TEMP_RAMP_TARGET, TEMP_HYSTERESIS);
        printed = true;
    }
   if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    control_update();
     if (timer_seconds()) {
        uart_puts("[RAMP] T= ");
        uart_putint(control_getCurrentTemp());
        uart_puts(" C  SetPoint= ");
        uart_putint(control_getTargetTemp());
        uart_puts(" C\r\n");
    }
    if (control_getCurrentTemp() >= (TEMP_RAMP_TARGET-TEMP_HYSTERESIS)) {
        printed = false;
        return REFLOW_PEAK;
    }
    return REFLOW_RAMP;
}

ReflowState_t stateReflowPeak(void){
    static bool printed = false;
    static bool peak_started = false;
    static uint16_t reflowpeak_seconds = 0;

    if (!printed) {
        uart_puts("REFLOW STATE: PEAK\r\n");
        control_setTarget(TEMP_PEAK_TARGET, TEMP_HYSTERESIS);
        peak_started = false;
        reflowpeak_seconds = 0;
        printed = true;
    }
    
    if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    control_update();
    if (!peak_started) {
        if (control_getCurrentTemp() >= (TEMP_PEAK_TARGET - TEMP_HYSTERESIS)) {
            peak_started = true;
            reflowpeak_seconds = 0;
            uart_puts("PEAK: reached SP, starting timer\r\n");
        }
        if (timer_seconds()) {
        uart_puts("[PEAK] T= ");
        uart_putint(control_getCurrentTemp());
        uart_puts(" C  SetPoint= ");
        uart_putint(control_getTargetTemp());
        uart_puts(" C\r\n");
    }
        return REFLOW_PEAK;
    }

    if(timer_seconds()){
        control_update();
        if(control_getCurrentTemp() >= (control_getTargetTemp() - TEMP_HYSTERESIS) && control_getCurrentTemp() <= (control_getTargetTemp() + TEMP_HYSTERESIS)){
            reflowpeak_seconds++;
            uart_puts("TIM PEAK = ");
            uart_putint(reflowpeak_seconds);
            uart_puts("s Temp = ");
            uart_putint(control_getCurrentTemp());
            uart_puts(" C\r\n");
        }else{
            uart_puts("HOLD: out of range, no time counted. T= ");
            uart_putint(control_getCurrentTemp());
            uart_puts(" C  SetPoint= ");
            uart_putint(control_getTargetTemp());
            uart_puts(" C\r\n");
        }
         if (reflowpeak_seconds >= TIM_PEAK_TARGET) {
            printed = false;
            return REFLOW_COOLING;
        }
    }return REFLOW_PEAK;
}


ReflowState_t stateReflowCooling(void){
    static uint16_t reflow_cooling_seconds = 0;
    static bool printed = false;

    if (!printed) {
        uart_puts("REFLOW STATE: COOLING\r\n");
        reflow_cooling_seconds = 0;
        printed = true;
    }

    if(adc_ready()){
        control_setCurrentTemp((int16_t)adc_convertCelsius());
    }
    control_reset();

    if (timer_seconds()) { 
        reflow_cooling_seconds++;
        uart_puts("TIM COOLING = ");
        uart_putint(reflow_cooling_seconds);
        uart_puts("s Temp = ");
        uart_putint(control_getCurrentTemp());
        uart_puts(" C\r\n");
        uart_puts("   SetPoint = ");
        uart_putint(control_getTargetTemp());
        uart_puts(" C\r\n");

        if (control_getCurrentTemp() <= TEMP_COOLED && reflow_cooling_seconds >= TIM_COOLED) {
            printed = false;
            return REFLOW_EXIT;
        }
    }
    return REFLOW_COOLING;
}

void system_reset(void) {
    currentMenu = MENU_IDLE;
    currentManualState = MANUAL_SETPOINT;
    currentReflowState = REFLOW_PREHEAT;
    manualRunning = false;
    reflowRunning = false;
    control_reset();
}