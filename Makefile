list.o: list.c list.h
	gcc -c list.c

board.o: board.c board.h
	gcc -c board.c

nqueens: nqueens.c board.c list.c board.h list.h item.h
	gcc -o nqueens nqueens.c board.c list.c

knights: knights.c board_k.c list.c board_k.h list.h item.h
	gcc -o knights knights.c board.c list.c

clean:
	rm *.o nqueens knights
