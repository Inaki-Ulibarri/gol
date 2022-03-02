CC = gcc
CFLAGS = -Wall -Wextra -pedantic
gol: gol.c
	${CC} ${CFLAGS} -o gol gol.c
