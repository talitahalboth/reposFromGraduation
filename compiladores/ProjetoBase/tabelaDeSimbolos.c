#include "tabelaDeSimbolos.h"


void inicializaTS(ts *p)
{
	p->topo = 0;
}

// passa todos os parametros
void inicializasSimbolo (ssimbolo *s, 
	const char *ident,
	int tipo,
	int categoria,
	int nivel,
	int deslocamento,
	int passagem,
	char* rotulo,
	int numeroParametros)
{
	strcpy(s->identificador, ident);
	s->tipo = tipo;
	s->categoria = categoria;
	s->nivel = nivel;
	s->deslocamento = deslocamento;
	s->passagem = passagem;
	strcpy(rotulo, s->rotulo);
	s->numeroParametros = numeroParametros;
	s->memoriaAlocada = 0;
}
// so passa parametros que parametro simples tem
void inicializasSimboloFunc(ssimbolo *s, 
	const char *ident,
	int nivel,
	char *rotulo)
{
	strcpy(s->identificador, ident);
	s->tipo = NONE;
	s->categoria = FUNCAO;
	s->nivel = nivel;
	s->deslocamento = -1;
	strcpy(s->rotulo,rotulo);
	s->memoriaAlocada = 0;
	s->passagem = 0;
}
// so passa parametros que parametro simples tem
void inicializasSimboloProc(ssimbolo *s, 
	const char *ident,
	int nivel,
	int deslocamento,
	char *rotulo)
{
	strcpy(s->identificador, ident);
	s->tipo = NONE;
	s->categoria = PROCEDIMENTO;
	s->nivel = nivel;
	s->deslocamento = deslocamento;
	strcpy(s->rotulo,rotulo);
	s->memoriaAlocada = 0;
	s->passagem = 0;
}
void inicializasSimboloParamFormal(ssimbolo *s, 
	const char *ident,
	int nivel)
{
	strcpy(s->identificador, ident);
	s->tipo = NONE;
	s->categoria = PARAM_FORMAL;
	s->nivel = nivel;
	s->deslocamento = -1;
	s->passagem = 0;
	s->memoriaAlocada = 0;
}

// so passa parametros que var simples tem
void inicializasSimboloVar(ssimbolo *s, 
	const char *ident,
	int nivel,
	int deslocamento)
{
	strcpy(s->identificador, ident);
	s->tipo = NONE;
	s->categoria = VAR_SIMPLES;
	s->nivel = nivel;
	s->deslocamento = deslocamento;
	s->memoriaAlocada = 0;
	s->passagem = 0;
}

int insere(ts *p, ssimbolo *e)
{
	if (p->topo == TAMANHO_TS)
	{
		return 0;
	}
	// memcpy( (void*)&p->elementos[p->topo], (void*)&e, sizeof(e) );
   	strcpy((p->elementos[p->topo].identificador), e->identificador);
   	p->elementos[p->topo].categoria = e->categoria;
   	p->elementos[p->topo].nivel = e->nivel;
   	p->elementos[p->topo].tipo = e->tipo;
   	p->elementos[p->topo].deslocamento = e->deslocamento;
   	p->elementos[p->topo].passagem = e->passagem;
   	strcpy((p->elementos[p->topo].rotulo), e->rotulo);
   	p->elementos[p->topo].numeroParametros = e->numeroParametros;
	p->topo++;
	return 1;
}

int deleta(ts *p,int n)
{

    #ifdef DEBUG
    // printf("\n\n"); 
    // printf("%d\n",n );
    // imprimeTS(p);
    // printf("\n\n");
    #endif 
	p->topo-=n;
	// todo: teste se tá tentando tirar mais do que tem
	if (p->topo < 0)
	{
		p->topo = 0;
	}
	return 1;
}

int busca(ts *p, char *ident, int checaMesmoNivel)
{
	if (checaMesmoNivel == -1)
	{	
		int indice = -1;
		for (int i = 0; i < p->topo; ++i)
		{
			if (!strcmp(p->elementos[i].identificador, ident))
			{
				indice = i;
			}
		}
		#ifdef DEBUG 
		printf("busca1: %s\nindice: %d\n", ident, indice );
		#endif 
		return indice;
	}
	else
	{
		int indice = -1;
		for (int i = 0; i < p->topo; ++i)
		{
			if (!strcmp(p->elementos[i].identificador, ident))
			{
				if (p->elementos[i].nivel == checaMesmoNivel)
				{
					indice = i;
				}
			}
		}
		#ifdef DEBUG 
		printf("busca2: %s\nindice: %d\n", ident, indice );
		#endif 
		return indice;

	}
}

int contaVarPorNivel(ts *p, int nivel, int alocar)
{
	// to-do:
	// só conta variáveis, não contar procedimentos/funcoes
	// para desalocar quando acabar procedimento
	int count = 0;
	int indice = p->topo - 1;
	while (indice >= 0 && 
		p->elementos[indice].nivel == nivel &&
		(
			p->elementos[indice].categoria == VAR_SIMPLES ))
	{
		if (alocar && p->elementos[indice].memoriaAlocada)
			break;
		p->elementos[indice].memoriaAlocada = !p->elementos[indice].memoriaAlocada;
		count++;
		indice--;
	}
	#ifdef DEBUG 
	printf("nivel: %d vars: %d\n",nivel, count );
	#endif
	return count;
}
int contaSubrotinaPorNivel(ts *p, int nivel)
{
	// to-do:
	// só conta variáveis, não contar procedimentos/funcoes
	// para desalocar quando acabar procedimento
	int count = 0;
	int indice = p->topo - 1;
	while (indice >= 0 && 
		p->elementos[indice].nivel == nivel &&
		(p->elementos[indice].categoria == PROCEDIMENTO ||
		p->elementos[indice].categoria == FUNCAO	) )
	{
		count++;
		indice--;
	}

	#ifdef DEBUG 
	printf("nivel: %d subtorinas: %d\n",nivel, count );
	#endif
	return count;
}

void setaTipo(ts *p, char *tipoStr)
{
	int tipo;
	if (!strcmp(tipoStr, "integer"))
	{
		tipo = INTEGER;
	}
	else if (!strcmp(tipoStr, "boolean"))
	{
		tipo = BOOL;
	}
	else 
	{
		// tipo desconhecido
		tipo = -1;
	}

	int indice = p->topo-1;
	while (indice >= 0 && p->elementos[indice].tipo == NONE && 
		(p->elementos[indice].categoria == VAR_SIMPLES ||
		 p->elementos[indice].categoria == PARAM_FORMAL)

	)
	{
		p->elementos[indice].tipo = tipo;
		indice--;
	}
}

void setaTipoEDeslocamentoFuncao(ts *p, char *tipoStr)
{
	int tipo;
	if (!strcmp(tipoStr, "integer"))
	{
		tipo = INTEGER;
	}
	else if (!strcmp(tipoStr, "boolean"))
	{
		tipo = BOOL;
	}
	else 
	{
		// tipo desconhecido
		tipo = -1;
	}
	int indice = p->topo-1;
	while (indice >= 0 && p->elementos[indice].categoria != FUNCAO)
	{
		
		indice--;
	}
	p->elementos[indice].tipo = tipo;
	p->elementos[indice].deslocamento = -4 - p->elementos[indice].numeroParametros;

}
void setaPassagem(ts *p, int passagem)
{
	int indice = p->topo-1;
	while (indice >= 0 && p->elementos[indice].passagem==0 && p->elementos[indice].categoria == PARAM_FORMAL)
	{

		p->elementos[indice].passagem = passagem;
		indice--;
	}
}
void setaDeslocamento(ts *p)
{
	int indice = p->topo-1;
	int deslocamento = -4;
	while (indice >= 0 && p->elementos[indice].deslocamento==-1 && p->elementos[indice].categoria == PARAM_FORMAL)
	{
		p->elementos[indice].deslocamento = deslocamento;
		deslocamento--;
		indice--;
	}
}

void setaParametros(ts *p, char* ident)
{
	#ifdef DEBUG 
	printf("SETANDO PARAMETROS\n" );
	#endif 

	int indiceSubRotina = busca(p, ident, -1);
	int indice = p->topo -1;
	int numeroParametros = p->elementos[indiceSubRotina].numeroParametros = 0;
	while (indice>=0 && p->elementos[indice].categoria == PARAM_FORMAL)
	{
		p->elementos[indiceSubRotina].parametros[numeroParametros].passagem = p->elementos[indice].passagem;
		p->elementos[indiceSubRotina].parametros[numeroParametros].tipo = p->elementos[indice].tipo;
		p->elementos[indiceSubRotina].numeroParametros++;
		numeroParametros++;
		indice--;
	}

	#ifdef DEBUG 
	// imprimeTS(p);
	#endif

}

void imprimeTS(ts *p)
{
	// todo: ifdef DEBUG
	// todo: mensagem mais explicativa
	// todo: especificar o que imprimir???
	printf("------------------------------\n");
	printf("IMPRIMINDO TS\n");
	printf("Topo da Pilha: %d\n", p->topo);
	for (int i = 0; i < p->topo; ++i)
	{
		printf("Indice: %d\n",i );
		printf("Identificador: %s\nAtributos\ntipo:%d\nnivel:%d\ndeslocamento:%d\n%d\n%s\nParametros:%d\n",
			p->elementos[i].identificador,
			p->elementos[i].tipo,
			p->elementos[i].nivel,
			p->elementos[i].deslocamento,
			p->elementos[i].categoria,
			p->elementos[i].rotulo,
			p->elementos[i].numeroParametros );
		if (p->elementos[i].numeroParametros)
		{
			printf("Parametros\n");
			for (int j = 0; j < p->elementos[i].numeroParametros; ++j)
			{
				printf("tipo:%d\n",p->elementos[i].parametros[j].tipo );
				printf("passagem:%d\n",p->elementos[i].parametros[j].passagem );
			}
		}
		printf("\n\n");
	}
	printf("TERMINOU IMPRESSÃO DA TS\n");
	printf("------------------------------\n");
}