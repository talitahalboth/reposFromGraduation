#include <stdio.h>
#include <stdlib.h>
#include "imgInOut.h"
#include "linhaDeComando.h"

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


int main (int argc, char **argv, char **envp)
{
	img_t imagem;
	int count;

	imagem = entrada (argc,argv);
	pgmNegativo(&imagem);

	saida (imagem,argc,argv);
	return 0;
}