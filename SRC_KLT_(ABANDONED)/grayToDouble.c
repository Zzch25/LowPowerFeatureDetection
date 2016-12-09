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

#include "defs.h"

/*
 *Initialize the conv2 data
 *
 *@PARAM: The image data to form the double
 *@PARAM: The double array output
 *@RETURN: The return code
 */
int grayToDouble(struct PGMStat inPGM, double **outDouble)
{
	/*
	 *
	 *The return code
	 *Generic iterator
	 *Generic iterator
	 */
	int res, i, j;

	res = 0;

	if((*outDouble = malloc(sizeof(double) * inPGM.row * inPGM.col)) == 0)
		res = -1;

	for(i = 0; i < inPGM.row; ++i)
	{
		for(j = 0; j < inPGM.col; ++j)
			(*outDouble)[i * inPGM.col + j] = (double)inPGM.elems[i][j];
	}

	return res;
}
