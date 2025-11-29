#include "config.h"
#include "gpio_setting.h"
#include "extint_setting.h"
#include "timer_setting.h"
#include "adc_setting.h"
#include "control.h"
#include "menus.h"
#include "avr_Uart.h"

void system_init(void){
    buttons_init();
    outputs_init();
    timer_init();
    // external_interrupt_init();
    adc_init();
    control_reset();
    uart_init(UART_BAUD_SELECT(9600, F_CPU));

}

//funcion para imprimir variables en UART.



void system_run(void){
    if (timer_tick()) {
        buttons_polling();
    }
    if (adc_ready()) {
        int16_t tempC = (int16_t)adc_convertCelsius();
        control_setCurrentTemp(tempC);
    }
    menuTable[currentMenu]();
}