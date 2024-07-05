CC = g++
CXX = g++

OPTIMIZE = -O

CFLAGS = $(OPTIMIZE)
CXXFLAGS = $(OPTIMIZE)
LDFLAGS = -lpthread


TARGETS = ex01 ex02 ex03 ex04 fuga

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(TARGETS)

clean::
	rm -f *~ *.o core

distclean::
	rm -f *~ *.o core ${TARGETS}

ex01: ex01.o slowPrint.o
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@

ex02: ex02.o slowPrint.o
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@

ex03: ex03.o slowPrint.o Monitor.o
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@

ex04: ex04.o slowPrint.o
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@

fuga: fuga.o slowPrint.o
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@

slowPrint.o: slowPrint.h
Monitor.o: Monitor.h
