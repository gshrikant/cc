# Build test infrastructure.

ROOT = $(CURDIR)
LIBDIR = $(ROOT)/lib
BUILDDIR = $(ROOT)/build
INCDIR = $(ROOT)/include
LIBDEPS = $(wildcard $(LIBDIR)/*)

CXXFLAGS = -Wall -fno-strict-aliasing -O0 -ggdb3 -pthread
SOURCES = $(wildcard *.cc)
OBJECTS = $(patsubst %.cc,$(BUILDDIR)/%.o,$(SOURCES))
LDFLAGS = -lgtest

.PHONY: all clean $(LIBDEPS)

all: setup compile $(LIBDEPS) 

setup:
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi;

compile: $(OBJECTS)

$(BUILDDIR)/%.o: %.cc
	@$(CXX) $(CXXFLAGS) -c -I$(INCDIR) -o $@ $^

$(LIBDEPS):
	@echo "     MAKE $(shell basename $@)"
	@$(MAKE) -s -C $@ OUT=$(BUILDDIR) INCLUDE=$(INCDIR) all

clean:
	@$(RM) -r $(BUILDDIR)
	@echo "     RM $(shell basename $(BUILDDIR))"
	@$(RM) runtest
