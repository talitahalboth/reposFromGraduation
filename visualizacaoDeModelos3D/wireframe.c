#include "entrada.h"
#include "struct.h"
#include "arestas.h"
#include "perspectiva.h"
#include "imprimeJanela.h"

int main( int argc, char **argv)
{
	inita ();
	entry( argc,argv);
	allocaAresta ();
	alocatmp ();
	plotaArestas ();
		
	imprime ();
	liberaMemoria ();
	freetmp ();
	return 0;
}