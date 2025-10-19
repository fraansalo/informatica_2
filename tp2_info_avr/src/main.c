#include "menus.h"
#include "config.h"


int main(void) {
    system_init(); //a definir cuando se haga el seteo de la API.
    while (1) {
        menuTable[currentMenu]();  // ejecuta el handler del menú actual
    }
}