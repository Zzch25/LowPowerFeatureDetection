/*
 *Zachary Job
 *conv2Clean.c
 *25/25/25
 */

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_fft_complex.h>

#include "defs.h"

/*
 *Clean the conv2 data
 *
 *@PARAM: The structure to clean
 *@RETURN: The return code
 */
int conv2Clean(struct conv2Data *ev)
{
	/*
	 *The return code
	 */
	int res;

	res = 0;

	if(ev != 0 && ev != NULL)
	{
		gsl_fft_complex_workspace_free(ev->wsColumn);
		gsl_fft_complex_workspace_free(ev->wsLine);
		gsl_fft_complex_wavetable_free(ev->wvColumn);
		gsl_fft_complex_wavetable_free(ev->wvLine);
		
		gsl_matrix_free(ev->fft);
		gsl_matrix_free(ev->fft2);

		if(ev->elemsRes != 0 && ev->elemsRes != NULL)
			free(ev->elemsRes);

		ev->heightSrc = 0;
		ev->widthSrc = 0;
		ev->heightFFT = 0;
		ev->widthFFT = 0;
		ev->heightRes = 0;
		ev->widthRes = 0;
	}
	else
		res = 1;

	return res;
}
