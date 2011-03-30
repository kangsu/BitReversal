#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int size, line, i, j, size2;
	int cache, cacheline;
	FILE *fp, *fp2;

	system("cp _bitrev.h bitrev.h");	
	fp2 = fopen(argv[1], "w");
	fp = fopen("bitrev.h", "a");

	printf("sizeof float = %d\n", sizeof(float));
	printf("What is the size of cache (in Kbytes)?\n");
	scanf("%d", &size);
	printf("How many bytes are there in a cache line?\n");
	scanf("%d", &line);
	cacheline = line/sizeof(float);

	size = size * 1024;
	size = size/sizeof(float);
	cache = size;
	size = size/2;
	line = cacheline * cacheline;
	if(cache < line) 
	{
		printf("Cache efficient algorithm not possible... sorry\n");
		exit(-1);
	}
	

	size = logn(size);
	size = size - (size % 2);
	size = size/2;
	size2 = 1 << size;
	while(size2 < cacheline)
	{
		size++;
		size2 = 1 << size;
	}

	printf("size = %d, line = %d\n", size, line);

	fprintf(fp, "#define LOGSIZE %d\n", size);
	fprintf(fp, "#define SIZE %d\n", size2);
	fprintf(fp, "#define SIZE2 %d\n", size2 * size2);
	fprintf(fp2, "int bittable[%d] = { ", size2);
	for(i = 0; i < size2; i++)
	{
		if(i != 0) fprintf(fp2, ", ");
		j = bitrev(i, size);
		fprintf(fp2, "%d", j);
	}
	fprintf(fp2, "};\n");
	fclose(fp);
	fclose(fp2);
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
