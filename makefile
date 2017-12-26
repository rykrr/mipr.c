CC=gcc
CFLAGS=-lncurses -g -Wall -Iincludes

OBJDIR=obj
OBJ=$(addprefix $(OBJDIR)/, ax.o cx.o dx.o rx.o qx.o)

micro: obj/micro.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(OBJ)

obj/micro.o: src/micro.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ): $(OBJDIR)/%.o: src/%.c includes/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

hex: src/shex.c
	$(CC) $(CFLAGS) -o hex src/shex.c

clean:
	rm obj/*.o
