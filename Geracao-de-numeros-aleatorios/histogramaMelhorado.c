//Talita Halboth Cunha Fernandes GRR20165399
#include <stdio.h>
#include "lcrandom.h"
long ValoresGerados[134456];

int main(int argc, char const *argv[])
{
	int numEstrelas;
	
	lcrandom_parms (8121, 28411, 134456);
	for (long i = 0; i <	10000000; ++i)
	{
		ValoresGerados[lcrandom()]++;
		
	}
	printf("%s","  " );
	for (int i = 0; i <= 10; ++i)
	{
		printf("%d        ",i*10 );
	}
	printf("\n");
	printf("%s","  +" );
	for (int i = 0; i < 10; ++i)
	{
		printf("%s","---------+" );
	}
	printf("\n");
	int maior = 0;
	for (int i = 0; i < 100; ++i)
	{
		if (ValoresGerados[i]> maior)
		{
			maior = ValoresGerados[i];
		}
	}

	for (int i = 0; i < 100; ++i)
	{
		if (i < 10)
		{
			printf(" ");
		}
		printf("%d|",i );
		numEstrelas=ValoresGerados[i]*100/maior;
		for (int i = 0; i < numEstrelas; ++i)
		{
			printf("*");
		}

		printf("\n");

	}

	return 0;
}