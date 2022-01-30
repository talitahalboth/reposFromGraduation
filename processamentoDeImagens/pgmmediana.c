#include <stdlib.h>
#include "imgInOut.h"
img_t imagem,imgMedia;

void pgmMedia (img_t imagem, img_t* imgMedia);
int mediana (img_t imagem, int posi, int posj);
void copia (img_t* dest, img_t src);
void aloca ();
void ordena (int v[9],int tam);


int main (int argc, char **argv, char **envp)
{
	imagem = entrada (argc,argv);
	aloca ();
	pgmMedia(imagem, &imgMedia);
	copia (&imagem, imgMedia);
	saida (imagem,argc,argv);

	for (int i = 0; i < imagem.linhas; ++i)
	{
		free(imgMedia.img[i]);
	}
	free(imgMedia.img);
	return 0;
}

void pgmMedia (img_t imagem, img_t* imgMedia)
{
	for (int i = 0; i < imagem.linhas; ++i)
	{
		for( int j = 0; j < imagem.colunas ; ++j)
		{
			imgMedia->img[i][j]=mediana(imagem,i,j);
		}
	}

}


void ordena (int v[9],int tam)
{
	int aux;
	for (int i = 0; i < tam; ++i)
		for (int j = i+1; j < tam; ++j)
			if (v[i]>v[j])
			{
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
}

int mediana (img_t imagem, int posi, int posj)
{
	int v[9],k=0,tam;
	for (int i = 0; i < 9; ++i)
	{
		v[i]=1000;
	}
	for (int i = ((posi == 0) ? 0 : (posi - 1) ); i <= ((posi == imagem.linhas-1) ? imagem.linhas-1:(posi + 1)); ++i)
	{
		for (int j = ((posj == 0 )? 0 : (posj - 1)); j <= ((posj == imagem.colunas-1) ? imagem.colunas-1 :(posj + 1)); ++j)
		{
			v[k]=imagem.img[i][j];
			k++;
		}
	}
	for (int i = 0; i < 9; ++i)
	{
		if (v[i]==1000)
		{
			tam=i+1;
			break;
		}
	}
	ordena(v,tam);
	if (tam%2==0)
		return ((v[tam/2]+v[(tam/2)-1])/2);
	else
		return (v[tam/2]);


}

void copia (img_t* dest, img_t src)
{
	for (int i = 0; i < dest->linhas; ++i)
	{
		for( int j = 0; j < dest->colunas; ++j)
		{
			dest->img[i][j]=src.img[i][j];
		}
	}

}


void aloca ()
{
	imgMedia.img = malloc((imagem.linhas*2) * sizeof(unsigned char*));
	for (int i = 0; i < imagem.linhas; ++i)
	{
		imgMedia.img[i] = malloc((imagem.colunas*2 )* sizeof(unsigned char));
	}
}