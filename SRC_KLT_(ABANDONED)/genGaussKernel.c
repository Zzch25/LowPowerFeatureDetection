/*
 *Zachary Job
 *Part credits to unkown author
 *genGaussKernel.c
 *25/25/25
 */

#include <math.h>
 
#include <gsl/gsl_statistics.h>

#include "defs.h"

/*
 *Produce the product of matricies
 *
 *@PARAM: The data to use in building the kernel
 *@PARAM: The result container
 */
int genGaussKernel(double *in, int sz, struct kernel *kernelOut)
{
	/*
	 *The return code
	 *Generic iterator
	 *Generic iterator
	 *The sum of the initial calculations
	 *The stdev of the input
	 */
	int res, i, j;
	double sum, sig;

	res = 0;
	sum = 0;

	if((kernelOut->elems = malloc(sizeof(double) * kernelOut->height * kernelOut->width)) == 0)
		res = -1;
	else
	{	
		sig = gsl_stats_sd(in, 1, sz);

		for(i = 0; i < kernelOut->height; i++)
		{
			for(j = 0; j < kernelOut->width; j++)
			{
				kernelOut->elems[i * kernelOut->width + j] = (exp((-1.0 * (double)(i*i + j*j)) / (2.0 * sig * sig))) / (double)((double)M_PI * 2.0 * sig * sig);
				sum += kernelOut->elems[i * kernelOut->width + j];
			}
		}

		for(i = 0; i < kernelOut->height; ++i)
		{
			for(j = 0; j < kernelOut->width; ++j)
				kernelOut->elems[i * kernelOut->width + j] /= sum;
		}
	}

	return res;
}
