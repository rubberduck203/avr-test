#include <stdint.h>

typedef uint8_t leds_t;

#define OFF 0x00
#define ON 0xff

void LedsOn(leds_t* leds);
void LedsOff(leds_t* leds);
void LedOn(leds_t* leds, uint8_t ledNumber);
void LedOff(leds_t* leds, uint8_t ledNumber);