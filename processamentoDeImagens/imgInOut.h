#ifndef __IMGINOUT__
#define __IMGINOUT__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct imagem_t
{
  char  tipo[100] ;
	int linhas;
	int colunas;
	int brancoMaximo;
	unsigned char **img;
} img_t;

//confere se é entrada padrão ou arquivo
img_t entrada (int argc, char **argv);
//trata a leitura de arquivos
img_t LeEntradaFile(char* nomeArquivo);
//trata a leitura da stdin
img_t LeEntradaStdin();
// aloca memória para a imagem
void alocaMemoria ();
//confere se é saída padrão
void saida (img_t imagem, int argc,char **argv);
//trada a saida stdout
void saidaStdout (img_t imagem);
//trata a saida para arquivos
void saidaFile (img_t imagem,char* nomeArquivo);
//libera memoria alocada
void liberaMemoria ();

int stringToInteger (char* lim);

#endif