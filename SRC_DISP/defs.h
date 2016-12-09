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

/*General definitions*/
#define m_min(x,y) ((x)<(y)?(x):(y))
#define m_max(x,y) ((x)>(y)?(x):(y))
#define m_sign(a, b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
#define m_abs(x) (x<0)?-x:x
#define fpow2(x) (x * x)
#define m_sqrrt(x) (x / x)
#define True 1
#define False 0
#define Updated 2

/*libnetpbm*/
#define WRITEASCII 1
#define WRITEBIN 0
#define MAXGRAY 85
#define GRAYTOP 255

/*File ops*/
#define NEWFILE 0
#define NEWFILE_OPT "wb+"
#define APPENDFILE 1
#define APPENDFILE_OPT "ab+"
#define READFILE 2
#define READFILE_OPT "r"

/*Instance specific*/
/*Loading*/
#define TRIPDIALOGUE 5
#define ARGSVIEWPAIR 5
/*Size information*/
#define MMTOM 1000
/*Disparity calculation*/
#define WINSZ 11
#define TRANSZ 11
#define MAXVAL 255
#define MINDISP 0
#define CONFIDENCE 0.9997

/*PPM load information*/
struct PPMStat
{
	char *fName;
	FILE *fd;

	int row;
	int col;
	pixval maxVal;
	unsigned short *rElems;
	unsigned short *gElems;
	unsigned short *bElems;
};

/*PGM load information*/
struct PGMStat
{
	char *fName;
	FILE *fd;

	int row;
	int col;
	pixval maxVal;
	double *gElems;
};

/*Data for generating disparity maps from view pairs*/
struct viewPairPoint
{
	double focallength;
	double baseline;
	struct PGMStat elemL;
	struct PGMStat elemR;
};

/*The data for generating dispairties from images*/
struct grayInfo
{
	int sz;
	int winSZ;
	int transSZ;
	double confidence;
	struct PGMStat *elems;
	struct viewPairPoint *viewPairInfo;
};

/*For generation disparity rank maps*/
struct rankMap
{
	int row;
	int col;
	int *elems;
};

/*Generic coordinate holder for integers*/
struct dcoords
{
	double x;
	double y;
	double z;
};

/*Open a file descriptor*/
int openFD(char *path, int mode, FILE **fd);
/*Close a file descriptor*/
int closeFD(FILE *fd);
/*Translate a gray matrix to a flat double*/
int grayToDouble(struct PGMStat *inPGM);
/*Scrub the data*/
int cleanData(struct grayInfo grayData);
/*Generate the map data from the user specifications*/
int initData(int argcIdx, char *argv[], struct grayInfo *grayData);
/*Write the resulting map data to outputs*/
int outGray(struct grayInfo grayData);
/*Calculate the disparities from the view pairs*/
int viewPairsToDisps(struct grayInfo grayData);
/*Generate a disparity map using a super basic winner take all algorithm*/
int stereo(struct viewPairPoint *images, struct PGMStat *outPGM, struct grayInfo grayData);
/*Compute the SAD of a pixel and its window*/
int SAD(struct rankMap *inRML, struct rankMap *inRMR, struct dcoords pixel, int windowSz, double *score, double *lastScore);
/*Generate rank maps for SAD*/
int rankTransform(struct PGMStat *inPGML, struct PGMStat *inPGMR, struct rankMap *outRML, struct rankMap *outRMR, int windowSz);

#endif
