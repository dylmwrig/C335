CFLAGS = -g
LDFLAGS = -g

poly: poly.o
	$(CC) $(LDFLAGS) -o poly poly.o dump.o

poly.o: poly.c dump.c
	$(CC) $(CFLAGS) -c poly.c dump.c

dump.o: dump.c
	$(CC) $(CFLAGS) -c dump.c
