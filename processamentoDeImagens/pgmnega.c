#include <stdio.h>
#include <stdlib.h>
#include "imgInOut.h"


void pgmNegativo (img_t *imagem);

int main (int argc, char **argv, char **envp)
{
	img_t imagem;

	imagem = entrada (argc,argv);
	pgmNegativo(&imagem);

	saida (imagem,argc,argv);
	return 0;
}

void pgmNegativo (img_t *imagem)
{
	for (int i = 0; i < imagem->linhas; ++i)
	{
		for( int j = 0; j < imagem->colunas; ++j)
		{
			imagem->img[i][j]=imagem->brancoMaximo-imagem->img[i][j];
		}
	}
}