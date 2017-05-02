prefix= arm-linux-gnueabi
CC = $(prefix)-gcc
AS = $(prefix)-as
LD = $(prefix)-ld
OBJCP = $(prefix)-objcopy
OBJDUMP=$(prefix)-objdump
SUBDIR = $(shell ls -l | grep ^d | awk '{if( $$9 != "debug" && $$9 != "include") print $$9}' )
DEBUGDIR= $(shell ls -l | grep ^d | awk '{if( $$9 == "debug") print $$9}' )
ROOTDIR = $(shell pwd)
BINFILE= boot.bin
OBJDIR = debug/obj
BINDIR = debug/bin
GCCLIBPATH = -lgcc  -L/usr/lib/gcc-cross/arm-linux-gnueabi/6/
CURSRC = ${wildcard *.c}
CUROBJ = $(patsubst %c,%o,$(CURSRC))
CFLAGS= -I$(ROOTDIR)/include -c  -Os -nostdlib -fno-builtin
export CC BINFILE ROOTDIR OBJDIR BINDIR CFLAGS GCCLIBPATH LD OBJCP OBJDUMP prefix AS
all:$(SUBDIR) $(CUROBJ) $(DEBUGDIR)
$(SUBDIR):ECHO
	make -C $@
$(CUROBJ): %.o:%.c
	$(CC) $(CFLAGS) $^ -o $(ROOTDIR)/$(OBJDIR)/$@
$(DEBUGDIR):ECHO
	make -C $@
ECHO:
	@echo $(SUBDIR)

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/*.bin