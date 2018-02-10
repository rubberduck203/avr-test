#ifndef _LEDDRIVER_H_
#define _LEDDRIVER_H_

#include <stdint.h>
#include <avr/io.h>
typedef volatile uint8_t register8_t;
typedef register8_t leds_t;

#define OFF 0xff
#define ON 0x00

void LedsOn(leds_t* leds);
void LedsOff(leds_t* leds);
void LedOn(leds_t* leds, uint8_t ledNumber);
void LedOff(leds_t* leds, uint8_t ledNumber);

#endif