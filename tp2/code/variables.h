#ifndef VAR_H
#define VAR_H

//definiciones para el menu de funcionamiento manual
typedef enum {
    MANUAL_SETPOINT,
    MANUAL_HOLD,
    MANUAL_COOLING,
    MANUAL_STATE_COUNT
} ManualState_t;

extern ManualState_t currentManualState;

typedef void (*ManualHandler_t)(void);

void stateIdle(void);
void stateManualSetpoint(void);
void stateManualHold(void);
void stateManualCooling(void);

extern ManualHandler_t manualStateTable[MANUAL_STATE_COUNT];


//definiciones para el menu de funcionamiento reflow
typedef enum {
    REFLOW_PREHEAT,
    REFLOW_SOAK,
    REFLOW_RAMP,
    REFLOW_PEAK,
    REFLOW_COOLING,
    REFLOW_STATE_COUNT
} ReflowState_t;

extern ReflowState_t currentReflowState;

typedef void (*ReflowHandler_t)(void);

void stateReflowPreheat(void);
void stateReflowSoak(void);
void stateReflowRamp(void);
void stateReflowPeak(void);
void stateReflowCooling(void);

extern ReflowHandler_t reflowStateTable[REFLOW_STATE_COUNT];


//definiciones para botones
typedef enum {
    BTN_NONE,
    BTN_UP,
    BTN_DOWN,
    BTN_ENTER,
    BTN_SELECT
} Button_t;

//definiciones de menus
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
void menuConfig(void);

typedef void (*MenuHandler_t)(void);

MenuHandler_t menuTable[MENU_COUNT] = {
    menuIdle,
    menuManual,
    menuReflow,
    menuConfig
};

extern Menu_t currentMenu;


#endif