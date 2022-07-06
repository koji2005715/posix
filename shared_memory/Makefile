CC = gcc

OPTIMIZE = -O

CFLAGS = $(OPTIMIZE) -Wno-unused-result
LFLAGS = -lncurses -lrt -lpthread

OBJS = $(SRCS:.c=.o)

TARGETS = ex01 ex02

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(TARGETS)

clean::
	rm -f *~ *.o core

distclean::
	rm -f *~ *.o core $(TARGETS)

ex01: ex01.o
	$(CC) -o $@ $^ $(LFLAGS)
	strip $@

ex02: ex02.o
	$(CC) -o $@ $^ $(LFLAGS)
	strip $@
