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
void uart_putint(int16_t val){
    char buffer[7]; // suficiente para "-32768"
    itoa(val, buffer, 10);
    uart_puts(buffer);
}


void system_run(void){
    if (timer_tick()) {
        // debounce y captura de botones
        buttons_polling();
    }
    //deshabilitado para testeo de botones y menu
    // if (adc_ready()) {
    //     int16_t tempC = (int16_t)adc_convertCelsius();
    //     control_setCurrentTemp(tempC);
    // }control_update();
    
    menuTable[currentMenu]();
    
    //formato UART para llevar control de los valores de temp.
    // if (timer_seconds()) {
    //     uart_puts("T=");
    //     uart_putint(control_getCurrentTemp());   
    //     uart_puts("  SP=");
    //     uart_putint(control_getTargetTemp());
    //     uart_puts("  H=");
    //     uart_putint(control_isHeating() ? 1 : 0);
    //     uart_puts("  M=");
    //     uart_putint((int16_t)currentMenu);
    //     uart_puts("\r\n");
    // }
}