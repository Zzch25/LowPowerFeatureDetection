/*
 *Zachary Job
 *mgr.c
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

#include "defs.h"

/*
 *The main
 *
 *@RETURN: returns program state at end of execution
 */
int main(int argc, char* argv[])
{
	/*
	  *Return code
	  *INCOMPLETE LIST
	  */
	int res, res2, i, j, cpSz; 
	double success, distx, disty, dist;
	struct PGMStat inPGML, inPGMR, inPGMT, outPGM1, outPGM2;
	struct harrisData hDataL, hDataR;
	struct opParam params;	
	struct SADData sData;
	struct SADQSortable *sDataTemp;
	FILE *fdl, *fdr, *fdt, *fdw1, *fdw2;

	double DERIVKERNELV[] = {-1,0,1,-1,0,1,-1,0,1};
	double DERIVKERNELH[] = {-1,-1,-1,0,0,0,1,1,1};

	res = res2 = 0;

	/*netpbm inittialize error calls etc*/
	pm_init(argv[0], 0);

	if(res == 0)
		fprintf(stderr, "Loading images and preparing outputs... ");

	/*Open descriptors*/
	res = openFD(ORGIMGPATHL, ORGIMGL, READFILE, &fdl);
	if(res == 0)
		res = openFD(ORGIMGPATHR, ORGIMGR, READFILE, &fdr);
	if(res == 0)
		res = openFD(ORGIMGPATHR, TRUTHIMG, READFILE, &fdt);
	if(res == 0)
		res = openFD(ORGIMGPATHR, NEWIMG1, NEWFILE, &fdw1);
	if(res == 0)
		res = openFD(ORGIMGPATHR, NEWIMG2, NEWFILE, &fdw2);

	if(res == 0)
	{	
		/*Load the input PGM*/
		inPGML.elems = pgm_readpgm(fdl, &(inPGML.col), &(inPGML.row), &(inPGML.maxVal));
		inPGMR.elems = pgm_readpgm(fdr, &(inPGMR.col), &(inPGMR.row), &(inPGMR.maxVal));	
		inPGMT.elems = pgm_readpgm(fdt, &(inPGMT.col), &(inPGMT.row), &(inPGMT.maxVal));
		outPGM1.elems = pgm_allocarray(inPGML.col, inPGML.row);
		outPGM2.elems = pgm_allocarray(inPGML.col, inPGML.row);
	}

	/*If error on closing begin to exit gracefully*/
	if((res = closeFD(fdl)) != 0)
		pgm_freearray(inPGML.elems, inPGML.row);
	if((res2 = closeFD(fdr)) != 0)
		pgm_freearray(inPGMR.elems, inPGMR.row);
	if(res == 0)
		res2 = res;
	if((res = closeFD(fdt)) != 0)
		pgm_freearray(inPGMT.elems, inPGMT.row);
	
	if(res == 0)
		fprintf(stderr, "Done\nPerforming harris detection and writing image maps... ");

	/*Set the operating parameters*/
	if(res == 0)
	{
		params.thresh = HARRISTHRESH;
		params.derivWin = DERIVWINSZ;
		params.gaussWin = GAUSSWINSZ;
		params.supprWin = SUPPRWINSIZE;
		params.isLocal = True;
		params.derivKernelL = DERIVKERNELV;
		params.derivKernelR = DERIVKERNELH;
	}

	/*perform the harris corner detection*/
	if(res == 0)
		getMap(inPGML, &hDataL, params);
	if(res == 0)
		getMap(inPGMR, &hDataR, params);

	for(i = 0; i < hDataL.height; i++)
	{
		for(j = 0; j < hDataL.width; j++)
		{
			if(hDataL.elems[i * hDataL.width + j] != 0)
				outPGM1.elems[i][j] = 255;
			else
				outPGM1.elems[i][j] = inPGML.elems[i][j];
		}
	}

	for(i = 0; i < hDataR.height; i++)
	{
		for(j = 0; j < hDataR.width; j++)
		{
			if(hDataR.elems[i * hDataR.width + j] != 0)
				outPGM2.elems[i][j] = 255;
			else
				outPGM2.elems[i][j] = inPGMR.elems[i][j];
		}
	}	


	if(res == 0)
	{
		pgm_writepgm(fdw1, outPGM1.elems, inPGML.col, inPGML.row, inPGML.maxVal, WRITEBIN);
		pgm_writepgm(fdw2, outPGM2.elems, inPGMR.col, inPGMR.row, inPGMR.maxVal, WRITEBIN);
		res = closeFD(fdw1);
		res2 = closeFD(fdw2);
		if(res == 0)
			res = res2;
	}

	if(res == 0)
	{
		pgm_freearray(outPGM1.elems, inPGML.row);
		pgm_freearray(outPGM2.elems, inPGMR.row);
	}

	if(res == 0)
		fprintf(stderr, "Done\nPerforming SAD operation (OUT OF TIME TO OPTIMIZE - SEE FUNCTION NOTES)... ");

	/*Perform SAD comparison*/
	if(res == 0)
	{
		sData.winSz = SADWINSZ;
		sData.maxElems = MAXCMP; 
		sData.rejectCap = SADREJECT;

		SADOperation(hDataL, hDataR, &sData);
	}

	if(res == 0)
		fprintf(stderr, "Done\nGathering information...\n");
/*
	fprintf(stderr, "\nDEBUG\n");
	for(i = 0; i < sData.totalElems; i++)
		fprintf(stderr, "X1(%d)Y1(%d) v X2(%d)Y2(%d) @ %G\n", sData.elems[i].locL.x, sData.elems[i].locL.y, sData.elems[i].locR.x, sData.elems[i].locR.y, sData.elems[i].val);
	fprintf(stderr, "DEBUG\n\n");
*/

	/*Perform statistics per change in acceptance percentage*/
	for(i = sData.maxElems; i < 100; i += PERCENTINC)
	{
		/*Copy to the results*/
		cpSz = (int)((((double)sData.totalElems / (double)100)) * (double)i);

		if((sDataTemp = malloc(sizeof(struct SADQSortable) * cpSz)) == 0)
			res = -1;
		else
			memcpy(sDataTemp, sData.elems, sizeof(struct SADQSortable) * cpSz);
	
		/*Generate statistics*/
		for(j = 0, success = 0; j < cpSz; j++)
		{
			distx = (fabs(sData.elems[j].locL.y - sData.elems[j].locR.y));
			distx *= distx;
			disty = (fabs(sData.elems[j].locL.x - sData.elems[j].locR.x));
			disty *= disty;
			dist = distx + disty;
			dist /= dist;
			success += (double)(inPGMT.elems[sData.elems[j].locL.y][sData.elems[j].locL.x] >= dist - 1 && 
									inPGMT.elems[sData.elems[j].locL.y][sData.elems[j].locL.x] <= dist + 1);
		}

		fprintf(stderr, "Success Percentile(@%d with size %d) - %G\n", i, cpSz, (100.0 / (double)cpSz) * success);

		if(res == 0)
			free(sDataTemp);
	}

	if(res == 0)
		fprintf(stderr, "Done\nCleaning... ");

	if(res == 0)
	{
		/*Cleanup - disregard errors try and close anyway*/	
		pgm_freearray(inPGML.elems, inPGML.row);
		pgm_freearray(inPGMR.elems, inPGMR.row);
		pgm_freearray(inPGMT.elems, inPGMT.row);

		free(hDataL.elems);
		free(hDataR.elems);
		free(hDataL.elemsU);
		free(hDataR.elemsU);
	}

	if(res == 0)
		fprintf(stderr, "Done\nExiting...\n");

   return res;
}
