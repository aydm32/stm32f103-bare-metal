TARGET  = firmware
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

CFLAGS  = -mcpu=cortex-m3 -mthumb -O1 -Wall -Wextra -Iinc -nostdlib
LDFLAGS = -mcpu=cortex-m3 -mthumb -nostdlib -nostartfiles \
          -T linker/stm32f103c8.ld

SRCS = src/startup.c src/gpio.c src/main.c src/rcc.c src/uart.c src/spi.c 
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))

all: build/$(TARGET).elf build/$(TARGET).bin
	$(SIZE) build/$(TARGET).elf

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

build/$(TARGET).bin: build/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

flash: build/$(TARGET).bin
	st-flash write build/$(TARGET).bin 0x08000000

build:
	mkdir -p build

clean:
	rm -rf build/
