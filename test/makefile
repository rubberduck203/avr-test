CPPUTEST_HOME = /usr/local/Cellar/cpputest/3.8/
CPPFLAGS += -I$(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

test:
	g++ -Wall $(CPPFLAGS) $(LD_LIBRARIES) $(CXXFLAGS) $(CFLAGS) helloTest.cpp AllTests.cpp -o bin/test 

clean:
	rm bin/*
