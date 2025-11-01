#ifndef MENU_H
#define MENU_H
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "timer_setting.h"
#include "adc_setting.h"

//*****************************************************
//definiciones para el menu de funcionamiento manual
//*****************************************************
typedef enum {
    MANUAL_SETPOINT,
    MANUAL_HOLD,
    MANUAL_COOLING,
    MANUAL_EXIT,
    MANUAL_STATE_COUNT
} ManualState_t;

extern ManualState_t currentManualState;
ManualState_t stateIdle(void);  
ManualState_t stateManualSetpoint(void);
ManualState_t stateManualHold(void);
ManualState_t stateManualCooling(void);
typedef ManualState_t (*ManualHandler_t)(void);
extern ManualHandler_t manualStateTable[MANUAL_STATE_COUNT];

//*****************************************************
//definiciones para el menu de funcionamiento reflow
//*****************************************************
typedef enum {
    REFLOW_PREHEAT,
    REFLOW_SOAK,
    REFLOW_RAMP,
    REFLOW_PEAK,
    REFLOW_COOLING,
    REFLOW_EXIT,
    REFLOW_STATE_COUNT
} ReflowState_t;

extern ReflowState_t currentReflowState;
ReflowState_t stateReflowPreheat(void);
ReflowState_t stateReflowSoak(void);
ReflowState_t stateReflowRamp(void);
ReflowState_t stateReflowPeak(void);
ReflowState_t stateReflowCooling(void);
typedef ReflowState_t (*ReflowHandler_t)(void);  //queda pendiente de cambio y modificacion
extern ReflowHandler_t reflowStateTable[REFLOW_STATE_COUNT];

//*****************************************************
//definiciones para botones
//*****************************************************
typedef enum {
    BTN_NONE,
    BTN_UP,
    BTN_DOWN,
    BTN_ENTER,
    BTN_SELECT
} Button_t;
void buttons_set(Button_t btn);
Button_t buttons_get(void);


//*****************************************************
//definiciones para control temp.
//*****************************************************
void control_setTarget(int16_t temp, int16_t h);
void control_update(int16_t temp_current);
bool control_isHeating(void);
void control_reset(void);



//*****************************************************
//definiciones de menus
//*****************************************************
typedef enum {
    MENU_NONE,
    MENU_IDLE,
    MENU_MANUAL,
    MENU_REFLOW,
    MENU_COUNT
} Menu_t;


void menuIdle(void);
void menuManual(void);
void menuReflow(void);

typedef void (*MenuHandler_t)(void);

MenuHandler_t menuTable[MENU_COUNT] = {
    menuIdle,
    menuManual,
    menuReflow,
};
extern Menu_t currentMenu;

#endif