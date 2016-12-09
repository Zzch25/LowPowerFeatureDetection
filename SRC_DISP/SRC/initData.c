/*
 *Zachary Job
 *initData.c
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
 *Attempt to initialize data in the map as specified by the user
 *
 *@PARAM: The number of arguments
 *@PARAM: The space delimited arguments
 *@PARAM: The map structure to initialize
 *@RETURN: returns program state at end of execution
 */
int initData(int argcIdx, char* argv[], struct grayInfo *grayData)
{
	/*
	  *Return code
	  *INCOMPLETE LIST
	  */
	int res, i, numViewPair, minRow, minCol;

	res = 0;

	numViewPair = 0;
	minRow = minCol = 0;
	
	grayData->sz = 0;
	grayData->winSZ = 0;
	grayData->transSZ = 0;
	grayData->confidence = 0;
	grayData->viewPairInfo = NULL;
	grayData->elems = NULL;

	/*Check user input*/
	if(argcIdx > TRIPDIALOGUE)
	{
		for(i = 1, grayData->sz = 0; res == 0 && i <= argcIdx - ARGSVIEWPAIR; i += ARGSVIEWPAIR)
		{	
			numViewPair++;
			
			if((grayData->elems = realloc(grayData->elems, sizeof(struct PGMStat) * (numViewPair))) == 0)
				res = -1;
			else
				(grayData->elems)[numViewPair - 1].gElems = NULL;
					
			if((grayData->viewPairInfo = realloc(grayData->viewPairInfo, sizeof(struct viewPairPoint) * (numViewPair))) == 0)
				res = -1;
			else
			{
				((grayData->viewPairInfo)[numViewPair - 1]).elemL.gElems = NULL;
				((grayData->viewPairInfo)[numViewPair - 1]).elemR.gElems = NULL;
			}
			
			if(res == 0)
			{
				sscanf(argv[i + 2], "%lf", &(((grayData->viewPairInfo)[numViewPair - 1]).baseline));
				sscanf(argv[i + 3], "%lf", &(((grayData->viewPairInfo)[numViewPair - 1]).focallength));

				((grayData->viewPairInfo)[numViewPair - 1]).elemL.fName = argv[i];
				((grayData->viewPairInfo)[numViewPair - 1]).elemR.fName = argv[i + 1];
				((grayData->elems)[numViewPair - 1]).fName = argv[i + 4];

				if((grayData->viewPairInfo)[numViewPair - 1].baseline < 0)
					res = 1;
				else if((grayData->viewPairInfo)[numViewPair - 1].focallength < 0)
					res = 1;
				
				if(res == 0)
					res = grayToDouble(&(((grayData->viewPairInfo)[numViewPair - 1]).elemL));
				if(res == 0)
					res = grayToDouble(&(((grayData->viewPairInfo)[numViewPair - 1]).elemR));

				if(res == 0)
				{
					(grayData->viewPairInfo)[numViewPair - 1].elemL.maxVal = MAXGRAY;
					(grayData->viewPairInfo)[numViewPair - 1].elemR.maxVal = MAXGRAY;
					
					minRow = fmin(((grayData->viewPairInfo)[numViewPair - 1]).elemL.row, ((grayData->viewPairInfo)[numViewPair - 1]).elemR.row);
					minCol = fmin(((grayData->viewPairInfo)[numViewPair - 1]).elemL.col, ((grayData->viewPairInfo)[numViewPair - 1]).elemR.col);

					if(minRow > 0 && minCol > 0)
					{
						(grayData->elems)[numViewPair - 1].row = minRow;
						(grayData->elems)[numViewPair - 1].col = minCol;
						if(((grayData->elems)[numViewPair - 1].gElems = malloc(sizeof(double) * minRow * minCol)) == 0)
							res = -1;
					}
					else
						res = 9;	

				}
			}
		}
	}
	else
		res = 1;

	if(numViewPair == 0)
		res = 1;
	
	grayData->sz = numViewPair;

	/*Undecided if these should be user specified*/
	grayData->winSZ = WINSZ;
	grayData->transSZ = TRANSZ;
	grayData->confidence = (double)CONFIDENCE;

   return res;
}
