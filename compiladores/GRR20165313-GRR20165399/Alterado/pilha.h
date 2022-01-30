#ifndef PILHA_H_   
#define PILHA_H_

#include <stdio.h>
#define TAMANHO_PILHA 1000

typedef struct pilha_t
{
	int topo;
	int elementos[TAMANHO_PILHA];
} pilha;
int insereElemento(pilha *p, int elem);
void removeElemento(pilha *p, int n);
void inicializaPilha(pilha *p);
#endif