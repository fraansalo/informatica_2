#include "menus.h"
#include "gpio_setting.h"
#include "timer_setting.h"
#include <avr/interrupt.h>
#include "avr_Timers.h"

static volatile bool tick_flag = false;
static volatile uint16_t tick_count = 0;
static volatile bool seconds_flag = false;

void systick_handler(void){
    tick_flag = true;
    tick_count++;
    if(tick_count >= 100){
        tick_count = 0;
        seconds_flag = true;
    }
}

void timer_init(void){
    SystickInitStructure_AVR systick;
    systick.timernumber = avr_TIM0;
    systick.time_ms = 10;
    systick.avr_systick_handler = systick_handler; //funcion que se ejecuta al finalizar la conversión

    init_Systick_timer(systick);
    sei();  //interrupciones globales
}