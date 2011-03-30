/* 
Function Name: bit_rev
Parameters: 
buffer) This is a pointer to a pre-allocated buffer of SIZE2 elements.
X) The source array.
Y) The destination array (must be preallocated).
nbits) The number of bits in n.
n) The number of elements in the source array you wish to bit-reverse.
lgn) log_2(n).
Returns: Nothing (void)
Side Effects: The X array is unchanged.  The Y array returns with the bit-
reverse of the X array.  The contents of buffer are undefined.
Warnings:  The code only works for problems that have at least SIZE2 elements.
If there are fewer elements then a different in-cache routine should be called 
(not only for correctness, but for speed). */
void bit_rev(float *buffer, float *X, float *Y, int nbits, int n, int lgn);

/* 
Function Name: logn
Paramters:
n) The value we are computing on.
Returns: log_2(n)
Side Effects: None
Warnings: None that I can remember */
int logn(int n);

/* 
Function Name: bitrev
Parameters: 
x) The value we are computing the bitreverse of.
logn) The number of bits with respect to x.
Returns:  The bitreverse of x with respect to logn bits.
Side Effects: None
Warnings: None that I can remember, except the code is kinda slow. */
int bitrev(int x, int logn);


/* Function Name: incachebitrev
This is just a dummy naive code that performs bit-reversals when the
arrays fit in cache */
void incachebitrev(float *X, float *Y, int nbits, int n, int lgn);
