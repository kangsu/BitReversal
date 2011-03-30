#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "bitrev.h"

#define CLOCK 66.66666667e6

int main(int argc, char *argv[])
{

	struct timeval tv, tv2;
	double ttime;
	float *Xtemp, *X, *Y;
	float *Xt1, *Xt2, ftemp1, ftemp2, ftemp3, ftemp4;
	float *Ypoint, *Xpoint, *Xpoint2;
	long temp;
	int *index, i, n, a, b, c,  nbits;
	int lgn;
	int diff, lgnminus ;

	if(argc != 2)
	{
		printf("usage: example n\n");
		printf("Where 'n' is the log size of the bit-reverse being done.\n");
		printf("For example: 'example 15' is a 32k element bit-reverse\n");
		return(0);
	}
	lgn = atoi(argv[1]);
	n = 1 << lgn;

	printf("sizeof(float) = %d\n", sizeof(float));
	X = malloc(sizeof(float)*n);
	Y = malloc(sizeof(float)*n);
	Xtemp = malloc(sizeof(float) * SIZE2); 
	lgnminus = lgn-LOGSIZE;
	nbits = n >> (2*LOGSIZE);
	for(i = 0; i < n; i++)
	{
		X[i] = (float)i;
		Y[i] = -1.0;
	}

	gettimeofday(&tv, NULL);
	gettimeofday(&tv2, NULL);
	diff = tv2.tv_usec - tv.tv_usec;
	printf("the diff is = %d\n", diff);

	gettimeofday(&tv, NULL);

	bit_rev(Xtemp, X,Y,nbits, n, lgn);

	gettimeofday(&tv2, NULL);
	for(i = 0; i < 4; i++)
		printf("Y[%d] = %f\n", i, Y[i]);
	for(i = n-5; i < n; i++)
		printf("Y[%d] = %f\n", i, Y[i]);
	printf("Total time = %d secs %d usecs\n", tv2.tv_sec-tv.tv_sec, 
	 tv2.tv_usec-tv.tv_usec-diff);

        ttime = tv2.tv_sec - tv.tv_sec + (tv2.tv_usec - tv.tv_usec-diff)/1.0e6;

	printf("ttime = %lf\n", ttime);
	printf("Cycles per elements = %lf\n", (double)ttime/(double)n*CLOCK);
	printf("Given that you have a %lf MHz clock\n", CLOCK);
}
