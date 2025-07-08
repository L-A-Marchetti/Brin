CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -Werror -pedantic -fstack-protector-strong -std=c99

ifdef BRIN_LITE
    CFLAGS += -DBRIN_LITE
endif

LIBNAME = brin
LIBSTATIC = lib$(LIBNAME).a
LIBOBJECT = $(LIBNAME).o
HEADER = $(LIBNAME).h

PREFIX ?= /usr/local
INCLUDEDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

.PHONY: all clean test install uninstall format

all: $(LIBSTATIC)

$(LIBSTATIC): $(LIBOBJECT)
	$(AR) rcs $@ $^

$(LIBOBJECT): $(LIBNAME).c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

test: all test.c
	$(CC) $(CFLAGS) test.c -o test -l$(LIBNAME)

install: all
	mkdir -p $(INCLUDEDIR)
	mkdir -p $(LIBDIR)
	cp $(HEADER) $(INCLUDEDIR)
	cp $(LIBSTATIC) $(LIBDIR)

uninstall:
	rm -f $(INCLUDEDIR)/$(HEADER)
	rm -f $(LIBDIR)/$(LIBSTATIC)

format:
	@astyle --recursive --max-code-length=70 --suffix=none --style=allman *.c *.h

clean:
	rm -f *.o *.a test
