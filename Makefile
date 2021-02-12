list.o: list.c list.h
	gcc -c list.c

board.o: board.c board.h
	gcc -c board.c

board_k.o: board_k.c board_k.h
	gcc -c board_k.c

nqueens.o: nqueens.c
	gcc -c nqueens.c

nqueens: nqueens.o board.o list.o board.h list.h item.h
	gcc -o nqueens nqueens.o board.o list.o

knights.o: knights.c
	gcc -c knights.c
	
knights: knights.o board_k.o list.o board_k.h list.h item.h
	gcc -o knights knights.o board_k.o list.o
	./knights

clean:
	rm *.o nqueens knights
