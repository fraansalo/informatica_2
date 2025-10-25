#include "extint_setting.h"
#include <avr/interrupt.h>

//Callback de INT0
static void extint0_handler(void){
    buttons_set(BTN_ENTER);
}

//Callback de INT1
static void extint1_handler(void){
    buttons_set(BTN_SELECT);
}

void external_interrupt_init(void){
    ExternalInterruptInitStructure_AVR mi_extint;
    
    mi_extint.interrupcion = avr_INT0;
    mi_extint.modo = avr_ext_int_lowlevel;
    mi_extint.avr_ext_interrupt_handler = extint0_handler;
    init_extern_interrupt(mi_extint);
    
    mi_extint.interrupcion = avr_INT1;
    mi_extint.modo = avr_ext_int_lowlevel;
    mi_extint.avr_ext_interrupt_handler = extint1_handler;
    init_extern_interrupt(mi_extint);
}
