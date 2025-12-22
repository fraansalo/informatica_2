#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Prototipo de funcion timer_init - Inicializador del timer del AVR.
 * @params: {void}
 * @returns: {void}
 */
void timer_init(void);

/*
 * Prototipo de funcion timer_tick - Función referenciada a flags para indicar el cumplimiento de un ciclo.
 * @params: {void}
 * @returns: {bool}
 */
bool timer_tick(void);

/*
 * Prototipo de funcion timer_seconds - Función que indica que transcurrió un segundo.
 * @params: {void}
 * @returns: {bool}
 */
bool timer_seconds(void);


#endif