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

	for(i = 0; i < grayData.sz; i++)
	{
		if((grayData.elems)[i].gElems != 0 && (grayData.elems)[i].gElems != NULL)
			free((grayData.elems)[i].gElems);
		if(((grayData.viewPairInfo)[i]).elemL.gElems != 0 && ((grayData.viewPairInfo)[i]).elemL.gElems != NULL)
			free(((grayData.viewPairInfo)[i]).elemL.gElems);
		if(((grayData.viewPairInfo)[i]).elemR.gElems != 0 && ((grayData.viewPairInfo)[i]).elemR.gElems != NULL)
			free(((grayData.viewPairInfo)[i]).elemR.gElems);
	}
	
	if(grayData.elems != 0 && grayData.elems != NULL)
		free(grayData.elems);
	if(grayData.viewPairInfo != 0 && grayData.viewPairInfo != NULL)
		free(grayData.viewPairInfo); 

	return res;
}
