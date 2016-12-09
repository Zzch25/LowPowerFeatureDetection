/*
 *Zachary Job
 *compQSort.c
 *25/25/25
 */

#include "defs.h"

/*
 *The compare function for qsort
 *
 *@PARAM: The first comparator 
 *@PARAM: The second comparator
 *@RETURN: The resulting value
 */
int cmpQSort(const void *in1, const void *in2)
{
	if((*((struct SADQSortable *)in1)).val > (*((struct SADQSortable *)in2)).val)
		return -1;
	if((*((struct SADQSortable *)in1)).val < (*((struct SADQSortable *)in2)).val)
		return 1;
	return 0;
}
