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
    BYTES_EQUAL(0x00, leds);
}

TEST(LedDriverTests, TurnAllLedsOff)
{
    leds_t leds = ON;
    LedsOff(&leds);
    BYTES_EQUAL(0xff, leds);
}

TEST(LedDriverTests, TurnLedOneOn)
{
    leds_t leds = OFF;
    LedOn(&leds, 1);
    BYTES_EQUAL(0xFE, leds);
}

TEST(LedDriverTests, TurnLedTwoOn)
{
    leds_t leds = OFF;
    LedOn(&leds, 2);
    BYTES_EQUAL(0xFD, leds);
}

TEST(LedDriverTests, TurnLedSevenOn)
{
    leds_t leds = OFF;
    LedOn(&leds, 7);
    BYTES_EQUAL(0xBF, leds);
}

TEST(LedDriverTests, TurnMultipleLedsOn)
{
    leds_t leds = OFF;
    LedOn(&leds, 1);
    LedOn(&leds, 7);
    BYTES_EQUAL(0xBE, leds);
}

TEST(LedDriverTests, TurnLedThreeOff)
{
    leds_t leds = ON;
    LedOff(&leds, 3);
    BYTES_EQUAL(0x04, leds);
}

TEST(LedDriverTests, TurnLedEightOff)
{
    leds_t leds = ON;
    LedOff(&leds, 8);
    BYTES_EQUAL(0x80, leds);
}

TEST(LedDriverTests, TurnMultipleLedsOff)
{
    leds_t leds = ON;
    LedOff(&leds, 8);
    LedOff(&leds, 2);
    BYTES_EQUAL(0x82, leds);
}