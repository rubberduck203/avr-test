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

### Rules for compiling for Tests
$(OBJ)/%.o: $(SRC)/%.c
	gcc -Wall -c $(CFLAGS) $^ -o $@

$(BIN)/AllTests: $(objects) $(testSource)
	g++ $(CPPFLAGS) -Wall $^ -o $@ $(LD_LIBRARIES)

.PHONY: check
check: $(BIN)/AllTests
	$< -c

.PHONY: clean
clean:
	$(RM) $(BIN)/* $(OBJ)/*

### Make predefined variable cheatsheet
# $^ - all prereqs
# $@ - target
# $< - first prereq