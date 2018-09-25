#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef unsigned long floatx;

union Floatx {	
		double in;	
		unsigned long final_num;
	} flx;

floatx doubleToFloatx(double in, int totBits, int expBits) 
{

	flx.in =  in;
		
	unsigned long out = flx.final_num;
	floatx final_val = 0;

	unsigned long fraction = out <<12;
	fraction = fraction >> 12;
	int fractionBits = totBits - expBits-1;
	unsigned long numberBitsShifted = 52 - fractionBits;
	
	if (flx.in < 0) 
	{
		final_val = 1UL << (totBits-1); //sign!
	}

	unsigned long exp = out << 1;
	exp = exp >> 53;


	exp = exp - (1023);
	exp = exp + (1UL << (expBits -1)) - 1;
	long exp_s = exp;

	long e_range = (1UL << expBits) -1;

	if (exp_s >= e_range) //infinity
	{
		exp = (1UL << expBits) - 1;
		exp = exp << fractionBits;
		final_val |= exp;
		return final_val;
	} 

	if(in  == 0)
	{ 
		return 0UL;
	}
	if (exp_s <= 0 && -exp_s > fractionBits) //too small
	{
		return final_val;

	} else if (exp_s <= 0) 
	{
		unsigned long bit_mask = 1UL << 52;
		fraction |= bit_mask;
		numberBitsShifted += -exp + 1;
		fraction = fraction >> (numberBitsShifted - 1);
		if (fraction & 1UL)
		{
			fraction = (fraction >> 1) + 1;
		} else 
		{
			fraction = fraction >> 1;
		}

	}else{
		exp = exp << fractionBits;
		final_val |= exp;
		
		fraction = fraction >> (numberBitsShifted - 1);
		if (fraction & 1UL)
		{
			fraction = (fraction >> 1) + 1;
		} else 
		{
			fraction = fraction >> 1;
		}
	}
	final_val |= fraction;	

	return final_val;
	
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
	
	



