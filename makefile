CPPFLAGS += $(shell pkg-config --cflags cpputest)
CXXFLAGS += -include CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = $(shell pkg-config --libs cpputest)

check:
	g++ $(CPPFLAGS) -Wall test/LedTests.cpp test/AllTests.cpp -o test/bin/AllTests $(LD_LIBRARIES)
	test/bin/AllTests -c