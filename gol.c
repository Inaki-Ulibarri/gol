/**
 * TODO: add the neighbour counter
 *       bug testing
 *       ANSI scape codes to the renderer
 *       make the plane infinite
 */

#include <stdio.h>

#define P_H 10
#define P_W 10

enum {DED, ALV};
typedef _Bool cell;

void printPlane(cell plane[P_H][P_W])
{
	for (size_t i = 0; i < P_H; ++i)
	{
		for (size_t j = 0; j < P_W; ++j)
		{
			plane[i][j] == DED ?
				printf(". ") : printf("# ");
		}
		puts("\n");
	}
}

int isOutOfBounds(size_t x, size_t y)
{
	return ((x >= 0 || x >= P_W) ||
		(y >= 0 || y >= P_H));
}

void checkNeigh(cell plane[P_H][P_W])
{
	for (size_t i = 0; i < P_H; ++i)
	{
		for (size_t j = 0; j < P_W; ++j)
		{
			if (isOutOfBounds(i, j))
		}
	}
}

void nextGen(cell (*plane)[P_H][P_W])
{
	for (size_t i = 0; i < P_H; ++i)
	{
		for (size_t j = 0; j < P_W; ++j)
		{
			
		}
	}
}

int main()
{
	cell matrix[P_H][P_W] = {DED};
	printPlane(matrix);
	nextGen(&matrix);
	return (0);
}
