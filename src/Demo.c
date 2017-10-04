#include "LedDriver.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) 
{
    //Just here to make sure we can link.
    // Implementation will come later.
    
    PORTE.DIR = 0xff; //config entire port for output

    while (1)
    {
        volatile leds_t* leds = &PORTE.OUT;
        LedsOff(leds);
        _delay_ms(1000);
        LedsOn(leds);
        _delay_ms(1000);
    }
    
    return 0;
}