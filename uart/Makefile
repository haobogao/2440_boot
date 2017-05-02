#Makefile
# Created on: May 1, 2017
#     Author: haobo
SUBDIR = $(shell ls -l | grep ^d | awk '{print $$9}')
CURSRCDOTC = ${wildcard *.c}
CURSRCDOTS = ${wildcard *.S}
CUROBJC = ${patsubst %.c,%.o,$(CURSRCDOTC)}
CUROBJS = ${patsubst %.S,%.o,$(CURSRCDOTS)}
all:$(SUBDIR) $(CUROBJC) $(CUROBJS)
$(CUROBJC):%.o:%.c
	$(CC) -c $^ -o $(ROOTDIR)/$(OBJDIR)/$@ $(CFLAGS)
$(CUROBJS):%.o:%.S
	$(CC) -c $^ -o $(ROOTDIR)/$(OBJDIR)/$@ 
ECHO:
	@echo $(SUBDIR)