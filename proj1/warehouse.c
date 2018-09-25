#include "order.h"
#include "bench.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char **argv) {
	
	if (argc<2) 
	{
		printf("Please invoke as %s <order_file>\n",argv[0]);
		return 1;
	}
	if (!openOrder(argv[1])) 
	{
		return 1;
	}

	int binsUsed[4][1] = {0};
	int binSlot = 0;
	int s_bin_val = 0;
	int pn = nextPartNumber();
	int bin = pn/10;
	
	fetchBin(bin, binSlot);

	while (fetchNextPart()) 
	{
		
		pn = nextPartNumber();
		bin = pn/10;


		for (int i = 0; i < 5; i++) 
		{

			if (binInSlot(i) == bin) {
				binSlot = i;
				binsUsed[binSlot][1]++;
				binsUsed[binSlot][0] = bin;
				break;

			}
			else if (binInSlot(i) == -1)
			{
				binSlot = i;
				fetchBin(bin, i);
				binsUsed[binSlot][1]++;
				binsUsed[binSlot][0] = bin;
				break;

			}
			


		} 
	
		
		if ((binInSlot(4) != -1) &&( binInSlot(binSlot) != bin)) {
				
			if (binsUsed[2][1] <= binsUsed[3][1])
			 {
				s_bin_val = 2;
				//binsUsed[2][1] = 0;
				//binsUsed[2][0] = 0;
				
			}
			else if (binsUsed[3][1] <= binsUsed[4][1])
			 {
					
				s_bin_val = 3;
						
				
				binsUsed[3][1] = 0;
				binsUsed[3][0] = 0;
				binsUsed[4][1] = 0;
				binsUsed[4][0] = 0;
			}
		
			binSlot =  s_bin_val;
			fetchBin(bin,s_bin_val);
					
							
			

			
			
			
		}




	}

	closeOrder();
	return 0;
}
