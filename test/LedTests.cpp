#include <stdint.h>
#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "../src/LedDriver.h"
}

TEST_GROUP(LedDriverTests)
{
};

TEST(LedDriverTests, TurnAllLedsOn)
{
    leds_t leds = OFF;
    LedsOn(&leds);
    BYTES_EQUAL(ON, leds);
}

TEST(LedDriverTests, TurnAllLedsOff)
{
    leds_t leds = ON;
    LedsOff(&leds);
    BYTES_EQUAL(OFF, leds);
}

TEST(LedDriverTests, TurnLedOneOn)
{
    leds_t leds = OFF;
    LedOn(&leds, 1);
    BYTES_EQUAL(0x01, leds);
}