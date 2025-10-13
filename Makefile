CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g -O0

game: game.o utils.o snake.o grid.o inptlib.o
	$(CC) $(CFLAGS) -o game game.o utils.o snake.o grid.o inptlib.o

game.o: game.c utils.h snake.h
	$(CC) $(CFLAGS) -c game.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

snake.o: snake.c snake.h inptlib.h grid.h
	$(CC) $(CFLAGS) -c snake.c

grid.o: grid.c grid.h
	$(CC) $(CFLAGS) -c grid.c

inputlib.o: inptlib.c inptlib.h
	$(CC) $(CFLAGS) -c inptlib.c

clean:
	rm -f game *.o
