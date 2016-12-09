/*
 *Zachary Job
 *stereo.c
 *25/25/25
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __CYGWIN__
	#include <netpbm/pam.h>
#elif __linux
	#include <pam.h>
#endif

#include "../defs.h"

/*
 *A wrapper for calling the stereo implementation
 *
 *@PARAM The input PGM data
 *@PARAM The output PGM data
 *@PARAM The general processing information 
 *@RETURN The return code 
 */
int stereo(struct viewPairPoint *images, struct PGMStat *outPGM, struct grayInfo grayData)
{
	/*
	 *Return code
	 *Description INCOMPLETE
	 */
	/*unsigned short *normalize;*/
	int res, i, j, windowSz, windowHalf;
	double score, lastScore;
	struct dcoords pixel1, pixel2;
	struct rankMap *rMapL, *rMapR;
	
	res = 0;

	/*Alloc all*/
	if((rMapL = malloc(sizeof(struct rankMap))) == 0)
		res = -1;
	else if((rMapR = malloc(sizeof(struct rankMap))) == 0)
		res = -1;

	/*Ensure odd windowSz above 3*/
	windowSz = grayData.transSZ;
	windowSz = windowSz * (int)(windowSz > 2) + 3 * (int)(windowSz <= 2);
	windowSz += (int)(windowSz % 2 == 0);
	/*Define the size to subtract to reach a corner of the window*/
	windowHalf = windowSz >> 1;
	
	/*Get rank maps*/
	res = rankTransform(&(images->elemL), &(images->elemR), rMapL, rMapR, windowSz);	

	/*Perform SAD*/
	for(i = windowHalf; res == 0 && i < outPGM->row - windowHalf; i++)
	{
		for(j = windowHalf; j < outPGM->col - windowHalf; j++)
		{
			pixel1.x = j; 
			pixel1.y = i;
			pixel2.x = SAD(rMapL, rMapR, pixel1, grayData.winSZ, &score, &lastScore);
			pixel2.y = i;	

			outPGM->gElems[i * outPGM->col + j] = pixel1.x - pixel2.x;

			if(outPGM->gElems[i * outPGM->col + j] > MAXGRAY)
				outPGM->gElems[i * outPGM->col + j] = MINDISP;
		}
	}

	free(rMapL->elems);
	free(rMapR->elems);
	free(rMapL);
	free(rMapR);

	return res;
}
