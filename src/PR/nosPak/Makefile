#!smake
include $(ROOT)/usr/include/make/PRdefs

SUBDIRS=lib test man src
COMMONPREF = nosPak

default:
	for i in $(SUBDIRS) ; do \
	    echo ==== $$i === ; \
	    cd $$i ; \
	    $(MAKE) default; \
	    cd .. ; \
	done

install:
	$(INSTALL) -m 444 -F /usr/src/PR/nosPak Makefile README
	for i in $(SUBDIRS) ; do \
	    echo ==== $$i === ; \
	    cd $$i ; \
	    $(MAKE) install; \
	    cd .. ; \
	done

$(COMMONTARGS): $(_FORCE)
	$(SUBDIRS_MAKERULE)

include $(COMMONRULES)


