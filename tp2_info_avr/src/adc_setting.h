#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdbool.h>

void adc_init(void);
bool adc_ready(void);
uint16_t adc_getter(void);

#endif