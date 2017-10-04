CPPFLAGS += $(shell pkg-config --cflags cpputest)
CXXFLAGS += -include CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = $(shell pkg-config --libs cpputest)

.PHONY: all
all:
	$(MAKE) check
	$(MAKE) avr

.PHONY: avr
avr:
	$(MAKE) clean
	avr-gcc -Wall -c -mmcu=atxmega128a1 src/LedDriver.c -o src/obj/LedDriver.o

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
	