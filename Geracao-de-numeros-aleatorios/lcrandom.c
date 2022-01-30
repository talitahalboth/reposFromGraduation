//Talita Halboth Cunha Fernandes GRR20165399
#include "lcrandom.h"
long a=40692, c=127, m=10000000;

long x=0;

long lcrandom ()
{
	x=(a*x+c)%m;
	return (x);
}
// o usuário passa o valor a ser usado como semente, entra na função como cópia
void lcrandom_seed (long s)
{
	x=s;
}
// retorna o valor máximo "aleatório" que pode ser retornado
long lcrandom_max ()
{
	return (m-1);
}
//muda os parâmetros da função lcrandom
void lcrandom_parms (long A, long C, long M)
{
	a=A;
	c=C;
	m=M;
}

