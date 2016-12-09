/*
 *Zachary Job
 *grayToDouble.c
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
 *Cast the gray elems to double
 *
 *@PARAM: The image data to form the unsigned short
 *@RETURN: The return code
 */
int grayToDouble(struct PGMStat *inPGM)
{
	/*
	 *
	 *The return code
	 *Generic iterator
	 *Generic iterator
	 *The input image grays
	 */
	int res, i, j;
	gray **inImage;

	res = 0;

	res = openFD(inPGM->fName, READFILE, &(inPGM->fd));

	if(res == 0)
	{
		inImage = pgm_readpgm(inPGM->fd, &(inPGM->col), &(inPGM->row), &(inPGM->maxVal)); 

		if((inPGM->gElems = malloc(sizeof(double) * inPGM->row * inPGM->col)) == 0)
			res = -1;
	}

	for(i = 0; res == 0 && i < inPGM->row; ++i)
	{
		for(j = 0; j < inPGM->col; ++j)
			(inPGM->gElems)[i * inPGM->col + j] = (double)(inImage[i][j]);
	}

	if(res == 0)
	{
		pgm_freearray(inImage, inPGM->row);
		res = closeFD(inPGM->fd);
	}

	return res;
}
