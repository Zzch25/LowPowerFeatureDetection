/*
 *Zachary Job
 *conv2Init.c
 *25/25/25
 */

#include <stdlib.h>

#include "defs.h"

/*
 *Initialize the conv2 data
 *
 *@PARAM: The data and structures to run and store the convolution steps and result
 *@PARAM: The height of the image
 *@PARAM: The width of the image
 *@RETURN: The return code
 */
int conv2Init(struct conv2Data *ev, int height, int width)
{
	/*
	 *
	 *The return code
	 */
	int res;

	res = 0;

	if(width > 0 && height > 0)
	{
		ev->heightSrc = height;
		ev->widthSrc = width;
	
		ev->heightRes = height;
		ev->widthRes = width;

		if((ev->elemsRes = malloc(sizeof(double) * ev->heightRes * ev->widthRes)) == 0)
			res = -1;
	}
	else
		res = 1;

	return res;
}
