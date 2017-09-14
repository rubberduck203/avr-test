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
    virtualLeds = 0xff;
    TurnLedsOff(&virtualLeds);
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

TEST(LedDriver, TurnAllLedsOn)
{
  TurnLedsOn(&virtualLeds);
  BYTES_EQUAL(0xff, virtualLeds);
}

TEST(LedDriver, TurnAllLedsOff)
{
  TurnLedsOff(&virtualLeds);
  BYTES_EQUAL(0x00, virtualLeds);
}

TEST(LedDriver, TurnFirstByteLedOff)
{
  TurnLedsOn(&virtualLeds);
  TurnLedOff(&virtualLeds, 3);

  //0b11111111 0xff 
  //0b00000100 0x06
  //0b11111011 0xfb
  BYTES_EQUAL(0xfb, virtualLeds);
}

TEST(LedDriver, TurnSecondByteLedOff)
{
  TurnLedsOn(&virtualLeds);
  TurnLedOff(&virtualLeds, 5);
  
  //0b11101111
  BYTES_EQUAL(0xef, virtualLeds);
}