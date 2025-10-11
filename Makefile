game: game.o
	gcc -o game game.o

game.o: game.c
	gcc -c game.c
