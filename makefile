CC=gcc
CFLAGS=-lncurses -g -Wall

micro: obj/micro.o obj/ax.o obj/dx.o
	$(CC) $(CFLAGS) -o micro obj/micro.o obj/ax.o obj/dx.o

obj/micro.o: micro.c
	$(CC) $(CFLAGS) -c micro.c -o obj/micro.o

obj/ax.o: ax.c ax.h
	$(CC) $(CFLAGS) -c ax.c -o obj/ax.o

obj/dx.o: dx.c dx.h
	$(CC) $(CFLAGS) -c dx.c -o obj/dx.o

hex:
	$(CC) $(CFLAGS) -o hex shex.c

clean:
	rm obj/*.o
