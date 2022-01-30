
#include "matriz.h"
#include "inOut.h"

/**
 * @file inOut.c
 * @author Stephanie Briere Americo, Talita Halboth Cunha Fernandes
 * @date 23 Sep 2017
 * @brief Funções referentes à entrada 
 * e saída de arquivos
 */



FILE *out;
//retorna o numero k de iterações



void trataArgumentos (int argc, char** argv, char** entrada, char** saida, int *N, int*k) {
    *entrada = NULL;
    *saida = NULL; 
    *N = -1;
    *k = 0;
    for (int i = 0; i < argc; ++i) {
        if (argv[i][0]=='-') {
            if (argv[i][1]=='e') {
                *entrada = (char*) malloc(strlen(argv[2]) + 1);
                strcpy(*entrada, argv[i+1]);
            }
            else if (argv[i][1]=='o') {
                *saida =  (char*) malloc(strlen(argv[i+1]) + 1);
                strcpy(*saida, argv[i+1]);
            }
            else if (argv[i][1]=='r')
                *N = atoi (argv[i+1]);
            else if (argv[i][1]=='i')
                *k = atoi (argv[i+1]);
        }
    }
}

int entradaPorArquivo (char *entrada, MATRIZ *matriz) {
    FILE *in = NULL;
    int x;
    if (entrada != NULL)
        in = fopen(entrada, "r");
    else
        in = stdin;
    if (!in)
        return -1;

    x = fscanf(in,"%d", &matriz->tam);

    if(alocaMatrizQuadrada(matriz) == -1)
        return -1;

    for (unsigned int i = 0; i < matriz->tam*matriz->tam; ++i)
        x = fscanf(in,"%lf", &matriz->dados[i]);
    if (x == 0) return -1;
    fclose (in);

    return 0;
}

int saidaPorArquivo(char *saida) {
    if (saida == NULL) {
        out = stdout;
        return 0;
    }
    out = fopen(saida,"w");
    if (!out) {
    #ifdef DEBUG
        printf("[SAIDAPORARQUIVO] Falha ao abrir o arquivo de saida.\n");
    #endif
        fprintf(stderr, " Falha ao abrir o arquivo de saida.\n");
        return -1;
    }
    return 0;
}
