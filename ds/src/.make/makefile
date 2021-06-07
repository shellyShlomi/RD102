
SUBDIRS := $(wildcard */.)


TOPTARGETS := all

$(TOPTARGETS): $(SUBDIRS) 
$(SUBDIRS):
	@cp $@/Makefile $@/old 
	@cp /home/shelly/git/ds/src/Makefile_for_ds_folders $@/new
	@echo $(shell diff $@/old $@/new)
	@cp $@/new $@/Makefile
	@rm -r -f $@/old $@/new

.PHONY: $(TOPTARGETS) $(SUBDIRS) 

