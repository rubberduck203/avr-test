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

# make
demo: check $(AVR_BIN)/Demo.hex size

# hex
$(AVR_BIN)/Demo.hex: $(AVR_BIN)/Demo.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@

# elf
$(AVR_BIN)/Demo.elf: $(AVR_OBJDIR)/Demo.o $(AVR_OBJDIR)/LedDriver.o
	avr-gcc $(AVR_CFLAGS) $^ -o $@

# objects
$(AVR_OBJDIR)/%.o: src/%.c
	avr-gcc -c $(AVR_CFLAGS) $^ -o $@

.PHONY: size
size:
	avr-size --format=avr --mcu=$(DEVICE) $(AVR_BIN)/Demo.elf

### Rules for compiling for Tests
$(OBJDIR)/%.o: src/%.c
	gcc -Wall -c $(CFLAGS) $^ -o $@

# Build the test executable
test/bin/AllTests: $(OBJDIR)/LedDriver.o test/LedTests.cpp test/AllTests.cpp
	g++ $(CPPFLAGS) -Wall $^ -o $@ $(LD_LIBRARIES)

.PHONY: check
check: test/bin/AllTests
	$< -c

.PHONY: clean
clean:
	find **/bin/ -type f -delete
	find **/obj/ -type f -delete

### Make predefined variable cheatsheet
# $^ - all prereqs
# $@ - target
# $< - first prereq