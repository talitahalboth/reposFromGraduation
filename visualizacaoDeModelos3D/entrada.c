#include "entrada.h"
#include "struct.h"




int booleano;

void entry( int argc, char **argv)
{
	booleano = 0;
	alocaMemoria ();
	entrada (argc, argv);
	allocaAresta ();
}

void entrada ( int argc, char **argv)
{
	if (argc == 1)
		entradaStdin ();
	else
		entradaFile (argv[1]);
}

void entradaStdin ()
{
	char c[1000],comentario[1000];
	while (scanf ("%s", c) != EOF)
	{
		if (strcmp(c, "v")==0 )
		{

				leVerticestdin ();			
		}
		else if (strcmp(c, "f")==0 )
		{
			leFacestdin ();
			while (booleano == 1)
			{
				booleano = 0;
				leFacestdin ();
			}

		}
		else
		{
			if (scanf ("%[^\n]",comentario )== EOF)
			{
				break;
			}
		}
	}
}

void entradaFile (char* nomeArquivo)
{
	in = fopen(nomeArquivo, "r");
	if (!in)
	{
		perror ("Erro ao abrir a imagem!");
		exit (1);
	}

	char c[1000],comentario[1000];

	while (fscanf (in,"%s", c) != EOF)
	{
		if (strcmp(c, "v")==0 )
		{

				leVerticeFile ();			
		}
		else if (strcmp(c, "f")==0 )
		{
			leFacefile ();
			while (booleano == 1)
			{
				booleano = 0;
				leFacefile ();
			}

		}
		else
		{
			if (fscanf (in,"%[^\n]",comentario )== EOF)
			{
				break;
			}
		}
	}

}

void alocaMemoria ()
{
	object.f = malloc (mallocSize*sizeof (face));
	object.fAlloc = mallocSize;
	object.fsize = 0;
	object.v = malloc (mallocSize*sizeof (vertice));
	object.vAlloc = mallocSize;
	object.vsize = 0;

}

void allocaAresta ()
{

	if (!(object.a = calloc (object.vsize+2,sizeof(*object.a))))
	{
		printf ("Não coseguiu alocar a memória necessária");
		return;
	}
	for (int i = 0; i < object.vsize+2; ++i)
	{
		if (!(object.a[i] = calloc (object.vsize+2,sizeof(unsigned int))))
		{
			printf ("Não coseguiu alocar a memória necessária");
			return;

		}
	}

}

void reallocF ()
{
	object.fAlloc+=mallocSize;
	object.f = realloc (object.f, (object.fAlloc)*sizeof (face));
}
void reallocV ()
{
	object.vAlloc+=mallocSize;
	object.v = realloc (object.v, (object.vAlloc + mallocSize)*sizeof (vertice));
}

void leFacestdin ()
{
	int i = 0,a;
	char c;
	c=0;
	object.fsize++;
	if (object.fsize >= object.fAlloc)
	{
		reallocF ();
	}
	while(scanf ("%c", &c) != EOF)
	{
		if (c == '\n' || c=='f')
		{
			break;
		}
		if(scanf(" %d/%*[^ \n]*c", &a) > 0)
		{			
			object.f[object.fsize].vertices[i]=a;
			i++;		
		}	

	}
	object.f[object.fsize].vertices[i]=object.f[object.fsize].vertices[0];
	object.f[object.fsize].vertices[i+1]=0;

	if (c=='f')
	{
		booleano = 1;
	}

}

void leFacefile ()
{
	int i = 0,a;
	char c;
	c=0;
	object.fsize++;
	if (object.fsize >= object.fAlloc)
	{
		reallocF ();
	}
	while(fscanf (in,"%c", &c) != EOF)
	{
		if (c == '\n' || c=='f')
		{
			break;
		}
		if(fscanf (in," %d/%*[^ \n]*c", &a) > 0)
		{			
			object.f[object.fsize].vertices[i]=a;
			i++;		
		}
		

	}
	object.f[object.fsize].vertices[i]=object.f[object.fsize].vertices[0];
	object.f[object.fsize].vertices[i+1]=0;

	if (c=='f')
	{
		booleano = 1;
	}

}


void leVerticestdin ()
{
	if (object.vsize >= object.vAlloc)
	{
		reallocV ();
	}
	scanf ("%lf %lf %lf", &object.v[object.vsize].x, &object.v[object.vsize].y, &object.v[object.vsize].z);
	object.vsize++;
}

void leVerticeFile ()
{
	if (object.vsize >= object.vAlloc)
	{
		reallocV ();
	}
	fscanf (in,"%lf %lf %lf", &object.v[object.vsize].x, &object.v[object.vsize].y, &object.v[object.vsize].z);
	object.vsize++;
}


void liberaMemoria ()
{
	free (object.v);
	free (object.f);

	for (int i = 0; i < object.vsize+2; ++i)	
		free(object.a[i]);
	free (object.a);

}