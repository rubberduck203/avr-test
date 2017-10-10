#include "LedDriver.h"
#include <avr/io.h>
#include <util/delay.h>

volatile leds_t* LedRegister;

void Setup(void)
{
    PORTE.DIR = 0xff; //config entire port for output
    LedRegister = &PORTE.OUT;
}

void Loop(void) 
{
    //Just here to make sure we can link.
    // Implementation will come later.
    LedsOff(LedRegister);
    _delay_ms(1000);
    LedsOn(LedRegister);
    _delay_ms(1000);
}