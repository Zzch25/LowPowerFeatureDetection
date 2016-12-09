/*
 *Zachary Job
 *rankTransform.c
 *25/25/25
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef __CYGWIN__
	#include <netpbm/pam.h>
#elif __linux
	#include <pam.h>
#endif

#include "../defs.h"

/*
 *Transform image data to a rank transform
 *
 *@PARAM The left input PGM data 
 *@PARAM The right input PGM data
 *@PARAM The rank map for the left input 
 *@PARAM The rank map for the right input
 *@PARAM The size of the window comparison
 *@RETURN The return code
 */
int rankTransform(struct PGMStat *inPGML, struct PGMStat *inPGMR, struct rankMap *outRML, struct rankMap *outRMR, int windowSz)
{
	/*
	 *The return status
	 *Generic iterator
	 *Generic iterator
	 *Generic iterator
	 *Generic iterator
	 *The pixels to travel to a window corner
	 *The max row to process
	 *The max column to process 
	 */
	int res, i, j, k, l, windowHalf, minRow, minCol;

	res = 0;

	windowHalf = windowSz >> 1;
	
	/*Set the generic row/column information*/
	outRML->row = inPGML->row;
	outRML->col = inPGML->col;
	outRMR->row = inPGMR->row;
	outRMR->col = inPGMR->col;

	/*Get the maximum to process row and column wise*/
	minRow = fmin(inPGML->row, inPGMR->row);
	minRow -= windowHalf;
	minCol = fmin(inPGML->col, inPGMR->col);
	minCol -= windowHalf;

	/*Alloc the element arrays in the output structs*/
	if((outRML->elems = malloc(sizeof(int) * (outRML->row * outRML->col))) == 0)
		res = -1;
	else if((outRMR->elems = malloc(sizeof(int) * (outRMR->row * outRMR->col))) == 0)
		res = -1;

	memset(outRML->elems, 0, outRML->row * outRML->col * sizeof(int));
	memset(outRMR->elems, 0, outRMR->row * outRMR->col * sizeof(int));

	if(res == 0)
	{
		/*Iterate the window assinging rank to the primary*/
		for(i = windowHalf; i < minRow; i++)
		{
			for(j = windowHalf; j < minCol; j++)
			{
				for(k = -1 * windowHalf; k < windowHalf + 1; k++)
				{
					for(l = -1 * windowHalf; l < windowHalf + 1; l++)
					{
						if(k != 0 && l != 0)
						{
							outRML->elems[i * outRML->col + j] += (int)(inPGML->gElems[i * inPGML->col + j] > inPGML->gElems[(i + l) * inPGML->col + j + k]);
							outRMR->elems[i * outRMR->col + j] += (int)(inPGMR->gElems[i * inPGMR->col + j] > inPGMR->gElems[(i + l) * inPGMR->col + j + k]);
						}
					}
				}
			}
		}
	}

	return res;
}
