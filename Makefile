prefix= arm-linux-gnueabi
CC = $(prefix)-gcc
AS = $(prefix)-as
LD = $(prefix)-ld
OBJCP = $(prefix)-objcopy
OBJDUMP=$(prefix)-objdump
objs:= led.o init.o start.o
VPATH=./include:./LED/:./init
CFLAGS= -I./include -c -Os
edit :$(objs)
	$(LD) -N -Tlinkscp1 $(objs) -o boot_elf
	$(OBJCP) -O binary -S boot_elf boot.bin
	$(OBJDUMP) -S -D -m arm boot_elf>DEBUG_INFO
	mv ./*.o ./bin 
%.o:%.c
	$(CC) $(CFLAGS) $< 
start.o:start.s
	$(CC) $(CFLAGS) $< 
clean:
	rm -f ./bin/*.o ./*.bin


