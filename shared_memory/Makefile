CC = gcc

OPTIMIZE = -O

CFLAGS = $(OPTIMIZE) -Wno-unused-result
LDFLAGS = -lncurses -lrt -lpthread

TARGETS = ex01 ex02

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(TARGETS)

clean::
	rm -f *~ *.o core

distclean::
	rm -f *~ *.o core $(TARGETS)

ex01: ex01.o
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@

ex02: ex02.o
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@
