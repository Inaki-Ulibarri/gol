/**
 * TODO: (temptative) add ncurses
 * Docs: https://conwaylife.com/wiki/Main_Page
 *       https://www.youtube.com/watch?v=qJAuyoDt03A
 *       https://en.wikipedia.org/wiki/Conway's_Game_of_Life 
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define P_H 18
#define P_W 20

enum {DED, ALV}; //alv papu :v
typedef _Bool cell;

void printPlane(cell plane[P_H][P_W]);
int  isBorder(size_t x, size_t y);
int  countNeigh(cell plane[P_H][P_W], int x, int y);
void copyMatrix(cell mat_s[P_H][P_W],
		cell mat_t[P_H][P_W]);
void nextGen(cell plane[P_H][P_W]);
void clScr(void);

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		printf("Usage: %s \n"
		       "This is a simple Conway's game of life that will\n"
		       "print an entire period of the eureka pattern three times.\n"
		       "If you want to change the pattern, feel free to edit the source code :D\n"
		       , argv[0]);
		return (0);
	}
	
	cell matrix_eureka[P_H][P_W] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
	        {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};
	const size_t period = 30,
		reps = 3;		
	//print a full period 'reps' times
	for (size_t i = 0; i < (period*reps); ++i)
	{
		clScr();
		printPlane(matrix_eureka);
		nextGen(matrix_eureka);		
		usleep(500000); //0.5 seconds
	}
	return (0);
}

void printPlane(cell plane[P_H][P_W])
{
	for (size_t i = 0; i < P_H; ++i)
	{
		for (size_t j = 0; j < P_W; ++j)
		{
			plane[i][j] == DED ?
				printf("  ") : printf("@ ");
		}
		puts("\n");
	}
}

/**
 * in order for a finite matrix to behave like
 * an infinite plane, you need to create patterns
 * that will fit into the finite matrix and avoid
 * using the borders of it. Because of this,
 * you'll want to stick to oscillators and not 
 * guns or spaceships.
 */
int isBorder(size_t x, size_t y)
{

	return ((x == 0 || x == P_W-1) ||
		(y == 0 || y == P_H-1));
}

int countNeigh(cell plane[P_H][P_W], int x, int y)
{
	int count = 0;
	if (isBorder(x, y))
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

void copyMatrix(cell mat_s[P_H][P_W],
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
			if (count == -1)               //exception 
				continue;
			if (plane[i][j] == ALV &&      //live by neighbours
			    (count == 2 || count == 3))
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
void clScr(void)
{
	printf("\033[2J\033[H ");
 	/**
	 * clear screen with ANSI
	 * scape codes
	 */
}
