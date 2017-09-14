#CppUTest
CPPFLAGS += -I$(CPPUTEST_INCLUDE)
CXXFLAGS += -include $(CPPUTEST_INCLUDE)/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_INCLUDE)/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_LIB) -lCppUTest -lCppUTestExt

#AVR
DEVICE = atxmega128a1
AVR_FLAGS = -Wall -mmcu=$(DEVICE)
AVR_CFLAGS = $(AVR_FLAGS) -Os -g -c -std=c11

.PHONY: all
all:
	make test
	make avr

build:
	gcc -Wall LedDriver.c -c -o bin/LedDriver.o

avr:
	avr-gcc $(AVR_CFLAGS) LedDriver.c -o bin/LedDriver.o
	avr-gcc $(AVR_CFLAGS) Main.c -o bin/Main.o 
	avr-gcc $(AVR_FLAGS) -g bin/LedDriver.o bin/Main.o -o bin/demo.elf
	avr-objcopy -j .text -j .data -O ihex bin/demo.elf bin/demo.hex
	avr-size --format=avr --mcu=$(DEVICE) bin/demo.elf

test:
	make build
	g++ -Wall $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o bin/test bin/LedDriver.o LedDriverTest.cpp AllTests.cpp $(LD_LIBRARIES)
	bin/test -c

clean:
	rm bin/*
