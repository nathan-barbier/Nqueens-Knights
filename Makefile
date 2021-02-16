CC = gcc
CCOPTS = -Wall

list.o: list.c list.h
	${CC} ${CCOPTS} -c list.c

board.o: board.c board.h
	${CC} ${CCOPTS} -c board.c

board_k.o: board_k.c board_k.h
	${CC} ${CCOPTS} -c board_k.c

nqueens.o: nqueens.c
	${CC} ${CCOPTS} -c nqueens.c

nqueens: nqueens.o board.o list.o board.h list.h item.h
	${CC} ${CCOPTS} -o nqueens nqueens.o board.o list.o
	./nqueens

knights.o: knights.c
	${CC} ${CCOPTS} -c knights.c
	
knights: knights.o board_k.o list.o board_k.h list.h item.h
	${CC} ${CCOPTS} -o knights knights.o board_k.o list.o
	./knights

clean:
	rm *.o nqueens knights
