//Talita Halboth Cunha Fernandes GRR20165399
#include <stdio.h>
#include "lcrandom.h"
long ValoresGerados[100];

void histograma (long m,long a,long c)
{
		int numEstrelas;
	
	for (int i = 0; i < 100; ++i)
	{
		//inicializa o vetor de número gerados
		ValoresGerados[i]=0; 
	}

	lcrandom_parms (a, c, m); //passa os parâmetros para a função
	for (long i = 0; i <	1000000; ++i)
	{
		//incrementa em um a posição do vetor do valor gerado "aleatoriamente"
		ValoresGerados[lcrandom()%100]++; // %100 -> gera números entre [0..99]
	}
	//trata a impressão do histograma:
	printf("%s","  " );
	for (int i = 0; i <= 10; ++i)
	{
		printf("%d   ",i*10 );
	}
	printf("\n");
	printf("%s","  +" );
	for (int i = 0; i < 10; ++i)
	{
		printf("%s","----+" );
	}
	printf("\n");
	int maior = 0;
	for (int i = 0; i < 100; ++i)
	{
		if (ValoresGerados[i]> maior)
		{
			//encontra o maior valor gerado, para normalizar os resultados
			maior = ValoresGerados[i]; 
		}
	}

	printf("%s\n"," ");
	for (int i = 0; i < 100; ++i) 
	{
		if (i < 10)
		{
			//imprime espaços antes dos números menores que 10, estética.
			printf(" ");
		}
		printf("%d|",i );
		numEstrelas=ValoresGerados[i]*100/(maior*2); 
		//imprime uma estrela para cada 2 unidades
		for (int i = 0; i < numEstrelas; ++i)
		{
			printf("*");
		}

		printf("\n");

	}
}

int main(int argc, char const *argv[])
{

	//faz o histograma para o caso padrão:
	printf("Histograma com multiplicador 40692, incremento de 127 e módulo de 10000000 \n\n");
	histograma (10000000, 40692, 127);
	printf("\n\n");
	//faz o histograma para um caso melhorado:
	printf("Histograma com multiplicador 28411, incremento de 134456 e módulo de 8121 \n\n"); 
	histograma (134456, 8121, 28411);

	return 0;
}