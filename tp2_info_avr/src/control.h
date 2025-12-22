#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Prototipo de funcion control_setTarget - Función setter para las temperatura objetivo.
 * @params: {int16_t,int16_t} - Temperatura a alcanzar ; temperatura de margen de histeresis.
 * @returns: {void}
 */
void control_setTarget(int16_t temp, int16_t h);

/*
 * Prototipo de funcion control_getTargetTemp - Función getter para las temperatura objetivo.
 * @params: {void} - 
 * @returns: {int16_t}
 */
int16_t control_getTargetTemp(void);

/*
 * Prototipo de funcion control_setCurrentTemp - Función setter para la variable de temperatura actual.
 * @params: {int16_t}
 * @returns: {void}
 */
void control_setCurrentTemp(int16_t temp);

/*
 * Prototipo de funcion control_getCurrentTemp - Función getter para las lecturas de temperatura actuales medidas.
 * @params: {void} 
 * @returns: {int16_t}
 */
int16_t control_getCurrentTemp(void);

/*
 * Prototipo de funcion control_update - Función que permite actualizar el valor de temperatura leída por el ADC, y en función a eso, encender el calefactor.
 * @params: {}  
 * @returns: {void}
 */
void control_update();

/*
 * Prototipo de funcion control_isHeating - Función flag para indicar el funcionamiento del calefactor.
 * @params: {void} 
 * @returns: {bool}
 */
bool control_isHeating(void);

/*
 * Prototipo de funcion control_reset - Función para establecer un hard reset en parámetros de temperatura.
 * @params: {void} 
 * @returns: {void}
 */
void control_reset(void);

/*
 * Prototipo de funcion uart_putint - Función usada para el debug por puerto Serial. Permite el muestreo de variables.
 * @params: {int16_t} - Variable a imprimir.
 * @returns: {void}
 */
static void uart_putint(int16_t val);

#endif
