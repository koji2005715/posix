CC = gcc

OPTIMIZE = -O

CFLAGS = $(OPTIMIZE) -Wno-unused-result
LDFLAGS = 

TARGETS = write read

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(TARGETS)

clean::
	rm -f *~ *.o core

distclean::
	rm -f *~ *.o core ${TARGETS}

write: write.o
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@

read: read.o
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@
