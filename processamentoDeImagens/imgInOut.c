#include "imgInOut.h"

img_t imagem;
img_t entrada (int argc,char **argv)
{
	//confere se é entrada padrão ou não
	img_t entry;
	if (argc == 1)
	{
		entry = LeEntradaStdin ();
	}

	else
	{
		int count=0, bool = 0;
		for (count = 0; count < argc; ++count)
		{
			if ((argv[count][0]=='-')&&(argv[count][1]=='i'))
			{
				entry = LeEntradaFile (argv[count+1]);
				bool = 1;
				break;
			}	
		}
		if (bool==0)
		{
			entry = LeEntradaStdin ();
		}
		
	}
	return (entry);
}



//aloca memória para a imagem
void alocaMemoria ()
{
	imagem.img = malloc((imagem.linhas*2) * sizeof(unsigned char*));
	for (int i = 0; i < imagem.linhas; ++i)
	{
		imagem.img[i] = malloc((imagem.colunas*2 )* sizeof(unsigned char));
	}
}

void liberaMemoria ()
{
	
	for (int i = 0; i < imagem.linhas; ++i)
	{
		free(imagem.img[i]);
	}
	free(imagem.img);
}

img_t LeEntradaFile(char* nomeArquivo)
{
	FILE *in;
	in = fopen(nomeArquivo, "r");


	if (!in)
	{
		perror ("Erro ao abrir a imagem!");
		exit (1);
	}
	char comentario;
	//lê o tipo da entrada
	fscanf (in,"%s", imagem.tipo);
	char aux[500];
	int aux2;
	//se for uma p5, lê o comentário e ignora
	fscanf(in,"%s", aux);
	aux2 = stringToInteger (aux);
	if (aux2 == '#'-'0')
		{
			fscanf(in," %c", &comentario);
				while (comentario!='\n')
				{
					fscanf(in,"%c",&comentario);

				}
				fscanf(in," %d %d",&imagem.colunas,&imagem.linhas);
			}
		else
		{
			imagem.colunas = aux2;
			fscanf(in," %d",&imagem.linhas);
		}
	fscanf (in,"%d", &imagem.brancoMaximo);
	alocaMemoria();
	//se é uma P2, lê com scanf
	if (imagem.tipo[1]=='2')
	{
		for (int i = 0; i < imagem.linhas; ++i)
		{
			for (int j = 0; j < imagem.colunas; j++)
			{
				fscanf(in," %d ", (int*)&imagem.img[i][j]);
			}
			
		}
	}
	//se for binário, usa fread
	else
	{
		for (int i = 0; i < imagem.linhas; ++i)
		{
			fread (imagem.img[i], sizeof (unsigned char), imagem.colunas, in);
		}
	}
	fclose (in) ;
	return imagem;

}

int stringToInteger (char* lim)
{
	int result = 0;
	int len = strlen (lim);
	for(int i=0; i<len; i++)
	{
		result = result * 10 + ( lim[i] - '0' );
	}
	return result;
}


img_t LeEntradaStdin()
{
	char comentario;
	//lê o tipo da entrada
	scanf ("%s", imagem.tipo);
	char aux[500];
	int aux2;
	//se for uma p5, lê o comentário e ignora
	scanf("%s", aux);
	aux2 = stringToInteger (aux);
	if (aux2 == '#'-'0')
		{
			scanf(" %c", &comentario);
				while (comentario!='\n')
				{
					scanf("%c",&comentario);

				}
				scanf (" %d %d",&imagem.colunas,&imagem.linhas);
			}
		else
		{
			imagem.colunas = aux2;
			scanf (" %d",&imagem.linhas);
		}	
	scanf ("%d", &imagem.brancoMaximo);
	alocaMemoria();
	//se é uma P2, lê com scanf
	if (imagem.tipo[1]=='2')
	{
		for (int i = 0; i < imagem.linhas; ++i)
		{
			for (int j = 0; j < imagem.colunas; j++)
			{
				scanf(" %d ", (int*)&imagem.img[i][j]);
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

void saida (img_t imagem, int argc,char **argv)
{
	//confere se é entrada padrão ou não
	if (argc == 1)
	{
		saidaStdout (imagem);
	}

	else
	{
		int count=0, bool = 0;
		for (count = 0; count < argc; ++count)
		{
			if ((argv[count][0]=='-')&&(argv[count][1]=='o'))
			{
				saidaFile (imagem, argv[count+1]);
				bool = 1;
				break;
			}	
		}
		if (bool==0)
		{
			saidaStdout (imagem);
		}		
	}
	void liberaMemoria ();
}



void saidaStdout (img_t imagem)
{
	printf("%s\n",imagem.tipo );
	printf("# filtro criado por Talita Halboth\n" );
	printf("%d %d\n",imagem.colunas,imagem.linhas  );
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

void saidaFile (img_t imagem,char* nomeArquivo)
{
	FILE *out;
	out = fopen(nomeArquivo, "w");

	if (!out)
	{
		perror ("Erro ao abrir o arquivo de destino!");
		exit (1);
	}
	fprintf(out,"%s\n",imagem.tipo );
	fprintf(out, "# filtro criado por Talita Halboth\n" );
	fprintf(out,"%d %d\n",imagem.colunas,imagem.linhas );
	fprintf(out,"%d\n",imagem.brancoMaximo );
	if (imagem.tipo[1]=='2')
	{
		for (int i = 0; i < imagem.linhas; ++i)
		{
			for (int j = 0; j < imagem.colunas; j++)
			{
				fprintf(out,"%d ", imagem.img[i][j]);
			}
			fprintf(out,"\n");
		}
	}
	else
	{
		for (int i = 0; i < imagem.linhas; ++i)
		{
			fwrite (imagem.img[i], sizeof (unsigned char), imagem.colunas, out);
		}
	}
	fclose(out);
}

