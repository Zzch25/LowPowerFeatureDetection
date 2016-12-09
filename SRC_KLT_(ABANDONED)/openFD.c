/*
 *(c) Zachary Job
 *All rights reserved.
 *4/14/2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *open a file for non binary operations
 *
 *@PARAM: the location of the file
 *@PARAM: the name of the file
 *@PARAM: the file descriptor mode
 *@PARAM: the descriptor to return for writing
 *@RETURN: the exit status
 */
int openFD(char *path, char *name, int mode, FILE **fd)
{
	/*
	 *Exit status
	 *Size of string representation of file path
	 *A string for the file path
	 *The file descriptor
	 */
	int res, pathSZ;
	char *fileLocAndName; 
	
	res = 0;
	
	/*Prepare string to form a full file path - could realloc instead*/
	pathSZ = strlen(name) + 1;
	if(path != NULL)
		pathSZ += strlen(path) + 1;
	if((fileLocAndName = malloc(sizeof(char) * pathSZ)) == 0)
		exit(-1);
	
	/* Malloc has not failed */
	if(res == 0)
	{
		/*Setup the file path*/
		if(path != NULL)
		{
			strcpy(fileLocAndName, path);
			strcat(fileLocAndName, name);
		}
		else /*because strcat can handle poorly to a null byte when it is at the start*/
			strcpy(fileLocAndName, name);
		fileLocAndName[pathSZ - 1] = '\0';
		
		/*open the targeted file*/
		
		/*New*/
		if(mode == 0)
		{
			if((*fd = fopen(fileLocAndName, "wb+")) == NULL)
				res = 1;
		}
		/*Append*/
		else if(mode == 1)
		{
			if((*fd = fopen(fileLocAndName, "ab+")) == NULL)
				res = 1;
		}
		/*Read*/
		else if(mode == 2)
		{
			if((*fd = fopen(fileLocAndName, "r")) == NULL)
				res = 1;
		}
		else
			res = 1;
		
		/*Cleanup*/
		free(fileLocAndName);
	}
	
	return res;
}
