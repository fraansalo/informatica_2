#include "adc_setting.h"


volatile static uint16_t adc_value = 0;
volatile static bool adc_flag = false;

//callback al completar la conversión del canal ADC.
static void mi_adc_handler(void){
    adc_value = leer_ADC(avr_ADC_canal0);
    adc_flag = true;
}


void adc_init(){
    AdcInitStructure_AVR mi_adc;

    mi_adc.channel = avr_ADC_canal0;
    mi_adc.mode = avr_ADC_MODE_Interrupt_request;
    mi_adc.prescaler = avr_ADC_Prescaler_128;
    mi_adc.reference = avr_ADC_REF_AVcc;
    mi_adc.resolution = avr_ADC_RES_10Bit;
    mi_adc.avr_adc_handler = mi_adc_handler;
    init_adc(mi_adc);
}

bool adc_ready(){
    return adc_flag;
}

uint16_t adc_getter(void){
    adc_flag = false;
    return adc_value;
}

float adc_convertCelsius(void){
    return adc_to_celsius(adc_getter());
}