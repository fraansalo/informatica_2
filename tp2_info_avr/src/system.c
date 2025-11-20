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
    external_interrupt_init();
    adc_init();
    control_reset();

    UartInitStructure uart_cfg;
    uart_cfg.baudrate = 9600;
    uart_cfg.uart_port = avr_uart0;   
    init_uart_avr(uart_cfg);
}
static void uart_putint(int16_t val){
    char buf[8];
    int8_t i = 0;

    if (val < 0){
        uart_putc('-');
        val = -val;
    }
    do {
        buf[i++] = (val % 10) + '0';
        val /= 10;
    } while(val && i < 7);

    while(i--){
        uart_putc(buf[i]);
    }
}

void system_run(void){
    
    if (timer_tick()) {
        // debounce y captura de botones
        buttons_polling();
    }
    if (adc_ready()) {
        int16_t tempC = (int16_t)adc_convertCelsius();
        control_setCurrentTemp(tempC);
    }control_update();
    
    menuTable[currentMenu]();

    if (timer_seconds()) {
        uart_puts("T=");
        uart_putint(control_getCurrentTemp());   
        uart_puts("  SP=");
        uart_putint(control_getTargetTemp());
        uart_puts("  H=");
        uart_putint(control_isHeating() ? 1 : 0);
        uart_puts("  M=");
        uart_putint((int16_t)currentMenu);
        uart_puts("\r\n");
    }
}