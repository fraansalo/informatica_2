#ifndef CONFIG_H
#define CONFIG_H

#define TEMP_PREHEAT_TARGET 140

#define TEMP_SOAK_TARGET 160
#define TIM_SOAK_TARGET 90

#define TEMP_RAMP_TARGET 210

#define TEMP_PEAK_TARGET 225
#define TIM_PEAK_TARGET 35

#define TEMP_COOLED 24
#define TIM_COOLED 50

#define DEBOUNCE_DELAY_MS 30
#define TIM_MANUAL_HOLD 50
#define TEMP_HYSTERESIS 5

void system_init(void);
void system_run(void);

#endif