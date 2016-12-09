/*
 *Zachary Job
 *pixelToUShorts.c
 *25/25/25
 */

#include <stdlib.h>

#ifdef __CYGWIN__
	#include <netpbm/pam.h>
#elif __linux
	#include <pam.h>
#endif

#include "../defs.h"

/*
 *Cast the pixel elems to unsigned shorts
 *
 *@PARAM: The image data to form the unsigned short
 *@RETURN: The return code
 */
int pixelToUShorts(struct PPMStat *inPPM)
{
	/*
	 *
	 *The return code
	 *Generic iterator
	 *Generic iterator
	 *The input image pixels
	 */
	int res, i, j;
	pixel **inImage;

	res = 0;

	res = openFD(inPPM->fName, READFILE, &(inPPM->fd));

	if(res == 0)
	{
		inImage = ppm_readppm(inPPM->fd, &(inPPM->col), &(inPPM->row), &(inPPM->maxVal)); 

		if((inPPM->rElems = malloc(sizeof(unsigned short) * inPPM->row * inPPM->col)) == 0)
			res = -1;
		else if((inPPM->gElems = malloc(sizeof(unsigned short) * inPPM->row * inPPM->col)) == 0)
			res = -1;
		else if((inPPM->bElems = malloc(sizeof(unsigned short) * inPPM->row * inPPM->col)) == 0)
			res = -1;
	}

	for(i = 0; res == 0 && i < inPPM->row; ++i)
	{
		for(j = 0; j < inPPM->col; ++j)
			(inPPM->rElems)[i * inPPM->col + j] = (unsigned short)(inImage[i][j]).r;
		for(j = 0; j < inPPM->col; ++j)
			(inPPM->gElems)[i * inPPM->col + j] = (unsigned short)(inImage[i][j]).g;
		for(j = 0; j < inPPM->col; ++j)
			(inPPM->bElems)[i * inPPM->col + j] = (unsigned short)(inImage[i][j]).b;
	}

	if(res == 0)
	{
		ppm_freearray(inImage, inPPM->row);
		res = closeFD(inPPM->fd);
	}

	return res;
}
