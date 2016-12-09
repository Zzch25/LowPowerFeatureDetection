/*
 *Zachary Job
 *viewPairToDisps.c
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
 *Calculate disparitues from view pairs
 *
 *@PARAM: The map data containing view pairs and disparity information
 *@RETURN: End of execution state
 */
int viewPairsToDisps(struct grayInfo grayData)
{
	/*
	  *Return code
	  *INCOMPLETE LIST
	  */
	int res, i;

	res = 0;

	/********************************/
	/**M A I N T A I N I N G   A S **/
	/**                            **/
	/**W R A P P E R   M A Y       **/
	/**                            **/
	/**W A N T   T O   P A S S     **/
	/**                            **/
	/**W I N D O W   A R G S       **/
	/**                            **/
	/**F R O M   C M D             **/
	/********************************/
	
	for(i = 0; res == 0 && i < grayData.sz; i++)
		res = stereo(&((grayData.viewPairInfo)[i]), &(grayData.elems[i]), grayData);

   return res;
}
