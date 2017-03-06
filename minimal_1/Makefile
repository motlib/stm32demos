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

OBJS=main.o


all: main.hex print_size
	${MAKE} print_size

%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $<

main.elf: ${OBJS}
	$(LD) $(LFLAGS) -o $@ ${OBJS}
	arm-none-eabi-size $@

main.hex: main.elf
	$(CP) -Oihex main.elf main.hex

clean:
	rm -rf *.o *.elf *.bin *.hex
