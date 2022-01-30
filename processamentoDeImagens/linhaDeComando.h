#ifndef __IMGINOUT__
#define __IMGINOUT__
#include <stdio.h>
#include <stdlib.h>

//confere se é entrada padrão ou arquivo
img_t entrada (int argc, char **argv);

//confere se é saída padrão
void saida (img_t imagem, int argc,char **argv);


#endif