#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H
#include "menus.h"

typedef struct {
    uint16_t remaining;
    bool state;
} timer_t;

void timer_init(void);
bool timer_tick(void);
bool timer_seconds(void);

void timer_start(timer_t *t, uint16_t seconds);
void timer_stop(timer_t *t);
bool timer_expired(timer_t *t);
// void timer_task(void);



#endif