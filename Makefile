CC = egcc
CFLAGS = -O6

bitrev2.h: gen.c 
	$(CC) gen.c -o gen -lm
	gen bitrev2.h

bitrev.o: bitrev.c bitrev2.h
	$(CC) $(CFLAGS) -c bitrev.c 

example: bitrev.o example.c
	$(CC) $(CFLAGS) example.c bitrev.o -o example

clean:
	rm -f bitrev.h bitrev2.h gen example bitrev.o
