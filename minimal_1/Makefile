##################################
# stm32 minimal example Makefile
##################################

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CP = arm-none-eabi-objcopy

LKR_SCRIPT = stm32_minimal.ld

CFLAGS  = -c -fno-common -Os -g -mcpu=cortex-m3 -mthumb -Wall -Wpedantic
#LFLAGS  = -nostartfiles -T$(LKR_SCRIPT)
LFLAGS  = -T$(LKR_SCRIPT)
CPFLAGS = -Obinary

all: main.hex

main.o: main.c
	$(CC) $(CFLAGS) -o main.o main.c

main.elf: main.o
	$(LD) $(LFLAGS) -o main.elf main.o

main.bin: main.elf
	$(CP) $(CPFLAGS) main.elf main.bin

main.hex: main.elf
	$(CP) -Oihex main.elf main.hex

clean:
	rm -rf *.o *.elf *.bin *.hex

write:
	./write_bin.sh openocd.cfg main.elf 
