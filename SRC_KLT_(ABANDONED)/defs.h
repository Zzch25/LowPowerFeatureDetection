/*
 *Zachary Job
 *defs.h
 *4/15/2015
 */

#ifndef _DEFS_
#define _DEFS_

#ifdef __CYGWIN__
	#include <netpbm/pam.h>
#elif __linux
	#include <pam.h>
#endif

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_fft_complex.h>

/*General definitions*/
#define x_min(x,y) ((x)<(y)?(x):(y))
#define x_max(x,y) ((x)>(y)?(x):(y))
#define x_sign(a, b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
#define x_abs(x) (x<0)?-x:x
#define x_sqr(x) (x * x)
#define x_sqrrt(x) (x / x)
#define True 1
#define False 0
#define Updated 2
#define MAXWINDOW 32
#define BASELINE 9
#define DERIVWINSZ 3
#define GAUSSWINSZ 5
#define SUPPRWINSIZE 3
#define SADWINSZ 3
#define TRANSZ 9
#define MAXVAL 25
#define MAXCMP 5
#define PERCENTINC 5
#define HARRISTHRESH 3500
#define SADREJECT 50
#define HARRISK 0.00004

/*libnetpbm*/
#define WRITEASCII 1
#define  WRITEBIN 0

/*File ops*/
#define NEWFILE 0
#define APPENDFILE 1
#define READFILE 2

/*Instance specific definitions given the example is a basic four point homography although the functionality could be expanded*/
#define ORGIMGPATHL "../IMG/"
#define ORGIMGPATHR "../IMG/"
#define ORGIMGL "teddyL.pgm" 
#define ORGIMGR "teddyR.pgm"
#define TRUTHIMG "disp2.pgm"
#define NEWIMGPATH "../IMG/"
#define NEWIMG1 "dispP1.pgm"
#define NEWIMG2 "dispP2.pgm"

/*PGM load information*/
struct PGMStat
{
	int row;
	int col;
	pixval maxVal;
	gray **elems;
};

/*derivative map information - T E M P O R A R Y - For compilation*/
struct derivMap
{
	int row;
	int col;
	int *elems;
};

/*All the required convolution data for the gsl convolution*/
struct conv2Data
{
	/*Matrix dimensions for the various structures*/
	int heightSrc, widthSrc;
	int heightFFT, widthFFT;
	int heightRes, widthRes;
	/*The matricies and various structures*/
	gsl_matrix *fft, *fft2;
	gsl_fft_complex_wavetable *wvColumn, *wvLine;
	gsl_fft_complex_workspace *wsColumn, *wsLine;
	/*The result structure*/
	double *elemsRes;
};

/*The data pertaining to a gaussian kernel*/
struct kernel
{
	int height;
	int width;
	char isLocal;
	double *elems;
};

/*The harris operation needed information*/
struct harrisData
{
	double *iX;
	double *iY;
	double *iX2;
	double *iY2;
	double *iXY;
	double *elems;
	double *elemsU;

	double thresh;
	int height;
	int width;
	int supprWin;
};

/*Harris corner oepration parameters*/
struct opParam
{
	int thresh;
	
	int derivWin;
	int gaussWin;
	int supprWin;
	
	int isLocal;
	double *derivKernelL;
	double *derivKernelR;
};

/*Generic coordinate holder for integers*/
struct icoords
{
	int x;
	int y;
	int z;
};

/*So that qsort may process the data*/
struct SADQSortable
{
	struct icoords locL;
	struct icoords locR;
	double val;
};

/*SAD infomration and parameters*/
struct SADData
{
	int winSz;
	int maxElems;
	int totalElems;
	int rejectCap;

	struct SADQSortable *elems;
};

/*Open a file descriptor*/
int openFD(char *path, char *name, int mode, FILE **fd);
/*Close a file descriptor*/
int closeFD(FILE *fd);
/*Generate the harris operator output from derived information*/
int harrisOperation(struct harrisData *hData);
/*Perfom a 2D convolution similar to Matlab*/
int conv2(struct conv2Data *ev, double *matIn, struct kernel kernel);
/*Initialize the convolution data*/
int conv2Init(struct conv2Data *ev, int height, int width);
/*Clean the convolution data*/
int conv2Clean(struct conv2Data *ev);
/*Matrix multiplication*/
void elemXplyMx(double *m1, double *m2, int width, int height, double *mRes);
/*Get the relevant gaussian kernel*/
int genGaussKernel(double *in, int sz, struct kernel *kernelOut);
/*Translate a gray matrix to a flat double*/
int grayToDouble(struct PGMStat inPGM, double **outDouble);
/*scrub a kernel*/
int kernClean(struct kernel *kern);
/*setup a kernel*/
int kernInit(struct kernel *kern, int height, int width, int local, double *mask);
/*Get the haris corner map*/
int getMap(struct PGMStat inPGM, struct harrisData *hData, struct opParam params);
/*Perform the SAD operation of the data*/
int SADOperation(struct harrisData hDataL, struct harrisData hDataR, struct SADData *sData);
/*Compare function for qsort*/
int cmpQSort(const void *in1, const void *in2);

#endif
