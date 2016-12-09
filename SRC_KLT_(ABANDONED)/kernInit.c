/*
 *Zachary Job
 *kernInit.c
 *25/25/25
 */

#include <stdlib.h>

#include "defs.h"

/*
 *To package a kernel init
 *
 *@PARAM: The structure to init
 *@PARAM: The kernel height
 *@PARAM: The kernel width
 *@PARAM: Whether or not to free the elements
 *@PARAM: The elements to assign
 *@RETURN: The return code
 */
int kernInit(struct kernel *kern, int height, int width, int local, double *mask)
{
	/*
	 *The return code
	 */
	int res;

	res = 0;

	if(kern != 0 && kern != NULL)
	{
		kern->width = width;
		kern->height = height;
		kern->isLocal = local;
		kern->elems = mask;
	}
	else
		res = 1;

	return res;
}
