/*
 *(c) Zachary Job
 *All rights reserved.
 *Upon completion rights relinquished to STIGroup with author mention
 *as the only condition.
 *4/15/2015
 */

#include <stdio.h>

/*
 *Close a file descriptor
 *
 *@PARAM: the file to close
 *@RETURN: the exit status
 */
int closeFD(FILE *fd)
{
	/*
	 *Exit status
	 */
	int res;
	
	res = 0;

	if(fclose(fd) == EOF)
		res = 1;
	
	return res;
}