#include "LedDriver.h"
#include <avr/io.h>
#include <util/delay.h>

#define LEDPORT PORTE

int main(void) 
{
    //Just here to make sure we can link.
    // Implementation will come later.
    
    LEDPORT.DIR = 0xff; //config entire port for output

    // Now, just for fun, we toggle all LEDs, again and again and again...
    while (1)
    {
        LEDPORT.OUTTGL = 0xff;
        _delay_ms(1000);
    }
    
    return 0;
}
