#include "matriz.h"

/**
 * @file matriz.c
 * @author Stephanie Briere Americo, Talita Halboth Cunha Fernandes
 * @date 23 Sep 2017
 * @brief Funções
 * referentes à manipulação de matrizes 
 *
 */

double *geraMatrizQuadradaRandomica( unsigned int n ) { // função dada pelo professor
#ifdef DEBUG
	printf("[geraMatrizQuadradaRandomica] Iniciando.\n");
#endif
	double *mat = NULL;

	/* return NULL if memory allocation fails */
	if ( ! (mat = (double *) malloc(n*n*sizeof(double))) ){
        #ifdef DEBUG
            printf("[geraMatrizQuadradaRandomica] Falha ao alocar a matriz original.\n");
        #endif
		return (NULL);
    }

	/* generate a randomly initialized matrix in row-major order */
	double *ptr = mat;
	double *end = mat + n*n;

	double invRandMax = 1.0/(double)RAND_MAX;

	while( ptr != end ) {
		*ptr++ = (double)rand() * invRandMax;
	}
#ifdef DEBUG
	printf("[geraMatrizQuadradaRandomica] Matriz randomica gerada.\n");
#endif
	return (mat);
}

void imprimeMatriz (MATRIZ matriz, FILE *out) {
#ifdef DEBUG
	fprintf(out, "[imprimeMatriz] Imprimindo matriz %ux%u.\n", matriz.tam, matriz.tam);
#endif
	unsigned int tam = matriz.tam;
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			if (matriz.dados[pos(i, j, tam)] == 0) matriz.dados[pos(i, j, tam)] = 0;
			// usar %.17g porque lf arredonda...
			fprintf(out, "%.17g ", matriz.dados[pos(i, j, tam)]);
		}
		fprintf(out, "\n");
	}
}

int pivotamentoParcial (MATRIZ *matriz, unsigned int col) {
    unsigned int max = col;
    for (unsigned int l_atual = col+1; l_atual < matriz->tam; ++l_atual) // encontra o maior elemento da coluna
        if (matriz->dados[pos(max, col, matriz->tam)] < matriz->dados[pos(l_atual, col, matriz->tam)])
            max = l_atual;

    if (matriz->dados[pos(max, col, matriz->tam)] == 0) // se a coluna for nula, impossivel realizar pivotamento/fatorar
        return -1;
    
    else if (max != col) trocaLinhas (matriz, max, col);

    return max;
}

void trocaLinhas (MATRIZ *matriz, unsigned int l1, unsigned int l2) { // troca 2 linhas de uma matriz
    double aux;
    for (int i = 0; i < matriz->tam; ++i) {
        aux = matriz->dados[pos(l1, i, matriz->tam)];
        matriz->dados[pos(l1, i, matriz->tam)] = matriz->dados[pos(l2, i, matriz->tam)];
        matriz->dados[pos(l2, i, matriz->tam)] = aux;
    }
}

void trocaColunas (MATRIZ *matriz, unsigned int c1, unsigned int c2) { // troca 2 colunas de uma matriz
    double aux;
    for (int i = 0; i < matriz->tam; ++i) {
        aux = matriz->dados[pos(i, c1, matriz->tam)];
        matriz->dados[pos(i, c1, matriz->tam)] = matriz->dados[pos(i, c2, matriz->tam)];
        matriz->dados[pos(i, c2, matriz->tam)] = aux;
    }
}


unsigned int pos(unsigned int lin, unsigned int col, unsigned int tam) {
  return (lin*tam + col);
}

int alocaMatrizQuadrada(MATRIZ *matriz) {
    unsigned tam = matriz->tam;
    if (!(matriz->dados = (double *) calloc(tam*tam, sizeof(double))))
        return -1;
    return 0;
}