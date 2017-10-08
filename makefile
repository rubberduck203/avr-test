DEVICE = atxmega128a1
AVR_CFLAGS = -Wall -Os -mmcu=$(DEVICE) -DF_CPU=32000000UL

OBJDIR = src/obj
AVR_OBJDIR = $(OBJDIR)/avr

BIN = src/bin
AVR_BIN = $(BIN)/avr

demo: check $(AVR_BIN)/Demo.hex size

# hex <- elf
$(AVR_BIN)/%.hex: $(AVR_BIN)/%.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@

# elf <- [obj]
avrObjects := $(patsubst src/%.c,$(AVR_OBJDIR)/%.o,$(wildcard src/*.c))

$(AVR_BIN)/%.elf: $(avrObjects)
	avr-gcc $(AVR_CFLAGS) $^ -o $@

# obj <- c
$(AVR_OBJDIR)/%.o: src/%.c
	avr-gcc -c $(AVR_CFLAGS) $^ -o $@

.PHONY: size
size:
	avr-size --format=avr --mcu=$(DEVICE) $(AVR_BIN)/Demo.elf

.PHONY: check
check:
	$(MAKE) -C test

.PHONY: clean
clean:
	find **/bin/ -type f -delete
	find **/obj/ -type f -delete

### Make predefined variable cheatsheet
# $^ - all prereqs
# $@ - target
# $< - first prereq