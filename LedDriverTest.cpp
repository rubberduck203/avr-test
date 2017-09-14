#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "LedDriver.h"
}

TEST_GROUP(LedDriverCreation)
{
};

TEST(LedDriverCreation, LedsAreOffAfterCreate)
{
  uint8_t virtualLeds = 0xff;
  LedDriver_Create(&virtualLeds);
  LONGS_EQUAL(0, virtualLeds);
}

uint8_t virtualLeds;
TEST_GROUP(LedDriver)
{
  void setup()
  {
    virtualLeds = 0xff;
    LedDriver_Create(&virtualLeds);
  }
};

TEST(LedDriver, TurnOnLED1)
{
  TurnLedOn(&virtualLeds, 1);
  BYTES_EQUAL(0x01, virtualLeds);
}

TEST(LedDriver, TurnOnLed2)
{
  TurnLedOn(&virtualLeds, 2);
  BYTES_EQUAL(0x02, virtualLeds);
}

TEST(LedDriver, ALightAlreadyOnStaysOn)
{
  TurnLedOn(&virtualLeds, 1);
  TurnLedOn(&virtualLeds, 2);
  BYTES_EQUAL(0x03, virtualLeds);
}

TEST(LedDriver, TurnOnSecondByteLed)
{
  TurnLedOn(&virtualLeds, 8);
  BYTES_EQUAL(0x80, virtualLeds);
}

IGNORE_TEST(LedDriver, TurnAllLedsOn)
{
  FAIL("Start Here")
}