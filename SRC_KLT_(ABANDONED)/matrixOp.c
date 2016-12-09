/*
 *Zachary Job
 *Part credits to unkown author
 *normalize.c
 *25/25/25
 */

#include <string.h>
#include <math.h>
 
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix_double.h>
 
#include "defs.h"

/*
 *Produce the product of matricies
 *
 *@PARAM: The first matrix
 *@PARAM: The second matrix
 *@PARAM: The width
 *@PARAM: The height
 *@PARAM: The product
 */
void elemXplyMx(double *m1, double *m2, int width, int height, double *mRes)
{
	/*
	 *Generic iterator
	 *Generic iterator
	 *Spare some computation
	 */
	int i, j, idx;

	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			idx = i * width + j;
			mRes[idx] = m1[idx] * m2[idx];
		}
	}
}
