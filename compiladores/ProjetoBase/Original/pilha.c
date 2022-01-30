#include "pilha.h"

int insereElemento(pilha *p, int elem)
{
	// printf("----inseriu %d\n",p->topo );
	if (p->topo == TAMANHO_PILHA)
	{
		return 0;
	}
	p->topo++;
	p->elementos[p->topo] = elem;
	return 1;
}

void removeElemento(pilha *p, int n)
{
	p->topo-=n;
	if (p->topo < -1)
	{
		p->topo = -1;
	}

}

void mudaElemento(pilha *p, int pos, int val)
{
	p->elementos[pos] = val;
}

void inicializaPilha(pilha *p)
{
	p->topo = -1;
}

int devolveElemento(pilha p, int pos)
{
	return p.elementos[pos];
}
