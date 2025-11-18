#include "menus.h"
#include "config.h"
#include "gpio_setting.h"
#include "extint_setting.h"
#include "timer_setting.h"

int main(void) {
    system_init();
    while (1) {
        system_run();
        //ejecuta los menus, el polling de botones, el adc, y el handler de ticks.
    }
}