#ifndef MENU_H
#define MENU_H
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "timer_setting.h"
#include "adc_setting.h"


void system_reset(void);

//************************************************************************************************
//                      definiciones para el menu de funcionamiento manual
//************************************************************************************************
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

//************************************************************************************************
//                     definiciones para el menu de funcionamiento reflow
//************************************************************************************************
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
typedef ReflowState_t (*ReflowHandler_t)(void);
extern ReflowHandler_t reflowStateTable[REFLOW_STATE_COUNT];

//************************************************************************************************
//                                  definiciones para botones
//************************************************************************************************

typedef enum {
    BTN_NONE,
    BTN_UP,
    BTN_DOWN,
    BTN_ENTER,
    BTN_SELECT
} Button_t;

/*
 * Prototipo de funcion buttons_set - Función setter para los botones. Matchea con la función polling de botones. 
 * @params: {Button_t} - Objeto de boton a settear.
 * @returns: {void}
 */
void buttons_set(Button_t btn);

/*
 * Prototipo de funcion buttons_get - Función getter para los botones presionados.
 * @params: {void}
 * @returns: {Button_t} - Objeto de boton solicitado
 */
Button_t buttons_get(void);

//************************************************************************************************
//                                  definiciones de menus
//************************************************************************************************

typedef enum {
    MENU_IDLE = 0,
    MENU_MANUAL,
    MENU_REFLOW,
    MENU_COUNT
} Menu_t;

/*
 * Prototipo de funcion menuIdle - Función que establece el funcionamiento del menu stand-by.
 * @params: {void} 
 * @returns: {void}
 */
void menuIdle(void);

/*
 * Prototipo de funcion menuManual - Función que establece el funcionamiento del menu Manual.
 * @params: {bool} - 
 * @returns: {void}
 */
void menuManual(void);

/*
 * Prototipo de funcion menuReflow - Función que establece el funcionamiento del menu reflow.
 * @params: {void}  
 * @returns: {void}
 */
void menuReflow(void);

/*
 * Prototipo de funcion system_reset - Establece un reset del funcionamiento principal del programa.
 * @params: {void} 
 * @returns: {void}
 */
void system_reset(void);

/*
 * @typedef MenuHandler_t
 * @brief Tipo de puntero a función para handlers de menú.
 *
 * Define el prototipo común de todas las funciones que implementan
 * un menú o estado principal del sistema.
 */
typedef void (*MenuHandler_t)(void);

/* @brief Tabla de funciones de los menús del sistema.
 *
 * Array de punteros a funciones que implementan los distintos menús
 * principales del sistema (IDLE, MANUAL, REFLOW, etc.).
 */
extern MenuHandler_t menuTable[MENU_COUNT];
extern Menu_t currentMenu;

#endif