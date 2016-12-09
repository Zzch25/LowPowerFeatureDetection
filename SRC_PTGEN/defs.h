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
#define TRIPDIALOGUE 6
#define ARGSVIEWPAIR 2
#define MAXVAL 255
#define MINDISP 0
#define WINSZ 26
#define HALFWINSZ 13
#define BIGBUFF 8196
#define CSV_HEADER "Q1W,Q2W,Q3W,Q4W,Q1STD,Q2STD,Q3STD,Q4STD,QSTD,Q1_2STD,Q2_3STD,Q3_4STD,TYPE"

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

/*Generic coordinate holder for integers*/
struct icoords
{
	int x;
	int y;
	int z;
};

/*Data for generating disparity maps from view pairs*/
struct selectPoint
{
	int num;
	int val;
};

/*Data corresponding to a select point*/
struct selectInfo
{
	double Q1F;
	double Q2F;
	double Q3F;
	double Q4F;
	
	double Q1W;
	double Q2W;
	double Q3W;
	double Q4W;

	double Q1AVG;
	double Q2AVG;
	double Q3AVG;
	double Q4AVG;

	double Q1V;
	double Q2V;
	double Q3V;
	double Q4V;

	double Q1STD;
	double Q2STD;
	double Q3STD;
	double Q4STD;

	double Q1_2AVG;
	double Q2_3AVG;
	double Q3_4AVG;

	double Q1_2V;
	double Q2_3V;
	double Q3_4V;

	double Q1_2STD;
	double Q2_3STD;
	double Q3_4STD;

	double QV;
	double QAVG;
	double QSTD;
};

/*The data for generating dispairties from images*/
struct grayInfo
{
	int fMode;
	char *outFName;
	FILE *outfd;

	char *type;

	int sz;
	int winSZ;
	int maxVal;
	int col;
	int row;

	struct PGMStat image;
	struct selectInfo *elemsData;
	struct icoords *elemsLoc;
	struct selectPoint **elems;
};

/*Open a file descriptor*/
int openFD(char *path, int mode, FILE **fd);
/*Close a file descriptor*/
int closeFD(FILE *fd);
/*Scrub the data*/
int cleanData(struct grayInfo grayData);
/*Generate the map data from the user specifications*/
int initData(int argcIdx, char *argv[], struct grayInfo *grayData);
/*Write the resulting map data to outputs*/
int outCSV(struct grayInfo grayData);
/*Calculate the disparities from the view pairs*/
int bucketPoints(struct grayInfo grayData);
/*Load a pgm to a double array*/
int grayToDouble(struct PGMStat *inPGM);

#endif
