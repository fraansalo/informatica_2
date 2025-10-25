#include "menus.h"
#include "config.h"
#include "gpio_setting.h"
#include "extint_setting.h"
#include "timer_setting.h"


int main(void) {
    system_init(); //a definir cuando se haga el seteo de la API.
    while (1) {
        menuTable[currentMenu]();  // ejecuta el handler del menú actual
    }
}