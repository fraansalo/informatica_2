#include <stdio.h>
#include <stdint.h>
#include "variables.h"
#include "config.h"

int main(void) {
    system_init();  // GPIO, timers, etc.
    while (1) {
        menuTable[currentMenu]();  // ejecuta el handler del menú actual
    }
}