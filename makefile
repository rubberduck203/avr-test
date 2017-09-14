#CppUTest
CPPFLAGS += -I$(CPPUTEST_INCLUDE)
CXXFLAGS += -include $(CPPUTEST_INCLUDE)/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_INCLUDE)/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_LIB) -lCppUTest -lCppUTestExt

#AVR
DEVICE = atxmega128a1

.PHONY: all
all:
	make test
	make avr

build:
	gcc -Wall LedDriver.c -c -o bin/LedDriver.o

avr:
	avr-gcc -Wall -mmcu=$(DEVICE) -Os -g -c -std=c11 LedDriver.c -o bin/LedDriver.o
	avr-gcc -Wall -mmcu=$(DEVICE) -Os -g -c -std=c11 Main.c -o bin/Main.o 
	avr-gcc -Wall -mmcu=$(DEVICE) -g bin/LedDriver.o bin/Main.o -o bin/demo.elf
	avr-objcopy -j .text -j .data -O ihex bin/demo.elf bin/demo.hex
	avr-size --format=avr --mcu=$(DEVICE) bin/demo.elf

test:
	make build
	g++ -Wall $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o bin/test bin/LedDriver.o LedDriverTest.cpp AllTests.cpp $(LD_LIBRARIES)
	bin/test -c

clean:
	rm bin/*
