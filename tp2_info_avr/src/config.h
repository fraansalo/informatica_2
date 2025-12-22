#ifndef CONFIG_H
#define CONFIG_H

#define TEMP_PREHEAT_TARGET 60 //140

#define TEMP_SOAK_TARGET 80//160
#define TIM_SOAK_TARGET 10//90

#define TEMP_RAMP_TARGET 130 //210

#define TEMP_PEAK_TARGET 145 //225
#define TIM_PEAK_TARGET 10//35

#define TEMP_COOLED 24
#define TIM_COOLED 10 //50

#define DEBOUNCE_DELAY_MS 30
#define TIM_MANUAL_HOLD 10 //50
#define TEMP_HYSTERESIS 5

/*
 * Prototipo de funcion system_init - Función que inicializa todos los módulos de nuestro programa en el AVR.
 * @params: {void} 
 * @returns: {void}
 */
void system_init(void);

/*
 * Prototipo de funcion system_run - Función que establece el loop principal de funcionamiento.
 * @params: {void} 
 * @returns: {void}
 */
void system_run(void);


#endif