test : floatx
	./floatx 32 8 <test1.txt
	./floatx 32 8 <test2.txt
	./floatx 31 8 <test3.txt
	./floatx 3 1 <test4.txt

floatx : floatx.c 
	gcc -Wall -g -o floatx floatx.c
	
clean :
	-rm floatx
