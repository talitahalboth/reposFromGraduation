#ifndef __ENTRADA__
#define __ENTRADA__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#define mallocSize 1024

FILE *in;
void entry( int argc, char **argv);
void entradaStdin ();
void entradaFile (char* nomeArquivo);
void alocaMemoria ();
void allocaAresta ();
void reallocF ();
void reallocV ();
void leFacestdin ();
void leFacefile ();
void leVerticestdin ();
void leVerticeFile ();
void liberaMemoria ();
void entrada ( int argc, char **argv);

#endif