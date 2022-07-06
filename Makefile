SUBDIRS := $(wildcard */.)

define submake
	for d in $(SUBDIRS);                  \
	do                                    \
		$(MAKE) $(1) --directory=$$d; \
	done
endef

all:
	$(call submake,$@)

clean:
	$(call submake,$@)

distclean:
	$(call submake,$@)

.PHONY: all clean distclean $(SUBDIRS)
