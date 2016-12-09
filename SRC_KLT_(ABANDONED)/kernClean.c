/*
 *Zachary Job
 *kernClean.c
 *25/25/25
 */

#include <stdlib.h>

#include "defs.h"

/*
 *To lessen confussion on how to scrub the struct
 *
 *@PARAM: The structure to clean
 *@RETURN: The return code
 */
int kernClean(struct kernel *kern)
{
	/*
	 *The return code
	 */
	int res;

	res = 0;

	if(kern != 0 && kern != NULL)
	{
		kern->width = 0;
		kern->height = 0;
		if(kern->isLocal == False)
			free(kern->elems);
		else
			kern->elems = 0;
	}
	else
		res = 1;

	return res;
}
