# Makefile for 'cc' - the C99 compiler
CC = gcc
CXX = g++
WARNINGS = -Wall -Wextra -Werror -pedantic -Wswitch-default -Wformat=2
CFLAGS = $(WARNINGS) -std=c99 -fno-strict-aliasing -O2
LDFLAGS = -ldl

TESTLDFLAGS = -pthread -lcompiler -lgtest

# External tools.
RM = rm -rf
MKDIR = mkdir -p

# Project name.
PROG = mycc
TESTAPP = mycc-test

SRCDIR = src
INCDIR = include
TESTDIR = tests
BUILDDIR = build

LIBDIR = $(TESTDIR)/$(BUILDDIR)
TESTLIB = $(BUILDDIR)/libcompiler.a

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
TO_CLEAN := $(PROG) $(OBJECTS) $(BUILDDIR) $(TESTAPP)

LIBOBJS = $(filter-out $(BUILDDIR)/main.o,$(OBJECTS))
TESTOBJS = $(wildcard $(TESTDIR)/build/*.o)

.PHONY: all setup clean test

all: setup $(PROG)

setup:
	@if [ ! -d $(BUILDDIR) ]; then $(MKDIR) -p $(BUILDDIR); fi;
	@echo "     MKDIR $(BUILDDIR)"

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -I$(INCDIR) $(CFLAGS) -c -o $@ $^
	@echo "     CC $^"

$(PROG): $(OBJECTS)
	@$(CC) $(LDFLAGS) $^ -o $@
	@echo "     LD $@"

$(TESTLIB): $(LIBOBJS)
	@$(AR) rcs $@ $^
	@echo "     LD $@"

test: setup $(TESTAPP)

$(TESTAPP): build_tests
	@$(CXX) -L$(BUILDDIR) -L$(LIBDIR) $(TESTOBJS) $(TESTLDFLAGS) -o $(TESTAPP)
	@echo "     LD $@"

build_tests: $(TESTLIB)
	@$(MAKE) -s -C $(TESTDIR) all
	@echo "     MAKE $@"

clean:
	@$(RM) $(TO_CLEAN)
	@echo "     RM $(TO_CLEAN)"
	@$(MAKE) -s -C $(TESTDIR) clean
