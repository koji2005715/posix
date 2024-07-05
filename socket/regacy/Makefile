CC = gcc

OPTIMIZE = -O

CFLAGS = $(OPTIMIZE) -Wno-unused-result
LDFLAGS = 

TARGETS = server client

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(TARGETS)

clean::
	rm -f *~ *.o core

distclean::
	rm -f *~ *.o core ${TARGETS}

server: server.o
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@

client: client.o
	$(CC) -o $@ $^ $(LDFLAGS)
	strip $@
