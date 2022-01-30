#ifndef TABELASIMBOLOS_H_   
#define TABELASIMBOLOS_H_

#include <stdio.h>
#include <string.h>

#define TAMANHO_TS 1000
#define TAMANHO_PARAMETROS 1000
#define TAMANHO_IDENTIFICADOR 1000
#define TAMANHO_ROTULO 10

#define NONE 0
// categories
#define VAR_SIMPLES 1
#define PROCEDIMENTO 2
#define FUNCAO 3
#define PARAM_FORMAL 4

// types 
#define INTEGER 1
#define BOOL 2

// how variables are passed
#define VALOR 1
#define REFERENCIA 2


typedef struct parametros_t
{
	// char identificador[TAMANHO_IDENTIFICADOR];
	// int nivel;
	// int deslocamento;
	int tipo;
	// referencia ou valor
	int passagem;
} parametros;

// struct for symbols
// in the "category" variable we define the category
// and use the necessary fields based on that
typedef struct ssimbolo_t
{
	// todo: tipos das variáveis
	char identificador[TAMANHO_IDENTIFICADOR];
	int categoria;
	int nivel;
	int tipo;
	int deslocamento;
	int passagem;
	char rotulo[TAMANHO_ROTULO];
	int numeroParametros;
	// precisa disso????
	parametros parametros[TAMANHO_PARAMETROS];
	int memoriaAlocada;
} ssimbolo;

// stack struct
// it has only a top variable and an array of elements
typedef struct tabelaDesSimbolos_t
{
	int topo;
	ssimbolo elementos[TAMANHO_TS];
	
} ts;

void inicializasSimbolo (ssimbolo *s, 
	const char *ident,
	int tipo,
	int categoria,
	int nivel,
	int deslocamento,
	int passagem,
	char* rotulo,
	int numeroParametros);
void inicializasSimboloFunc(ssimbolo *s, 
	const char *ident,
	int nivel,
	char *rotulo);
void inicializasSimboloProc(ssimbolo *s, 
	const char *ident,
	int nivel,
	int deslocamento,
	char *rotulo);
void inicializasSimboloVar(ssimbolo *s, 
	const char *ident,
	int nivel,
	int deslocamento);
void inicializasSimboloParamFormal(ssimbolo *s, 
	const char *ident,
	int nivel);
void inicializaTS(ts *p);
int insere(ts *p, ssimbolo *e);
int deleta(ts *p,int n);
int busca(ts *p, char *ident, int checaMesmoNivel);

void setaTipo(ts *p, char *tipoStr);
void setaPassagem(ts *p, int passagem);
void setaDeslocamento(ts *p);
void setaParametros(ts *p, char* ident);
void setaTipoEDeslocamentoFuncao(ts *p, char *tipoStr);

int contaVarPorNivel(ts *p, int nivel, int alocar);
int contaSubrotinaPorNivel(ts *p, int nivel);

void imprimeTS(ts *p);
#endif
