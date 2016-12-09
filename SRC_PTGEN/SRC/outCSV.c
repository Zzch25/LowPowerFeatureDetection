/*
 *Zachary Job
 *outCSV.c
 *25/25/25
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef __CYGWIN__
	#include <netpbm/pam.h>
#elif __linux
	#include <pam.h>
#endif

#include "../defs.h"

/*
 *Write the csv
 *
 *@PARAM: The map data now containing the resulting reconstructions
 *@RETURN: End of execution state
 */
int outCSV(struct grayInfo grayData)
{
	/*
	  *Return code
	  *INCOMPLETE LIST
	  */
	int res, i, offset;
	char buffer[BIGBUFF];

	res = 0;	
	
	res = openFD(grayData.outFName, grayData.fMode, &(grayData.outfd));
	
	if(res == 0 && grayData.fMode == NEWFILE)
		fputs(CSV_HEADER, grayData.outfd);

	for(i = 0; res == 0 && i < grayData.sz; i++)
	{
		if(res == 0)
		{
			putc('\n', grayData.outfd);
			
			offset = sprintf(buffer, "%lf", (grayData.elemsData)[i].Q1W);
			offset += sprintf(&(buffer[offset]), ",%lf", (grayData.elemsData)[i].Q2W);
			offset += sprintf(&(buffer[offset]), ",%lf", (grayData.elemsData)[i].Q3W);
			offset += sprintf(&(buffer[offset]), ",%lf", (grayData.elemsData)[i].Q4W);
			offset += sprintf(&(buffer[offset]), ",%lf", (grayData.elemsData)[i].Q1STD);
			offset += sprintf(&(buffer[offset]), ",%lf", (grayData.elemsData)[i].Q2STD);
			offset += sprintf(&(buffer[offset]), ",%lf", (grayData.elemsData)[i].Q3STD);
			offset += sprintf(&(buffer[offset]), ",%lf", (grayData.elemsData)[i].Q4STD);
			offset += sprintf(&(buffer[offset]), ",%lf", (grayData.elemsData)[i].QSTD);
			offset += sprintf(&(buffer[offset]), ",%lf", (grayData.elemsData)[i].Q1_2STD);
			offset += sprintf(&(buffer[offset]), ",%lf", (grayData.elemsData)[i].Q2_3STD);
			offset += sprintf(&(buffer[offset]), ",%lf", (grayData.elemsData)[i].Q3_4STD);
			sprintf(&(buffer[offset]), ",%s", grayData.type);
			
			fputs(buffer, grayData.outfd);
		}
	}

	if(res == 0)
		res = closeFD(grayData.outfd);

   return res;
}
