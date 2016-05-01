CC = gcc
LD = $(CC)

CFLAGS = -O3 -g
LDFLAGS = $(CFLAGS)

all : poly polyb

clean :
	rm -f *.o poly polyb

poly : poly.o check.o
	$(LD) $(LDFLAGS) -o $@ $^

polyb : polyb.o check.o
	$(LD) $(LDFLAGS) -o $@ $^

check.o: check.h

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
