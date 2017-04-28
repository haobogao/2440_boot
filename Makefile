prefix= arm-linux-gnueabi
CC = $(prefix)-gcc
AS = $(prefix)-as
LD = $(prefix)-ld
OBJCP = $(prefix)-objcopy
OBJDUMP=$(prefix)-objdump
GCCLIBPATH = -lgcc  -L/usr/lib/gcc-cross/arm-linux-gnueabi/6/
objs:= led.o init.o start.o  main.o uart.o clock.o CMD.o nand1.o printf.o vsprintf.o string.o div64.o ctype.o#IRQ.o
VPATH=./include:./LED/:./init:./uart:./nand
CFLAGS= -I./include -c  -Os -nostdlib -fno-builtin -Os 
edit :$(objs)
	$(LD) -N -Tlinkscp $(objs) -o boot_elf $(GCCLIBPATH)
	$(OBJCP) -O binary -S boot_elf boot.bin
	$(OBJDUMP) -S -D -m arm boot_elf>DEBUG_INFO
	mv ./*.o ./bin
%.o:%.c
	$(CC) $(CFLAGS) $<
start.o:start.s
	$(CC) $(CFLAGS) $<
clean:
	rm -f ./bin/*.o ./*.bin ./*o
