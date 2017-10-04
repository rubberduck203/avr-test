CPPFLAGS += $(shell pkg-config --cflags cpputest)
CXXFLAGS += -include CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = $(shell pkg-config --libs cpputest)

DEVICE = atxmega128a1
AVR_CFLAGS = -Wall -Os -mmcu=$(DEVICE) -DF_CPU=32000000UL

OBJDIR = src/obj
AVR_OBJDIR = $(OBJDIR)/avr

BIN = src/bin
AVR_BIN = $(BIN)/avr

.PHONY: all
all:
	$(MAKE) check
	$(MAKE) avr

.PHONY: avr
avr:
	avr-gcc -c $(AVR_CFLAGS) src/LedDriver.c -o $(AVR_OBJDIR)/LedDriver.o
	avr-gcc -c $(AVR_CFLAGS) src/Demo.c -o $(AVR_OBJDIR)/Demo.o
	avr-gcc $(AVR_CFLAGS) $(AVR_OBJDIR)/LedDriver.o $(AVR_OBJDIR)/Demo.o -o $(AVR_BIN)/Demo.elf
	avr-objcopy -j .text -j .data -O ihex $(AVR_BIN)/Demo.elf $(AVR_BIN)/Demo.hex
	avr-size --format=avr --mcu=$(DEVICE) $(AVR_BIN)/Demo.elf
	
.PHONY: build
build:
	gcc -Wall -c src/LedDriver.c -o $(OBJDIR)/LedDriver.o

.PHONY: check
check:
	$(MAKE) build
	g++ $(CPPFLAGS) -Wall -o test/bin/AllTests $(OBJDIR)/LedDriver.o test/LedTests.cpp test/AllTests.cpp $(LD_LIBRARIES)
	test/bin/AllTests -c

.PHONY: clean
clean:
	$(RM) **/bin/* **/obj/*
	