#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "bitrev.h"
#include "bitrev2.h"


void bit_rev(float *buffer, float *X, float *Y, int nbits, int n, int lgn)
{
    float ftemp1, ftemp2, ftemp3, ftemp4;
    int a, b, c, lgnminus;
    int aprime, bprime, bshift, bprimeshift, lgnstep;
    float *Xt1, *Xt2, *Ypoint, *Xpoint;

    if(lgn < 2*LOGSIZE)
    {
        incachebitrev(X, Y, nbits, n, lgn);
        return;
    }

    lgnminus = lgn-LOGSIZE;
    lgnstep = 1 << lgnminus;
    for(b = 0; b < nbits; b++)
    {
        bprime = bitrev(b, logn(nbits));   
        bshift = b << LOGSIZE;
        bprimeshift = bprime << LOGSIZE;
        Xt1 = &X[bshift];
        for(a = 0; a < SIZE; a++, Xt1 += lgnstep)
        {
            aprime = bittable[a];
            Xt2 = &buffer[aprime << LOGSIZE];
/******************************************************************
   This part coming up is where we move the data into the buffer.
   We unrolled 4 times and load data into scalars to avoid some alias problems 
   and to mask latency.  
******************************************************************/
            for(c = 0; c < SIZE; c += 4)
            {
                ftemp1 = Xt1[c];
                ftemp2 = Xt1[c+1];
                ftemp3 = Xt1[c+2];
                ftemp4 = Xt1[c+3];
                Xt2[c] = ftemp1;
                Xt2[c+1] = ftemp2;
                Xt2[c+2] = ftemp3;
                Xt2[c+3] = ftemp4;
            }
        }
        for(c = 0; c < SIZE; c++)
        {
            Ypoint = &Y[(bittable[c] << (lgnminus)) | bprimeshift];
            Xpoint = &buffer[c];

/***************************************************************
  Here we move the data from the buffer which should be in cache to
  the output array.  Notice that the addressing on the array buffer is
  surprisingly simple and despite the fact that we aren't making unit
  strides is irrelevant since it is all in cache.  Also this loop is 
  unrolled 8 times.
******************************************************************/
            for(aprime = 0; aprime < SIZE; aprime += 8, Xpoint += (SIZE*8))
            { 
                Ypoint[aprime] = Xpoint[0];
                Ypoint[aprime+1] = Xpoint[SIZE];
                Ypoint[aprime+2] = Xpoint[2*SIZE];
                Ypoint[aprime+3] = Xpoint[3*SIZE];
                Ypoint[aprime+4] = Xpoint[4*SIZE];
                Ypoint[aprime+5] = Xpoint[5*SIZE];
                Ypoint[aprime+6] = Xpoint[6*SIZE];
                Ypoint[aprime+7] = Xpoint[7*SIZE];
            } 

        }
    }

}

int logn(int n)
{
    int i = 0;
    n = n -1;
    while(n > 0)
    {
        i++;
        n = n >> 1;
    }
    return(i);
}
    

int bitrev(int x, int lgn)
{
    int i, t, value;

    value = 0;


    for(i = lgn-1; i >= 0; i--)     
    {
        t = 1 & x;
        value = (value | (t << i));
        x = x >> 1;
    }
        
    return(value);
}

void incachebitrev(float *X, float *Y, int nbits, int n, int lgn)
{
    int i, bitrevi;

/**** Printfs warning user that this bitreverse algorithm is not tuned *****/

    printf("This code is not at all tuned and not part of COBRA.\n");  
    printf("In fact this is a very naive implementation.\n");
    printf("We suggest putting in your own in-cache bit-reversal here ");
    printf("for robust performance.\n");
    printf("This code can be found in the bottom of file bitrev.c.\n");
    printf("These printfs can be removed with no ill effect.\n");

    Y[0] = X[0];
    Y[n-1] = X[n-1];
    for(i = 1; i < n-1; i++)
    {
        bitrevi = bitrev(i, lgn);
        if(bitrevi < i) continue;
        Y[i] = X[bitrevi];
        Y[bitrevi] = X[i];
    }
    return;
}
