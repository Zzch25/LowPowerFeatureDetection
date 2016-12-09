/*
 *Zachary Job
 *harrisOperation.c
 *25/25/25
 */

#include <stdlib.h>
#include <math.h>

#include "defs.h"

/*
 *Utilize the harris corner detection algorithm to fill a map with corners of a 
 *certain threshold
 *
 *@PARAM: The data to produce the harris corner map along with the result container 
 *@RETURN: The return code
 */
int harrisOperation(struct harrisData *hData)
{
	/*
	 *The return code
	 *Generic iterator
	 *Generic iterator
	 *Generic iterator
	 *Generic iterator
	 *INCOMPLETE LIST
	 */
	int res, i, j, k, l, idx, idx2, halfWin;
	double val, currMax;

	res = 0;

	/*Force odd window*/
	hData->supprWin = hData->supprWin * ((int)(hData->supprWin >= 0));
	hData->supprWin += (int)(hData->supprWin % 2 == 0);
	hData->supprWin += ((int)(hData->supprWin < 3)) << 1;

	if((hData->elems = malloc(sizeof(double) * hData->height * hData->width)) == 0)
		res = -1;
	else if((hData->elemsU = malloc(sizeof(double) * hData->height * hData->width)) == 0)
		res = -1;
	else
	{
		/*Generate harris map*/
		for(i = 0; i < hData->height; i++)
		{
			for(j = 0; j < hData->width; j++)
			{
				idx = i * hData->width + j;
				
				val = (hData->iX2[idx] * hData->iY2[idx]) / (hData->iX2[idx] + hData->iY2[idx]);
				hData->elemsU[idx] = val;
			}
		}
		
		/*Threshold filtering*/
		halfWin = (hData->supprWin >> 1);
		for(i = halfWin; i < hData->height - halfWin; i++)
		{
			for(j = halfWin, currMax = 0; j < hData->width - halfWin; j++, currMax = 0)
			{
				idx = i * hData->width + j;
				for(k = i - halfWin; k < i + halfWin; k++)	
				{
					for(l = j - halfWin; l < j + halfWin; l++)	
					{
						idx2 = k * hData->width + l;
						currMax = (double)fmax(currMax,hData->elemsU[idx2]);
					}
				}
				hData->elems[idx] = hData->elemsU[idx] * (double)(currMax == hData->elemsU[idx]) * (double)(hData->elemsU[idx] > hData->thresh);
			}
		}
	}

	return res;
}
