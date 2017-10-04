CPPFLAGS += $(shell pkg-config --cflags cpputest)
CXXFLAGS += -include CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = $(shell pkg-config --libs cpputest)

check:
	g++ $(CPPFLAGS) $(LD_LIBRARIES) test/AllTests.cpp -o test/bin/AllTests
	test/bin/AllTests