#Makefile
# Created on: May 1, 2017
#     Author: haobo
OBJ = *.o
$(ROOTDIR)/$(BINDIR)/$(BINFILE):$(OBJ)
	@echo $(OBJ)
	$(LD) -N -Tlinkscp $(OBJ) -o $(ROOTDIR)/$(OBJDIR)/boot_elf $(GCCLIBPATH)
	$(OBJCP) -O binary -S $(ROOTDIR)/$(OBJDIR)/boot_elf $(ROOTDIR)/boot.bin
	$(OBJDUMP) -S -D -m arm $(ROOTDIR)/$(OBJDIR)/boot_elf>$(ROOTDIR)/debug/bin/DEBUG_INFO