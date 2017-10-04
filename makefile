CPPFLAGS += $(shell pkg-config --cflags cpputest)
CXXFLAGS += -include CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = $(shell pkg-config --libs cpputest)

build:
	gcc -Wall -c src/LedDriver.c -o src/obj/LedDriver.o

check:
	make build
	g++ $(CPPFLAGS) -Wall -o test/bin/AllTests src/obj/LedDriver.o test/LedTests.cpp test/AllTests.cpp $(LD_LIBRARIES)
	test/bin/AllTests -c