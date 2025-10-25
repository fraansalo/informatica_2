#include "adc_setting.h"
#include "avr_Adc.h"
#include <avr/interrupt.h>

volatile static uint16_t adc_value = 0;
volatile static bool adc_flag = false;

//callback al completar la conversión del canal ADC.
static void adc_handler(void){
    if (ADMUX & (1 << ADLAR)) {
        adc_value = ADCH;   // Si está en res. 8 bits
    } else {
        adc_value = ADCL | (ADCH << 8); // Si esta en res. 10 bits
    }
    adc_flag = true;
}


void adc_init(){
    AdcInitStructure_AVR mi_adc;

    mi_adc.channel = avr_ADC_canal0;
    mi_adc.mode = avr_ADC_MODE_Interrupt_request;
    mi_adc.prescaler = avr_ADC_Prescaler_128;
    mi_adc.reference = avr_ADC_REF_AVcc;
    mi_adc.resolution = avr_ADC_RES_10Bit;
    mi_adc.avr_adc_handler = adc_handler;
    init_adc(mi_adc);
}


bool adc_ready(){
    return adc_flag;
}

uint16_t adc_getter(void){
    adc_flag = false;
    return adc_value;
}