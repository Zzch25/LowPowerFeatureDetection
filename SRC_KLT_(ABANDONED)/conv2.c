/*
 *Zachary Job
 *conv2.c
 *25/25/25
 */

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_fft_complex.h>

#ifdef __CYGWIN__
	#include <netpbm/pam.h>
#elif __linux
	#include <pam.h>
#endif

#include "defs.h"

/*
 *An interpretation of the Matlab conv2 function using GSL
 *
 *@PARAM: The data and structures to run and store the convolution steps and result
 *@PARAM: The matrix to process
 *@PARAM: The kernel to apply
 *@RETURN: The return code
 */
int conv2(struct conv2Data *ev, double *matIn, struct kernel kernel)
{
	/*
	 *The return code
	 *Generic iterator
	 *Generic iterator
	 *Height offset
	 *Width offset
	 *FFT intermediate for element-wise product
	 *FFT intermediate for element-wise product
	 *unreal FFT intermediate for element-wise product
	 *unreal FFT intermediate for element-wise product
	 */
	int res, i, j, hOffs, wOffs;
	double armReal, armReal2, armImag, armImag2;

	res = 0;

	/**********************/
	/*Finalize alloc*******/	
	/**********************/
	ev->heightFFT = ev->heightSrc + (kernel.height >> 1);
	ev->widthFFT = ev->widthSrc + (kernel.width >> 1);

	ev->fft = gsl_matrix_alloc(ev->heightFFT, (ev->widthFFT << 1));
	ev->fft2 = gsl_matrix_alloc(ev->heightFFT, (ev->widthFFT << 1));

	ev->wsColumn = gsl_fft_complex_workspace_alloc(ev->heightFFT);
	ev->wsLine = gsl_fft_complex_workspace_alloc(ev->widthFFT);
	ev->wvColumn = gsl_fft_complex_wavetable_alloc(ev->heightFFT);
	ev->wvLine = gsl_fft_complex_wavetable_alloc(ev->widthFFT);

	gsl_matrix_set_zero(ev->fft);
	gsl_matrix_set_zero(ev->fft2);

	/**********************/
	/*Circular convolution*/
	/**********************/

	for(i = 0; i < ev->heightSrc; i++)
	{
		for(j = 0; j < ev->widthSrc; j++)
			ev->fft->data[((i % ev->heightFFT) << 1) * ev->widthFFT + ((j % ev->widthFFT) << 1)] += matIn[i * ev->widthSrc + j];
	}

	for(i = 0; i < kernel.height; i++)
	{
		for(j = 0; j < kernel.width; j++)
			ev->fft->data[((i % ev->heightFFT) << 1) * ev->widthFFT + ((j % ev->widthFFT) << 1) + 1] += kernel.elems[i * kernel.width + j];
	}

	for(i = 0; i < ev->heightFFT; i++)
		gsl_fft_complex_forward(&((ev->fft)->data[(i << 1) * ev->widthFFT]), 1, ev->widthFFT, ev->wvLine, ev->wsLine);
    
	for(j = 0; j < ev->widthFFT; j++)
		gsl_fft_complex_forward(&ev->fft->data[j << 1], ev->widthFFT, ev->heightFFT, ev->wvColumn, ev->wsColumn);

	for(i = 0; i < ev->heightFFT; i++)
   {
		for(j = 0; j < ev->widthFFT; j++)
		{
			armReal = (ev->fft)->data[(i << 1) * ev->widthFFT + (j << 1)];
			armImag = (ev->fft)->data[(i << 1) * ev->widthFFT + (j << 1) + 1];
			armReal2 = (ev->fft)->data[(((ev->heightFFT - i) % ev->heightFFT) << 1) * ev->widthFFT + (((ev->widthFFT << 1) - (j << 1)) % (ev->widthFFT << 1))];
			armImag2 = -1 * (ev->fft)->data[(((ev->heightFFT - i) % ev->heightFFT) << 1) * ev->widthFFT + (((ev->widthFFT << 1) - (j << 1)) % (ev->widthFFT << 1)) + 1];

			ev->fft2->data[(i << 1) * ev->widthFFT + (j << 1)] = 0.5 * (armReal * armImag - armReal2 * armImag2);
			ev->fft2->data[(i << 1) * ev->widthFFT + (j << 1) + 1] = -0.25 * (armReal * armReal - armImag * armImag - armReal2 * armReal2 + armImag2 * armImag2);
		}
	}


	for(i = 0; i < ev->heightFFT; i++)
		gsl_fft_complex_inverse(&ev->fft2->data[(i << 1) * ev->widthFFT], 1, ev->widthFFT, ev->wvLine, ev->wsLine);

	for(j = 0; j < ev->widthFFT; j++)
		gsl_fft_complex_inverse(&ev->fft2->data[j << 1], ev->widthFFT, ev->heightFFT, ev->wvColumn, ev->wsColumn);
	
	/**********************/
	/*Extraction***********/	
	/**********************/
	hOffs = kernel.height >> 1;
	wOffs = kernel.width >> 1;

	for(i = 0; i < ev->heightRes; i++)
	{
		for(j = 0; j < ev->widthRes; j++)
			ev->elemsRes[i * ev->widthRes + j] = (ev->fft2)->data[((i + hOffs) << 1) * ev->widthFFT + ((j + wOffs) << 1)];
	}	

	return res;
}
