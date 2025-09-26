#include <stdio.h>
#include <menus.h>
#include <config.h>


void menuIdle(void) {
    Button_t btn = buttons_get();

    if (btn == BTN_SELECT) {
        currentMenu = (currentMenu + 1) % MENU_COUNT;
    }
    if (btn == BTN_ENTER) {
        if (currentMenu == MENU_MANUAL) currentMenu = MENU_MANUAL;
        else if (currentMenu == MENU_REFLOW) currentMenu = MENU_REFLOW;
    }
}

void menuManual(void) {
    manualStateTable[currentManualState]();
}

void menuReflow(void) {
    reflowStateTable[currentManualState]();
}