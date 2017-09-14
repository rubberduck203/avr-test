#CppUTest
CPPUTEST_HOME = /usr/local/Cellar/cpputest/3.8
CPPFLAGS += -I$(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

#AVR
DEVICE = atxmega128a1

build:
	gcc -Wall LedDriver.c -c -o bin/LedDriver.o

avr:
	avr-gcc -Wall -mmcu=$(DEVICE) -Os -g -c LedDriver.c -o bin/LedDriver.o
	avr-gcc -Wall -mmcu=$(DEVICE) -Os -g -c Main.c -o bin/Main.o 
	avr-gcc -Wall -mmcu=$(DEVICE) -g bin/LedDriver.o bin/Main.o -o bin/demo.elf
	avr-objcopy -j .text -j .data -O ihex bin/demo.elf bin/demo.hex
	avr-size --format=avr --mcu=$(DEVICE) bin/demo.elf

test:
	make build
	g++ -Wall $(CPPFLAGS) $(LD_LIBRARIES) $(CXXFLAGS) $(CFLAGS) bin/LedDriver.o LedDriverTest.cpp AllTests.cpp -o bin/test 
	bin/test -c

clean:
	rm bin/*
