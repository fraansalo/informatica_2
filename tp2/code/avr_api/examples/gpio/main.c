#include "hard.h"


int main (void)

{
	GpioInitStructure_AVR sens;

	sens.port =	SENS_PORT;
	sens.modo = 	avr_GPIO_mode_Input;
	sens.pine s=	SENS_DER_PIN | SENS_DERC_PIN | SENS_CEN_PIN | SENS_IZQC_PIN | SENS_IZQ_PIN;
	init_gpio (sens);

	return 0;
}
