/**
 * TODO: add some cool patterns for the 
 * user to choose from.
 */

#include <stdio.h>
#include <stdbool.h>

#define P_H 5
#define P_W 5

enum {DED, ALV}; //alv papu :v
typedef _Bool cell;

void printPlane(cell plane[P_H][P_W])
{
	for (size_t i = 0; i < P_H; ++i)
	{
		for (size_t j = 0; j < P_W; ++j)
		{
			plane[i][j] == DED ?
				printf(". ") : printf("@ ");
		}
		puts("\n");
	}
}

int isOutOfBounds(size_t x, size_t y)
{
	//avoid using the borders of the plane
	return ((x == 0 || x == P_W-1) ||
		(y == 0 || y == P_H-1));
}

int countNeigh(cell plane[P_H][P_W], int x, int y)
{
	int count = 0;
	if (isOutOfBounds(x, y))
		return (-1);
	/**
	 * I tried some *way* fancier solutions and they
	 * didn't work ._., good 'ol block of if statements
	 * get the job done as always
	 */
	//sides
	if (plane[y][x-1]) ++count;
	if (plane[y][x+1]) ++count;
	if (plane[y-1][x]) ++count;
	if (plane[y+1][x]) ++count;

	//corners
	if (plane[y-1][x-1]) ++count;
	if (plane[y-1][x+1]) ++count;
	if (plane[y+1][x-1]) ++count;
	if (plane[y+1][x+1]) ++count;
	return (count);
}

void copyMatrix(cell const mat_s[P_H][P_W],
	       cell mat_t[P_H][P_W])
{
	for (size_t i = 0; i < P_H; ++i)
	{
		for (size_t j = 0; j < P_W; ++j)
		{
			mat_t[i][j] = mat_s[i][j];
		}
	}
}
	
void nextGen(cell plane[P_H][P_W])
{
	int count = 0;
	cell planecpy[P_H][P_W] = {0};
	for (size_t i = 0; i < P_H; ++i)
	{
		for (size_t j = 0; j < P_W; ++j)
		{
			count = countNeigh(plane, j, i);
			if (count == -1) //exception 
				continue;
			if (plane[i][j] == ALV && //live by neighbours
			    count >= 2)
				planecpy[i][j] = ALV;
			
			else if (plane[i][j] == ALV && // dead by ovepopulation
			    count > 3)
				planecpy[i][j] = DED;
			
			else if (plane[i][j] == ALV && //dead by undepopulation
			    count < 2)
				planecpy[i][j] = DED;
			
			else if (plane[i][j] == DED && //birth
			    count == 3)
				planecpy[i][j] = ALV;
			else
				planecpy[i][j] = DED;
			
		}
	}
	copyMatrix(planecpy, plane);
}

int main()
{
	cell matrix[P_H][P_W] = {
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	};
	int opt = 0;
	while(opt != 'q') {
		printf("\e[2J\e[H"); //clear screen
		nextGen(matrix);
		puts("Next gen: ");
		printPlane(matrix);
		opt = getchar();		
	}
	return (0);
}
