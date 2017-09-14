#include "LedDriver.h"
#include <avr/io.h>
#include <util/delay.h>

#define LEDPORT PORTE

int main(void) 
{
    //Just here to make sure we can link.
    // Implementation will come later.
    
    LEDPORT.DIR = 0xff; //config entire port for output

    while (1)
    {
        volatile uint8_t* leds = &LEDPORT.OUT;
        LedDriver_Create(leds);
        _delay_ms(1000);
        for(uint8_t i = 1; i < 9; i++) 
        {
            TurnLedOn(leds, i);
            _delay_ms(1000);
        }
    }
    
    return 0;
}
