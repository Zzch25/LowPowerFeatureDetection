/*
 *Zachary Job
 *readyViewPairs.c
 *25/25/25
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __CYGWIN__
	#include <netpbm/pam.h>
#elif __linux
	#include <pam.h>
#endif

#include "../defs.h"

/*
 *Sets the disparity map information for view pairs
 *
 *@PARAM: The map data
 *@RETURN: End of execution state
 */
int readyViewPairs(struct grayInfo grayData)
{
	/*
	 *
	 *The return code
	 *Generic iterator
	 *The input image grays
	 */
	int res, i, minCol, minRow, currViewPair;

	res = 0;
	
	for(i = 0, currViewPair = 0; i < grayData.sz; i++)
	{
		if((grayData.type)[i] == TYPEVIEW)
		{
			(grayData.viewPairInfo)[currViewPair].elemL.maxVal = MAXGRAY;
			(grayData.viewPairInfo)[currViewPair].elemR.maxVal = MAXGRAY;
			
			minRow = fmin((grayData.viewPairInfo)[currViewPair].elemL.row, (grayData.viewPairInfo)[currViewPair].elemR.row);
			minCol = fmin((grayData.viewPairInfo)[currViewPair].elemL.col, (grayData.viewPairInfo)[currViewPair].elemR.col);

			if(minRow > 0 && minCol > 0)
			{
				(grayData.elems)[i].row = minRow;
				(grayData.elems)[i].col = minCol;
				if(((grayData.elems)[i].gElems = malloc(sizeof(double) * minRow * minCol)) == 0)
					res = -1;
			}
			else
				res = 9;

			currViewPair++;
		}
	}

   return res;
}
