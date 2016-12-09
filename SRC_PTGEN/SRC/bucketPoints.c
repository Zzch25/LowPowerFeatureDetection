/*
 *Zachary Job
 *bucketPoints.c
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
 *Sort comparator
 *
 *@PARAM: Element one
 *@PARAM: Element two
 *@RETURN: The sort decision
 */
int comparator(const void *a, const void *b)
{
	int pta, ptb, ta, tb;

	pta = ((struct selectPoint *)a)->num;
	ta = ((struct selectPoint *)a)->val;
	ptb = ((struct selectPoint *)b)->num;
	tb = ((struct selectPoint *)b)->val;

	pta *= (int)(ta != 0);
	ptb *= (int)(tb != 0);

	return ptb - pta;
}

/*
 *Bucket the information rgarding the point
 *
 *@PARAM: The system information
 *@RETURN: End of execution state
 */
int bucketPoints(struct grayInfo grayData)
{
	/*
	  *Return code
	  *INCOMPLETE LIST
	  */
	int res, i, j, k, winHalf, val, curr, currLast, currNext, total, temp1, temp2, temp3, max, min, trip, tripNext, iters;
	double varLine;

	res = 0;
	winHalf = grayData.winSZ >> 1;
	
	for(i = 0; res == 0 && i < grayData.sz; i++)
	{
		total = 0;

		for(j = -1 * winHalf; res == 0 && j < winHalf; j++)
		{
			for(k = -1 * winHalf; res == 0 && k < winHalf; k++)
			{
				val = (int)((grayData.image).gElems)[((grayData.elemsLoc)[i].y + j) * grayData.image.col + (grayData.elemsLoc)[i].x + k];
				if(val >= 0 && val <= MAXVAL)
				{
					((grayData.elems)[i][val]).val++;
					total++;
				}
			}
		}

		/*Sort in descending order*/
		qsort((grayData.elems)[i], MAXVAL + 1, sizeof(struct selectPoint), comparator);

		temp1 = total >> 2;
		temp2 = temp1 << 2;
		temp3 = total - temp2;

		((grayData.elemsData)[i]).Q1F = (double)temp1;
		((grayData.elemsData)[i]).Q2F = (double)temp1;
		((grayData.elemsData)[i]).Q3F = (double)temp1;
		((grayData.elemsData)[i]).Q4F = (double)temp1 + (double)temp3;

		curr = 0;

		for(j = 0, trip = 0, max = ((grayData.elems)[i])[curr].num; j < ((grayData.elemsData)[i]).Q1F; j++)
		{
			min = ((grayData.elems)[i])[curr].num;
			currLast = curr;
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			trip *= (int)(curr == currLast);
			((grayData.elemsData)[i]).Q1AVG += (double)((grayData.elems)[i])[curr].num;
		}
		((grayData.elemsData)[i]).Q1AVG /= ((grayData.elemsData)[i]).Q1F;
		((grayData.elemsData)[i]).Q1W = max - min;

		for(j = 0, max = ((grayData.elems)[i])[curr].num; j < ((grayData.elemsData)[i]).Q2F; j++)
		{
			min = ((grayData.elems)[i])[curr].num;
			currLast = curr;
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			trip *= (int)(curr == currLast);
			((grayData.elemsData)[i]).Q2AVG += ((grayData.elems)[i])[curr].num;
		}
		((grayData.elemsData)[i]).Q2AVG /= ((grayData.elemsData)[i]).Q2F;
		((grayData.elemsData)[i]).Q2W = max - min;

		for(j = 0, max = ((grayData.elems)[i])[curr].num; j < ((grayData.elemsData)[i]).Q3F; j++)
		{
			min = ((grayData.elems)[i])[curr].num;
			currLast = curr;	
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			trip *= (int)(curr == currLast);
			((grayData.elemsData)[i]).Q3AVG += ((grayData.elems)[i])[curr].num;
		}
		((grayData.elemsData)[i]).Q3AVG /= ((grayData.elemsData)[i]).Q3F;
		((grayData.elemsData)[i]).Q3W = max - min;

		for(j = 0, max = ((grayData.elems)[i])[curr].num; j < ((grayData.elemsData)[i]).Q4F; j++)
		{
			min = ((grayData.elems)[i])[curr].num;
			currLast = curr;	
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			trip *= (int)(curr == currLast);
			((grayData.elemsData)[i]).Q4AVG += ((grayData.elems)[i])[curr].num;
		}
		((grayData.elemsData)[i]).Q4AVG /= ((grayData.elemsData)[i]).Q4F;
		((grayData.elemsData)[i]).Q4W = max - min;

		curr = 0;

		for(j = 0, trip = 0; j < ((grayData.elemsData)[i]).Q1F; j++)
		{
			currLast = curr;	
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			trip *= (int)(curr == currLast);
			varLine = (double)((grayData.elems)[i])[curr].num - ((grayData.elemsData)[i]).Q1AVG;
			((grayData.elemsData)[i]).Q1V += varLine * varLine;
		}
		((grayData.elemsData)[i]).Q1V /= (((grayData.elemsData)[i]).Q1F - 1);
		((grayData.elemsData)[i]).Q1STD = sqrt(((grayData.elemsData)[i]).Q1V);
		
		for(j = 0; j < ((grayData.elemsData)[i]).Q2F; j++)
		{
			currLast = curr;	
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			trip *= (int)(curr == currLast);
			varLine = (double)((grayData.elems)[i])[curr].num - ((grayData.elemsData)[i]).Q2AVG;
			((grayData.elemsData)[i]).Q2V += varLine * varLine;
		}
		((grayData.elemsData)[i]).Q2V /= (((grayData.elemsData)[i]).Q2F - 1);
		((grayData.elemsData)[i]).Q2STD = sqrt(((grayData.elemsData)[i]).Q2V);
		
		for(j = 0; j < ((grayData.elemsData)[i]).Q3F; j++)
		{
			currLast = curr;	
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			trip *= (int)(curr == currLast);
			varLine = (double)((grayData.elems)[i])[curr].num - ((grayData.elemsData)[i]).Q3AVG;
			((grayData.elemsData)[i]).Q3V += varLine * varLine;
		}
		((grayData.elemsData)[i]).Q3V /= (((grayData.elemsData)[i]).Q3F - 1);
		((grayData.elemsData)[i]).Q3STD = sqrt(((grayData.elemsData)[i]).Q3V);

		for(j = 0; j < ((grayData.elemsData)[i]).Q4F; j++)
		{
			currLast = curr;	
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			trip *= (int)(curr == currLast);
			varLine = (double)((grayData.elems)[i])[curr].num - ((grayData.elemsData)[i]).Q4AVG;
			((grayData.elemsData)[i]).Q4V += varLine * varLine;
		}
		((grayData.elemsData)[i]).Q4V /= (((grayData.elemsData)[i]).Q4F - 1);
		((grayData.elemsData)[i]).Q4STD = sqrt(((grayData.elemsData)[i]).Q4V);

		((grayData.elemsData)[i]).QAVG = 
													(	((grayData.elemsData)[i]).Q1AVG * ((grayData.elemsData)[i]).Q1F +
														((grayData.elemsData)[i]).Q2AVG * ((grayData.elemsData)[i]).Q2F +
														((grayData.elemsData)[i]).Q3AVG * ((grayData.elemsData)[i]).Q3F +
														((grayData.elemsData)[i]).Q4AVG * ((grayData.elemsData)[i]).Q4F	)
														/
														total;

		curr = 0;

		for(j = 0, trip = 0; j < total; j++)
		{
			currLast = curr;
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			trip *= (int)(curr = currLast);
			varLine = (double)((grayData.elems)[i])[curr].num - ((grayData.elemsData)[i]).QAVG;
			((grayData.elemsData)[i]).QV += varLine * varLine;
		}
		((grayData.elemsData)[i]).QV /= total;
		((grayData.elemsData)[i]).QSTD = sqrt(((grayData.elemsData)[i]).QV);

		((grayData.elemsData)[i]).Q1_2AVG = 
													(	((grayData.elemsData)[i]).Q1AVG * ((grayData.elemsData)[i]).Q1F +
														((grayData.elemsData)[i]).Q2AVG * ((grayData.elemsData)[i]).Q2F	)
														/
														(((grayData.elemsData)[i]).Q1F + ((grayData.elemsData)[i]).Q2F);
		
		((grayData.elemsData)[i]).Q2_3AVG = 
													(	((grayData.elemsData)[i]).Q2AVG * ((grayData.elemsData)[i]).Q2F +
														((grayData.elemsData)[i]).Q3AVG * ((grayData.elemsData)[i]).Q3F	)
														/
														(((grayData.elemsData)[i]).Q2F + ((grayData.elemsData)[i]).Q3F);
		
		((grayData.elemsData)[i]).Q3_4AVG = 
													(	((grayData.elemsData)[i]).Q3AVG * ((grayData.elemsData)[i]).Q3F +
														((grayData.elemsData)[i]).Q4AVG * ((grayData.elemsData)[i]).Q4F	)
														/
														(((grayData.elemsData)[i]).Q3F + ((grayData.elemsData)[i]).Q4F);
		

		curr = 0;

		for(j = 0, trip = 0, tripNext = 0, iters = 0; j < ((grayData.elemsData)[i]).Q1F + ((grayData.elemsData)[i]).Q2F; j++)
		{
			currLast = curr;	
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			if(iters++ < ((grayData.elemsData)[i].Q1F)) currNext = curr, tripNext = trip;
			trip *= (int)(curr == currLast);
			varLine = (double)((grayData.elems)[i])[curr].num - ((grayData.elemsData)[i]).Q1_2AVG;
			((grayData.elemsData)[i]).Q1_2V += varLine * varLine;
		}
		((grayData.elemsData)[i]).Q1_2V /= (((grayData.elemsData)[i]).Q1F + ((grayData.elemsData)[i]).Q2F - 1);
		((grayData.elemsData)[i]).Q1_2STD = sqrt(((grayData.elemsData)[i]).Q1_2V);

		curr = currNext;
		trip = tripNext;

		for(j = 0, iters = 0; j < ((grayData.elemsData)[i]).Q2F + ((grayData.elemsData)[i]).Q3F; j++)
		{
			currLast = curr;	
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			if(iters++ < ((grayData.elemsData)[i].Q2F)) currNext = curr, tripNext = trip;
			trip *= (int)(curr == currLast);
			varLine = (double)((grayData.elems)[i])[curr].num - ((grayData.elemsData)[i]).Q2_3AVG;
			((grayData.elemsData)[i]).Q2_3V += varLine * varLine;
		}
		((grayData.elemsData)[i]).Q2_3V /= (((grayData.elemsData)[i]).Q2F + ((grayData.elemsData)[i]).Q3F - 1);
		((grayData.elemsData)[i]).Q2_3STD = sqrt(((grayData.elemsData)[i]).Q2_3V);

		curr = currNext;
		trip = tripNext;
		
		for(j = 0, iters = 0; j < ((grayData.elemsData)[i]).Q3F + ((grayData.elemsData)[i]).Q4F; j++)
		{
			currLast = curr;	
			curr += (int)(((grayData.elems)[i])[curr].val == trip++);
			trip *= (int)(curr == currLast);
			varLine = (double)((grayData.elems)[i])[curr].num - ((grayData.elemsData)[i]).Q3_4AVG;
			((grayData.elemsData)[i]).Q3_4V += varLine * varLine;
		}
		((grayData.elemsData)[i]).Q3_4V /= (((grayData.elemsData)[i]).Q3F + ((grayData.elemsData)[i]).Q4F - 1);
		((grayData.elemsData)[i]).Q3_4STD = sqrt(((grayData.elemsData)[i]).Q3_4V);
	}

   return res;
}
