#include <stdio.h>
#include <stdlib.h>
typedef struct imagem_t
{
  char  tipo[100] ;
	int linhas;
	int colunas;
	int brancoMaximo;
	unsigned char **img;
} img_t;

img_t imagem;

/*void Entrada ()
{
	if (blah != "-i")
	{
		LeEntradaStdin();
	}
	else
	{
		LeEntradaArquivo();
	}
}
*/

//aloca memória para a imagem
void alocaMemoria ()
{
	imagem.img = malloc((imagem.linhas*2) * sizeof(unsigned char*));
	for (int i = 0; i < imagem.linhas; ++i)
	{
		imagem.img[i] = malloc((imagem.colunas*2 )* sizeof(unsigned char));
	}
}


img_t LeEntradaStdin()
{
	char comentario;
	//lê o tipo da entrada
	scanf ("%s", imagem.tipo);
	//se for uma p5, lê o comentário e ignora
	if (imagem.tipo[1]=='5')
	{
		scanf(" %c", &comentario);
		if (comentario == '#')
		{
			while (comentario!='\n')
			{
				scanf("%c",&comentario);
			}
		}
	}
	scanf ("%d %d",&imagem.linhas , &imagem.colunas);
	scanf ("%d", &imagem.brancoMaximo);
	alocaMemoria();
	//se é uma P2, lê com scanf
	if (imagem.tipo[1]=='2')
	{
		for (int i = 0; i < imagem.linhas; ++i)
		{
			for (int j = 0; j < imagem.colunas; j++)
			{
				scanf("%d ", &imagem.img[i][j]);
			}
			
		}
	}
	//se for binário, usa fread
	else
	{
		for (int i = 0; i < imagem.linhas; ++i)
		{
			fread (imagem.img[i], sizeof (unsigned char), imagem.colunas, stdin);
		}
	}
	return imagem;
}



void saida (img_t imagem)
{
	printf("%s\n",imagem.tipo );
	printf("%d %d\n",imagem.linhas,imagem.colunas );
	printf("%d\n",imagem.brancoMaximo );
	if (imagem.tipo[1]=='2')
	{
		for (int i = 0; i < imagem.linhas; ++i)
		{
			for (int j = 0; j < imagem.colunas; j++)
			{
				printf("%d ", imagem.img[i][j]);
			}
			printf("\n");
		}
	}
	else
	{
		for (int i = 0; i < imagem.linhas; ++i)
		{
			fwrite (imagem.img[i], sizeof (unsigned char), imagem.colunas, stdout);
		}
	}
}

int main(int argc, char const *argv[])
{
	img_t imagem;
	imagem = LeEntradaStdin();
	
	saida(imagem);
	return 0;
}