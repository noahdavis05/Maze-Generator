CC = gcc


SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

mazeGenerator: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f maze $(OBJS)