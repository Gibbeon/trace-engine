#SUBDIRS := $(wildcard */.)
SUBDIRS := ./tecore
build: $(SUBDIRS)
	
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: build $(SUBDIRS)