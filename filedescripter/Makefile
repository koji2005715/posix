CC = gcc

OPTIMIZE = -O

CFLAGS = $(OPTIMIZE) -Wno-unused-result
LFLAGS = 

OBJS = $(SRCS:.c=.o)

TARGETS = file_basic fd

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(TARGETS)

clean::
	rm -f *~ *.o core

distclean::
	rm -f *~ *.o core ${TARGETS}

fd: fd.o
	$(CC) -o $@ $^ $(LFLAGS)
	strip $@

file_basic: file_basic.o
	$(CC) -o $@ $^ $(LFLAGS)
	strip $@

