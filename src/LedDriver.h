#include <stdint.h>

typedef uint8_t leds_t;

#define OFF 0x00
#define ON 0xff

void LedsOn(volatile leds_t* leds);
void LedsOff(volatile leds_t* leds);
void LedOn(volatile leds_t* leds, uint8_t ledNumber);
void LedOff(volatile leds_t* leds, uint8_t ledNumber);