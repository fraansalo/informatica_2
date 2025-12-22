#ifndef ADC_H
#define ADC_H
#include <stdint.h>
#include <stdbool.h>
#define adc_to_celsius(adc) ((float)(adc)*0.488f)

/*
 * Prototipo de funcion adc_init - Función de inicialización del conversor ADC.
 * @params: {void} 
 * @returns: {void}
 */
void adc_init(void);

/*
 * Prototipo de funcion adc_ready - Función flag que indica cuando conversor esta listo.
 * @params: {void} 
 * @returns: {bool}
 */
bool adc_ready(void);

/*
 * Prototipo de funcion adc_getter - Función para obtener el valor de la lectura del conversor.
 * @params: {void} 
 * @returns: {uint16_t}
 */
uint16_t adc_getter(void);

/*
 * Prototipo de funcion adc_convertCelsius - Función que toma el valor de la lectura y utiliza una macro para convertirlo a grados celsius.
 * @params: {void} - 
 * @returns: {float}
 */
float adc_convertCelsius(void);

#endif