#ifndef ADC_H
#define ADC_H
#include <stdint.h>
#include <stdbool.h>
#include "avr_Adc.h"
#include <avr/interrupt.h>
#define adc_to_celsius(adc) ((float)(adc)*0.448f)

void adc_init(void);
bool adc_ready(void);
uint16_t adc_getter(void);
float adc_convertCelsius(void);

#endif