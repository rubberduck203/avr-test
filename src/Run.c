#include "LedDriver.h"
#include <avr/io.h>
#include <util/delay.h>

void Setup(void)
{
    PORTE.DIR = 0xff; //config entire port for output
}

void Loop(void) 
{
    //Just here to make sure we can link.
    // Implementation will come later.
    volatile leds_t* leds = &PORTE.OUT;
    LedsOff(leds);
    _delay_ms(1000);
    LedsOn(leds);
    _delay_ms(1000);
}