//Talita Halboth Cunha Fernandes GRR20165399
#include <stdio.h>
#include "lcrandom.h"

int valoresGerados[10000000];
long CalculaPeriodo (long a,long c,long m)
{
	
	lcrandom_parms (a, c, m);
	int x,cont=0;
	for (int i = 0; i < m; ++i)
	{
		valoresGerados[i]=0;
	}
	x=lcrandom();
	while (!valoresGerados[x])
	{
		valoresGerados[x]=1;
		x=lcrandom();
		++cont;
	}
	for (int i = 0; i < m; ++i)
	{
		valoresGerados[i]=0;
	}
	x=lcrandom();
	cont = 0;
	while (!valoresGerados[x])
	{
		valoresGerados[x]=1;
		x=lcrandom();
		++cont;
	}

	return (cont);
}

int main()
{
	printf("Período para o caso padrão : %li\n", CalculaPeriodo (40692, 127, 10000000));
	printf("Período para caso melhorado, com multiplicador = 8121, incremento = 28411, e módulo = 134456: %li\n", 
		CalculaPeriodo (8121, 28411,134456));
	return 0;
}