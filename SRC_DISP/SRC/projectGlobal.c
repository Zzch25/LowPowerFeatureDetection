/*
 *Zachary Job
 *projectGlobal.c
 *25/25/25
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __CYGWIN__
	#include <netpbm/pam.h>
#elif __linux
	#include <pam.h>
#endif

#include "../defs.h"

/*
 *Project the global coordinates to the reconstruction
 *
 *@PARAM: The map data for 
 *@RETURN: End of execution state
 */
int projectGlobal(struct mapInfo mapData)
{
	/*
	  *Return code
	  *INCOMPLETE LIST
	  */
	int res, i, j;
	double xLoc, yLoc, zDisp;

	res = 0;

	for(i = 0; res == 0 && i < mapData.szRecon; i++)
	{
		for(j = 0; res == 0 && j < ((mapData.reconInfo)[i]).szGlobal; j++)
		{
			zDisp =	(mapData.focalLength * (mapData.baseline)[((mapData.reconInfo)[i]).position]) 
						/
						(((mapData.reconInfo)[i]).global)[j].z;

			yLoc =	((((mapData.reconInfo)[i]).global)[j].y * mapData.focalLength)
						/
						(((mapData.reconInfo)[i]).global)[j].z;
			yLoc =	round(yLoc + ((mapData.reconInfo)[i]).row / (double)2);

			xLoc =	((((mapData.reconInfo)[i]).global)[j].x * mapData.focalLength)
						/
						(((mapData.reconInfo)[i]).global)[j].z;
			xLoc =	round(xLoc + ((mapData.reconInfo)[i]).col / (double)2);

			/*fprintf(stderr, "BOUNDS(%G %G %G)\n", xLoc, yLoc, zLoc);*/

			if(xLoc < ((mapData.reconInfo)[i]).col && xLoc >= 0)
			{
				if(yLoc < ((mapData.reconInfo)[i]).row && yLoc >= 0)
				{
					if(((((mapData.reconInfo)[i]).result)[(int)yLoc][(int)xLoc] > zDisp || ((((mapData.reconInfo)[i]).result)[(int)yLoc][(int)xLoc] == 0 && zDisp != 0)) && (unsigned short)round(zDisp) <= MAXGRAY)
						(((mapData.reconInfo)[i]).result)[(int)yLoc][(int)xLoc] = (gray)round(zDisp);
				}
			}
		}
	}

   return res;
}
