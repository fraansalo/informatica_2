#include "menus.h"
#include "config.h"
#include "gpio_setting.h"
#include "extint_setting.h"
#include "timer_setting.h"
#include "avr_Uart.h"
#include <util/delay.h>

int main(void) {
    system_init();
    uart_puts("BOOT\r\n");
    
    while(1){
        system_run();
    }
}