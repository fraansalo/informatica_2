#include "timer_setting.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile bool tick_flag = false;
static volatile uint16_t tick_count = 0;
static volatile bool seconds_flag = false;

// static void systick_handler(void){
//     tick_flag = true;
//     tick_count++;
//     if(tick_count >= 100){
//         tick_count = 0;
//         seconds_flag = true;
//     }
// }

ISR(TIMER0_COMPA_vect){
    tick_flag = true;
    tick_count++;

    if (tick_count >= 100){     // 100 ticks de 10ms ≈ 1 segundo
        tick_count = 0;
        seconds_flag = true;
    }
    
}


void timer_init(void){
    // SystickInitStructure_AVR systick;
    // systick.timernumber = avr_TIM0;
    // systick.time_ms = 10;
    // systick.avr_systick_handler = systick_handler; //funcion que se ejecuta al finalizar la conversión
    // init_Systick_timer(systick);
    // sei();  //interrupciones globales
    

    // Timer0 → CTC con OCR0A
    // Frec timer: 16MHz / 1024 = 15625 Hz
    // 10ms = 15625 * 0.01 = 156 ciclos → OCR0A = 155

    TCCR0A = (1 << WGM01);          // Modo CTC
    TCCR0B = 0;                     // Prescaler off
    OCR0A = 155;                    // 10 ms

    TIMSK0 = (1 << OCIE0A);         // Habilitar interrupción compare match A

    TCCR0B = (1 << CS02) | (1 << CS00); // Prescaler 1024

    sei();
}



bool timer_tick(){  //ajuste de flags para indicar que se cumplio un ciclo.
    if(tick_flag){
        tick_flag = false;
        return true;
    }return false;
}

bool timer_seconds(void){ ////ajuste de flags para indicar que se cumplio un tiempo seteado.
    if(seconds_flag){
        seconds_flag = false;
        return true;
    }return false;
}

