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
	int res, i, j, k, numPts;

	res = 0;

	numPts = 0;
	
	grayData->sz = 0;
	grayData->winSZ = 0;
	
	grayData->elems = NULL;
	grayData->elemsLoc = NULL;
	grayData->elemsData = NULL;
	(grayData->image).gElems = NULL;

	/*Check user input*/
	if(argcIdx > TRIPDIALOGUE)
	{
		(grayData->image).fName = argv[1];
		res = grayToDouble(&(grayData->image));
		
		if(res == 0)
		{
			grayData->outFName = argv[2];
			grayData->type = argv[3];
			grayData->fMode = atoi(argv[4]);
			if(grayData->fMode != NEWFILE && grayData->fMode != APPENDFILE)
				res = 1;
		}

		for(i = 5, k = 0, grayData->sz = 0; res == 0 && i <= argcIdx - ARGSVIEWPAIR; i += ARGSVIEWPAIR, k++)
		{	
			numPts++;
		
			if((grayData->elems = realloc(grayData->elems, sizeof(struct selectPoint *) * (numPts))) == 0)
				res = -1;
			else
			{
				(grayData->elems)[numPts - 1] = NULL;

				if((grayData->elemsData = realloc(grayData->elemsData, sizeof(struct selectInfo) * (numPts))) == 0)
					res = -1;
				else if((grayData->elemsLoc = realloc(grayData->elemsLoc, sizeof(struct icoords) * (numPts))) == 0)
					res = -1;
				else if(((grayData->elems)[numPts - 1] = realloc((grayData->elems)[numPts - 1], sizeof(struct selectPoint) * (MAXVAL + 1))) == 0)
					res = -1;
			}

			if(res == 0)
			{
				for(j = 0; j < MAXVAL + 1; j++)
				{
					((grayData->elems)[numPts - 1][j]).num = j;
					((grayData->elems)[numPts - 1][j]).val = 0;
				}
				
				((grayData->elemsData)[k]).Q1F = 0;
				((grayData->elemsData)[k]).Q2F = 0;
				((grayData->elemsData)[k]).Q3F = 0;
				((grayData->elemsData)[k]).Q4F = 0;
				((grayData->elemsData)[k]).Q1W = 0;
				((grayData->elemsData)[k]).Q2W = 0;
				((grayData->elemsData)[k]).Q3W = 0;
				((grayData->elemsData)[k]).Q4W = 0;
				((grayData->elemsData)[k]).Q1AVG = 0;
				((grayData->elemsData)[k]).Q2AVG = 0;
				((grayData->elemsData)[k]).Q3AVG = 0;
				((grayData->elemsData)[k]).Q4AVG = 0;
				((grayData->elemsData)[k]).Q1V = 0;
				((grayData->elemsData)[k]).Q2V = 0;
				((grayData->elemsData)[k]).Q3V = 0;
				((grayData->elemsData)[k]).Q4V = 0;
				((grayData->elemsData)[k]).Q1STD = 0;
				((grayData->elemsData)[k]).Q2STD = 0;
				((grayData->elemsData)[k]).Q3STD = 0;
				((grayData->elemsData)[k]).Q4STD = 0;
				((grayData->elemsData)[k]).Q1_2AVG = 0;
				((grayData->elemsData)[k]).Q2_3AVG = 0;
				((grayData->elemsData)[k]).Q3_4AVG = 0;
				((grayData->elemsData)[k]).Q1_2V = 0;
				((grayData->elemsData)[k]).Q2_3V = 0;
				((grayData->elemsData)[k]).Q3_4V = 0;
				((grayData->elemsData)[k]).Q1_2STD = 0;
				((grayData->elemsData)[k]).Q2_3STD = 0;
				((grayData->elemsData)[k]).Q3_4STD = 0;
				((grayData->elemsData)[k]).QV = 0;
				((grayData->elemsData)[k]).QAVG = 0;
				((grayData->elemsData)[k]).QSTD = 0;

				((grayData->elemsLoc)[numPts - 1]).x = atoi(argv[i]);
				((grayData->elemsLoc)[numPts - 1]).y = atoi(argv[i + 1]);

				if(((grayData->elemsLoc)[numPts - 1]).x - HALFWINSZ < 0 && ((grayData->elemsLoc)[numPts - 1]).x + HALFWINSZ >= (grayData->image).col)
					res = 1;
				else if(((grayData->elemsLoc)[numPts - 1]).y - HALFWINSZ < 0 && ((grayData->elemsLoc)[numPts - 1]).y + HALFWINSZ >= (grayData->image).row)
					res = 1;
			}
		}
	}
	else
		res = 1;

	if(res != -1 && numPts == 0)
		res = 1;
	
	grayData->sz = numPts;
	grayData->winSZ = WINSZ;

   return res;
}
