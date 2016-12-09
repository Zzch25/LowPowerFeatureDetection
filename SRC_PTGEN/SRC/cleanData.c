/*
 *Zachary Job
 *cleanData.c
 *25/25/25
 */

#include <stdlib.h>
#include <stdio.h>

#ifdef __CYGWIN__
	#include <netpbm/pam.h>
#elif __linux
	#include <pam.h>
#endif

#include "../defs.h"

/*
 *Purge map data
 *
 *@PARAM: The map to scrub
 *@RETURN: End of execution state
 */
int cleanData(struct grayInfo grayData)
{
	/*
	  *Return code
	  *INCOMPLETE LIST
	  */
	int res, i;

	res = 0;
	
	/*Was undecided on 0 or NULL*/

	if((grayData.image).gElems != 0 && (grayData.image).gElems != NULL)
		free((grayData.image).gElems);

	for(i = 0; i < grayData.sz; i++)
	{
		if((grayData.elems)[i] != 0 && (grayData.elems)[i] != NULL)
			free((grayData.elems)[i]);
	}
	
	if(grayData.elems != 0 && grayData.elems != NULL)
		free(grayData.elems);
	if(grayData.elemsLoc != 0 && grayData.elemsLoc != NULL)
		free(grayData.elemsLoc);
	if(grayData.elemsData != 0 && grayData.elemsData != NULL)
		free(grayData.elemsData);

	return res;
}
