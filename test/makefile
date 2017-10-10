CPPFLAGS += $(shell pkg-config --cflags cpputest)
CXXFLAGS += -include CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = $(shell pkg-config --libs cpputest)

CPPFLAGS += -Imocks/include 

OBJ = obj
BIN = bin
SRC = ../src

# Build the test executable
testSource := $(wildcard *.cpp)
# Include all the source from src, except the entry point
objects := $(patsubst $(SRC)/%.c,$(OBJ)/%.o, $(filter-out $(SRC)/Demo.c, $(wildcard $(SRC)/*.c)))

all: check

### Compile code under test
$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	gcc -Wall -c $(CFLAGS) $(CPPFLAGS) $^ -o $@

### Create test runner executable
$(BIN)/AllTests: $(objects) $(testSource)
	@mkdir -p $(BIN)
	g++ -Wall $(CXXFLAGS) $(CPPFLAGS) $^ -o $@ $(LD_LIBRARIES)

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