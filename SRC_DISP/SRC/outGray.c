/*
 *Zachary Job
 *outGray.c
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
 *Write the resulting reconstruction data
 *
 *@PARAM: The map data now containing the resulting reconstructions
 *@RETURN: End of execution state
 */
int outGray(struct grayInfo grayData)
{
	/*
	  *Return code
	  *INCOMPLETE LIST
	  */
	int res, i, j, k;
	gray **offload;

	res = 0;	

	for(i = 0; res == 0 && i < grayData.sz; i++)
	{

		if((offload = malloc(sizeof(gray *) * ((grayData.elems)[i]).row)) == 0)
			res = -1;
		else
		{
			for(j = 0; res == 0 && j < ((grayData.elems)[i]).row; j++)
			{
				if((offload[j] = malloc(sizeof(gray) * ((grayData.elems)[i]).col)) == 0)
					res = -1;
				else
				{
					for(k = 0; k < ((grayData.elems)[i]).col; k++)
						offload[j][k] = (gray)(((grayData.elems)[i]).gElems)[j * ((grayData.elems)[i]).col + k];
				}
			}
		
			res = openFD(((grayData.elems)[i]).fName, NEWFILE, &(((grayData.elems)[i]).fd));


			if(res == 0)
			{
				pgm_writepgm(((grayData.elems)[i]).fd, offload, ((grayData.elems)[i]).col, ((grayData.elems)[i]).row, MAXGRAY, WRITEBIN);
				
				res = closeFD((grayData.elems)[i].fd);
			}
		}
	}

	if(offload != 0)
		free(offload);

   return res;
}
