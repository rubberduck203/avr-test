#include "LedDriver.h"
#include <avr/io.h>
#include <util/delay.h>

leds_t* LedRegister;

void Setup(void)
{
    PORTE.DIR = 0xff; //config entire port for output
    LedRegister = &PORTE.OUT;
}

void Loop(void) 
{
    LedsOff(LedRegister);
    _delay_ms(1000);
    LedsOn(LedRegister);
    _delay_ms(1000);
}