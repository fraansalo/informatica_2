#include "config.h"
#include "gpio_setting.h"
#include "extint_setting.h"
#include "timer_setting.h"
#include "adc_setting.h"
#include "control.h"
#include "menus.h"

void system_init(void){
    buttons_init();
    outputs_init();
    timer_init();
    external_interrupt_init();
    adc_init();
    control_reset();
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
}