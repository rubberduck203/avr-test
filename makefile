CPPFLAGS += $(shell pkg-config --cflags cpputest)
CXXFLAGS += -include CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = $(shell pkg-config --libs cpputest)

DEVICE = atxmega128a1
AVR_CFLAGS = -Wall -Os -mmcu=$(DEVICE) -DF_CPU=32000000UL

.PHONY: all
all:
	$(MAKE) check
	$(MAKE) avr

.PHONY: avr
avr:
	avr-gcc -c $(AVR_CFLAGS) src/LedDriver.c -o src/obj/avr/LedDriver.o
	avr-gcc -c $(AVR_CFLAGS) src/Demo.c -o src/obj/avr/Demo.o
	avr-gcc $(AVR_CFLAGS) src/obj/avr/LedDriver.o src/obj/avr/Demo.o -o src/bin/avr/Demo.elf
	avr-objcopy -j .text -j .data -O ihex src/bin/avr/Demo.elf src/bin/avr/Demo.hex
	avr-size --format=avr --mcu=$(DEVICE) src/bin/avr/Demo.elf
	
.PHONY: build
build:
	gcc -Wall -c src/LedDriver.c -o src/obj/LedDriver.o

.PHONY: check
check:
	$(MAKE) build
	g++ $(CPPFLAGS) -Wall -o test/bin/AllTests src/obj/LedDriver.o test/LedTests.cpp test/AllTests.cpp $(LD_LIBRARIES)
	test/bin/AllTests -c

.PHONY: clean
clean:
	$(RM) **/bin/* **/obj/*
	