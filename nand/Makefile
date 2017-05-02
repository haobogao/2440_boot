#Makefile
# Created on: May 1, 2017
#     Author: haobo
SUBDIR = $(shell ls -l | grep ^d | awk '{print $$9}')
CURSRCDOTC = ${wildcard *.c}
CURSRCDOTS = ${wildcard *.s}
CUROBJC = ${patsubst %.c,%.o,$(CURSRCDOTC)}
CUROBJS = ${patsubst %.s,%.o,$(CURSRCDOTS)}
all:$(SUBDIR) $(CUROBJC) $(CUROBJS)
$(CUROBJC):%.o:%.c
	@echo $(CUROBJ)
	$(CC) -c $^ -o $(ROOTDIR)/$(OBJDIR)/$@ $(CFLAGS)
$(CUROBJS):%.o:%.s
	$(CC) -c $^ -o $(ROOTDIR)/$(OBJDIR)/$@ $(CFLAGS)
ECHO:
	@echo $(SUBDIR)