
SUBDIRS := $(wildcard */.)

OBJ = ../obj


TOPTARGETS := all

$(TOPTARGETS): $(SUBDIRS) 
$(SUBDIRS):
	@mkdir -p $(OBJ)/$@ 
	$(MAKE) -C $@ $(MAKECMDGOALS) so	


.PHONY: $(TOPTARGETS) $(SUBDIRS) 
