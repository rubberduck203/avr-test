CPPFLAGS += $(shell pkg-config --cflags cpputest)
CXXFLAGS += -include CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = $(shell pkg-config --libs cpputest)

OBJ = obj
BIN = bin
SRC = ../src

# Build the test executable
testSource := $(wildcard *.cpp)
objects := $(OBJ)/LedDriver.o

all: check

### Compile code under test
$(OBJ)/%.o: $(SRC)/%.c
	gcc -Wall -c $(CFLAGS) $^ -o $@

### Create test runner executable
$(BIN)/AllTests: $(objects) $(testSource)
	g++ -Wall $(CPPFLAGS) $^ -o $@ $(LD_LIBRARIES)

.PHONY: check
check: $(BIN)/AllTests
	$< -c -v 

.PHONY: clean
clean:
	$(RM) $(BIN)/* $(OBJ)/*

### Make predefined variable cheatsheet
# $^ - all prereqs
# $@ - target
# $< - first prereq