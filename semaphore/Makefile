CC = gcc

OPTIMIZE = -O

CFLAGS = $(OPTIMIZE)
LFLAGS = -lpthread

OBJS = $(SRCS:.c=.o)

TARGETS = ex01 ex02 ex03 ex04 unlock fuga

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(TARGETS)

clean::
	rm -f *~ *.o core

distclean::
	rm -f *~ *.o core ${TARGETS}

ex01: ex01.o slowPrint.o
	$(CC) -o $@ $^ $(LFLAGS)
	strip $@

ex02: ex02.o slowPrint.o
	$(CC) -o $@ $^ $(LFLAGS)
	strip $@

ex03: ex03.o slowPrint.o
	$(CC) -o $@ $^ $(LFLAGS)
	strip $@

ex04: ex04.o slowPrint.o
	$(CC) -o $@ $^ $(LFLAGS)
	strip $@

unlock: unlock.o
	$(CC) -o $@ $^ $(LFLAGS)
	strip $@

fuga: fuga.o slowPrint.o
	$(CC) -o $@ $^ $(LFLAGS)
	strip $@


