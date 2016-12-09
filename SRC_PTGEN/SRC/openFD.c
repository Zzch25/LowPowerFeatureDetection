/*
 *(c) Zachary Job
 *All rights reserved.
 *4/14/2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "../defs.h"

/*
 *open a file for non binary operations
 *
 *@PARAM: the location of the file
 *@PARAM: the file descriptor mode
 *@PARAM: the descriptor to return for writing
 *@RETURN: the exit status
 */
int openFD(char *path, int mode, FILE **fd)
{
	/*
	 *Exit status
	 *Size of string representation of file path
	 *The file descriptor
	 */
	int res;
	
	res = 0;
	
	/*New*/
	if(mode == NEWFILE)
	{
		if((*fd = fopen(path, NEWFILE_OPT)) == NULL)
			res = 1;
	}
	/*Append*/
	else if(mode == APPENDFILE)
	{
		if((*fd = fopen(path, APPENDFILE_OPT)) == NULL)
			res = 1;
	}
	/*Read*/
	else if(mode == READFILE)
	{
		if((*fd = fopen(path, READFILE_OPT)) == NULL)
			res = 1;
	}
	else
		res = 1;
		
	return res;
}
