DEVICE = atxmega128a1
CFLAGS = -Wall -Os -mmcu=$(DEVICE) -DF_CPU=32000000UL

OBJDIR = obj
BIN = bin

demo: $(BIN)/Demo.hex size

# hex <- elf
$(BIN)/%.hex: $(BIN)/%.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@

# elf <- [obj]
.PRECIOUS: $(BIN)/%.elf
avrObjects := $(patsubst %.c,$(OBJDIR)/%.o,$(wildcard *.c))
$(BIN)/%.elf: $(avrObjects)
	avr-gcc $(CFLAGS) $^ -o $@

# obj <- c
.PRECIOUS: $(OBJDIR)/%.o
$(OBJDIR)/%.o: %.c
	avr-gcc -c $(CFLAGS) $^ -o $@

.PHONY: size
size:
	avr-size --format=avr --mcu=$(DEVICE) $(BIN)/Demo.elf

.PHONY: clean
clean:
	$(RM) bin/* obj/*

### Make predefined variable cheatsheet
# $^ - all prereqs
# $@ - target
# $< - first prereq