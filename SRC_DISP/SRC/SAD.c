/*
 *Zachary Job
 *SAD.c
 *25/25/25
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../defs.h"

/*
 *Find a match of most fit disparity 
 *
 *@PARAM The left input rank data 
 *@PARAM The right input rank data
 *@PARAM The coordinates of the left PGM to base the calculation
 *@PARAM The size of the window comparison
 *@PARAM The minima 
 *@PARAM The last minima
 *@RETURN The return code
 */
int SAD(struct rankMap *inRML, struct rankMap *inRMR, struct dcoords pixel, int windowSz, double *score, double *lastScore)
{
	/*
	 *Generic iterator
	 *Generic iterator
	 *Generic iterator
	 *Maximum possible score
	 *The return code
	 *The current score
	 *The left value
	 *The right value
	 *The matrix dimensions for the left rank map
	 *The matrix dimensions for the right rank map
	 */
	int i, j, k, maxScore, res, scoreCurr, valL, valR, dimL, dimR, windowHalf;

	/*Ensure odd windowSz above 3*/
	windowSz = windowSz * ((int)(windowSz >= 0));
	windowSz += (int)(windowSz % 2 == 0);
	windowSz += ((int)(windowSz < 3))<<1;
	/*Get half minus precision*/
	windowHalf = windowSz >> 1;
	
	/*Get max score*/
	maxScore = windowSz * windowSz * GRAYTOP;

	/*Get matrix dimensions*/
	dimL = inRML->col * inRML->row;
	dimR = inRMR->col * inRMR->row;

	/*N O T E*/
	/*N O T E*/
	/*The rankmaps start at a half window offset*/
	/*N O T E*/
	/*N O T E*/
	
	/*Iterate the comparator column*/	
	for(i = (int)((int)pixel.x > MAXGRAY) * ((int)pixel.x - MAXGRAY), res = 0, *score = 1, *lastScore = 0; i < (int)pixel.x; i++)
	{
		/*compare ranks*/
		for(j = -1 * windowHalf, scoreCurr = maxScore; j < windowHalf + 1; j++)
		{
			for(k = -1 * windowHalf; k < windowHalf + 1; k++)
			{
				valL = inRML->col * ((int)pixel.y + j) + ((int)pixel.x + k);
				valR = inRMR->col * ((int)pixel.y + j) + (i + k); 
				if(valL < dimL && valR < dimR && valL > 0 && valR > 0)
					scoreCurr -= (int)abs(inRML->elems[valL] - inRMR->elems[valR]);
			}
		}

		/*Assign data if new maxima*/
		if(*score < (double)scoreCurr)
		{
			*lastScore = *score;
			*score = (double)scoreCurr;
			res = i;
		}	
	}

	return res;
}
