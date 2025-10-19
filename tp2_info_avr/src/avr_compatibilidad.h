#ifndef COMPAT_AVR_H
#define COMPAT_AVR_H

#include <avr/io.h>

#if defined(__AVR_ATmega328P__)

#ifndef TCCR0
#define TCCR0 TCCR0B
#endif

#ifndef OCR0 
#define OCR0 OCR0A
#endif

#ifndef OCR1C
#define OCR1C OCR1A
#endif

#ifndef TIMSK
#define TIMSK TIMSK0
#endif

#ifndef TCCR2
#define TCCR2 TCCR2B
#endif

#endif // __AVR_ATmega328P__

#endif // COMPAT_AVR_H
