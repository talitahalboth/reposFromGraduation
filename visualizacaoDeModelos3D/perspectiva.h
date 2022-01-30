#ifndef __PERSPECTIVA__
#define __PERSPECTIVA__
#include "entrada.h"
#include "struct.h"

vertice *objEmpErspectiva;
vertice *objtmp;
int max;

void inita ();
void alocatmp ();
void perspectivaFraca (double xc, double yc, double zc);
void rotacionaX (double a);
void rotacionaZ (double a);
void rotacionaY (double a);
void convertePonto ();
void freetmp ();


#endif