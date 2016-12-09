/*
 *Zachary Job
 *mgr.c
 *25/25/25
 */

#include <stdlib.h>
#include <stdio.h>

#ifdef __CYGWIN__
	#include <netpbm/pam.h>
#elif __linux
	#include <pam.h>
#endif

#include "defs.h"

/*
 *The main
 *
 *@RETURN: The return status
 */
int getMap(struct PGMStat inPGM, struct harrisData *hData, struct opParam params)
{
	/*
	 *Return code
	 *INCOMPLETE LIST
	 */
	int res/*, i, j,*/,cRow, cCol;
	double *gToD;
	struct conv2Data c2L, c2R, c2G;
	struct kernel gKern, lKern, rKern;

	res = 0;

	/*Cast input to double and set dimensions*/
	if(res == 0)
		res = grayToDouble(inPGM, &gToD);	
	if(res == 0)
	{
		cRow = inPGM.row;
		cCol = inPGM.col;
	}

	/*Smooth input with gaussian filter*/
	if(res == 0)
		res = conv2Init(&c2G, cRow, cCol);		
	if(res == 0)
	{
		gKern.height = params.gaussWin;
		gKern.width = params.gaussWin;
		res = genGaussKernel(gToD, cRow * cCol, &gKern);
	}

	/*Apply Gaussian Filter*/
	if(res == 0)
	{
		conv2(&c2G, gToD, gKern);
		free(gToD);
		gToD = c2G.elemsRes, c2G.elemsRes = 0;
	}

	/*Scrub*/
	if(res == 0)
		res = conv2Clean(&c2G);
	if(res == 0)
		res = kernClean(&gKern);
	
	/*Initialize first derivative data*/
	if(res == 0)
		res = kernInit(&lKern, params.derivWin, params.derivWin, params.isLocal, params.derivKernelL);
	if(res == 0)
		res = kernInit(&rKern, params.derivWin, params.derivWin, params.isLocal, params.derivKernelR);
	if(res == 0)
		res = conv2Init(&c2L, cRow, cCol);	
	if(res == 0)
		res = conv2Init(&c2R, cRow, cCol);	

	/*Perform convulution operation for initial derivative*/
	if(res == 0)
	{
		conv2(&c2L, gToD, lKern);
		conv2(&c2R, gToD, rKern);
	
		hData->iX = c2L.elemsRes, c2L.elemsRes = 0;
		hData->iY = c2R.elemsRes, c2R.elemsRes = 0;
		
		cCol = c2L.widthRes;		
		cRow = c2L.heightRes;		
	}

	/*Scrub*/
	if(res == 0)
		res = conv2Clean(&c2L);
	if(res == 0)
		res = conv2Clean(&c2R);
	if(res == 0)
		res = kernClean(&lKern);
	if(res == 0)
		res = kernClean(&rKern);

	/*Malloc containers for results of matrix math ops*/
	if((hData->iX2 = malloc(sizeof(double) * cCol * cRow)) == 0)
		res = -1;	
	else if((hData->iY2 = malloc(sizeof(double) * cCol * cRow)) == 0)
		res = -1;	

	/*Matrix math ops*/	
	if(res == 0)
	{
		elemXplyMx(hData->iX, hData->iX, cCol, cRow, hData->iX2);
		elemXplyMx(hData->iY, hData->iY, cCol, cRow, hData->iY2);
	}
	
	/*Perform harris operation*/
	if(res == 0)
	{
		hData->width = cCol;	
		hData->height = cRow;	
		hData->supprWin = params.supprWin; 
		hData->thresh = params.thresh;
		res = harrisOperation(hData);
	}

	if(res == 0)
	{
		/*Cleanup - disregard errors past here and try to close anyway*/	
		free(hData->iX);
		free(hData->iY);
		free(hData->iX2);
		free(hData->iY2);
		free(gToD);
	}

   return res;
}
