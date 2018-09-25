#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

typedef unsigned long floatx;

		
floatx doubleToFloatx(double in, int totBits, int expBits) 
{

	//double in is the number that you are trying to disect and change into a floatx
	
	int in_copy;
	double fraction;
	int bin_int;
	int bin_fract;
	int placement = 1;
	in_copy = (int) in;
	fraction = in - (in_copy);
	floatx floatNum = 0;


	while (0 < in_copy)

	{
		bin_int = (bin_int + in_copy) % 2 * placement;
		placement = placement * 10;
		in_copy = in_copy/2;
		floatNum |= (bin_int << ((totBits-1) - (expBits)));
		printf("bin_int: %d\n", bin_int);
	}	
	//Now need to set the fraction bits. Don't forget about the sign.

	for (int k = 0; k < expBits; k++)
	{
		
		if ((fraction * 2) < 1) 
		{
			bin_fract = 0 >> k;

		} 
		else if ((fraction * 2) == 1)
		{
			bin_fract = 1UL >> k;
		}

		fraction = fraction * 2;	
		floatNum |= (bin_fract) << (totBits -1);
	}
	
 

	return floatNum;

}


int main(int argc, char** argv) 
{

	int totBits = atoi(argv[1]);

	int expBits = atoi(argv[2]);

	if (!(totBits > 2) || !(totBits < 65)) 
	{
		printf("Invalid # of bits.\n");
		return -1;
	}

	if (!(expBits > 0) || !(expBits <= (totBits - 2)))
	{
		printf("Invalid # of exponent bits.\n");
		return -1;
	}


	while(!feof(stdin)) {
		double in=NAN; // NAN defined in math.h
		if(1==scanf("%lf ",&in)) {
		floatx fx = doubleToFloatx(in,totBits,expBits);
		printf("%14.8g = floatx(%d,%d) : %016lx\n",in,totBits,expBits,fx);
		} else {
			char buf[100];
			scanf("%s ",buf);
			printf("Input : %s not recognized as a double\n",buf);
		}
	}


	return 0;
}
	
	



