#Makefile
# Created on: May 1, 2017
#     Author: haobo
SUBDIR = $(shell ls -l | grep ^d | awk '{if($$9 != "bin") print $$9}')
all:$(SUBDIR)
$(SUBDIR):ECHO
	make -C $@
ECHO:
	@echo $(SUBDIR)