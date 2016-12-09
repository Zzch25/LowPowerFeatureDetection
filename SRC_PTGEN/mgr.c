/*
 *Zachary Job
 *mgr.c
 *25/25/25
 */

#include <stdlib.h>
#include <stdio.h>

#ifdef __CYGWIN__
	#include <netpbm/pam.h>
#elif __linux
	#include <pam.h>
#endif

#include "defs.h"

/*
 *The main
 *
 *@PARAM: The number of arguments
 *@PARAM: The space delimited arguments
 *@RETURN: returns program state at end of execution
 */
int main(int argc, char* argv[])
{
	/*
	  *Return code
	  *INCOMPLETE LIST
	  */
	int res;
	struct grayInfo grayData;

	res = 0;

	/*netpbm inittialize error calls etc*/
	pm_init(argv[0], 0);

	fprintf(stderr, "Initializing...\n");

	/*Attempt to initialize the map data as requested*/
	res = initData(argc, argv, &grayData);	
	
	if(res == 0)
	{
		fprintf(stderr, "Generating Buckets...\n");
		res = bucketPoints(grayData);
	}

	if(res == 0)
	{
		fprintf(stderr, "Outputting...\n");
		res = outCSV(grayData);		
	}

	if(res != 0)
		fprintf(stderr, "RES :: %d\n", res);

	if(res >= 0)
	{
		fprintf(stderr, "Cleaning...\n");
		res = cleanData(grayData);
	}

   return res;
}
