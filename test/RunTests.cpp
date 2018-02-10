#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "../src/Run.h"
}

TEST_GROUP(RunTests)
{
};

TEST(RunTests, SetupForOutput)
{
    Setup();
    BYTES_EQUAL(0xff, DDRD);
}

TEST(RunTests, LedsRegisterAssignedToPORTD)
{
    Setup();
    POINTERS_EQUAL(&PORTD, LedRegister);
}
