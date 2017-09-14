#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "LedDriver.h"
}

uint8_t virtualLeds;
TEST_GROUP(LedDriver)
{
  void setup()
  {
    virtualLeds = 0x00;
    TurnLedsOff(&virtualLeds);
  }
};

TEST(LedDriver, TurnOnLED1)
{
  TurnLedOn(&virtualLeds, 1);
  BYTES_EQUAL(0xfe, virtualLeds);
}

TEST(LedDriver, TurnOnLed2)
{
  TurnLedOn(&virtualLeds, 2);
  BYTES_EQUAL(0xfd, virtualLeds);
}

TEST(LedDriver, ALightAlreadyOnStaysOn)
{
  TurnLedOn(&virtualLeds, 1);
  TurnLedOn(&virtualLeds, 2);
  BYTES_EQUAL(0xfc, virtualLeds);
}

TEST(LedDriver, TurnOnSecondByteLed)
{
  TurnLedOn(&virtualLeds, 8);
  BYTES_EQUAL(0x7f, virtualLeds);
}

TEST(LedDriver, TurnAllLedsOn)
{
  TurnLedsOn(&virtualLeds);
  BYTES_EQUAL(0x00, virtualLeds);
}

TEST(LedDriver, TurnAllLedsOff)
{
  TurnLedsOff(&virtualLeds);
  BYTES_EQUAL(0xff, virtualLeds);
}

TEST(LedDriver, TurnFirstByteLedOff)
{
  TurnLedsOn(&virtualLeds);
  TurnLedOff(&virtualLeds, 3);

  //0b00000100
  BYTES_EQUAL(0x04, virtualLeds);
}

TEST(LedDriver, TurnSecondByteLedOff)
{
  TurnLedsOn(&virtualLeds);
  TurnLedOff(&virtualLeds, 5);
  
  //0b11101111
  BYTES_EQUAL(0x10, virtualLeds);
}