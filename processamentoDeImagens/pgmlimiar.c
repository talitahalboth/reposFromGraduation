#include <stdio.h>
#include <string.h>
#include "imgInOut.h"
#include "limiar.h"

void filtroLimiar (img_t *imagem, int limite);
int limiteInteger (char* lim);

int main (int argc, char **argv, char **envp)
{
	img_t imagem;
	int limite;
	
	imagem = entrada (argc,argv);
	limite = limiteInteger( limiar (argc,argv));
	limite = (imagem.brancoMaximo *limite)/100; 
	filtroLimiar (&imagem, limite);
	saida (imagem,argc,argv);
	return 0;
}

int limiteInteger (char* lim)
{
	int result = 0;
	int len = strlen (lim);
	for(int i=0; i<len; i++)
	{
		result = result * 10 + ( lim[i] - '0' );
	}
	return result;
}

void filtroLimiar (img_t *imagem, int limite)
{
	for (int i = 0; i < imagem->linhas; ++i)
	{
		for( int j = 0; j < imagem->colunas; ++j)
		{
			imagem->img[i][j]=imagem->img[i][j] >= limite ? imagem->brancoMaximo : 0;
		}
	}
}