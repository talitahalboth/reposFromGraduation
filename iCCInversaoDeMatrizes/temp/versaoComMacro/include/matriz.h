#ifndef __MATRIZ_H__
#define __MATRIZ_H__

/**
 * @file matriz.h
 * @author Stephanie Briere Americo, Talita Halboth Cunha Fernandes
 * @date 23 Sep 2017
 * @brief Header com funções e estruturas de dados
 * referentes à manipulação de matrizes 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define pos(lin, col, tam) (lin*tam + col)
/**
 * @brief Estrutura de dados para representar uma matriz
 *
 *
 * @p dados é um vetor de tipo double. Alocar a matriz dessa forma garante que 
 * os dados estejam contínuos na memória, aumentando a eficiência do programa
 * por causa da localidade física de cada elemento.
 * 
 */
typedef struct MATRIZ {
    unsigned int tam; /**< Inteiro que representa o tamanho da matriz */
    double *dados; /**< Vetor de tipo double par armazenar os dados da matriz */
} MATRIZ;


/**
 * @brief Função que gera uma matriz quadrada aleatória
 *
 * @param n é o tamanho da matriz a ser gerada
 * \return Retorna um ponteiro para uma matriz de tamanho n*n
 *
 */
double *geraMatrizQuadradaRandomica(unsigned int n);

/**
 * @brief Função que imprime os elementos de uma matriz
 * @param matriz é a matriz a ser impressa
 * @param out é o arquivo onde deve ser impressa a saída
 *
 */
void imprimeMatriz (MATRIZ matriz, FILE *out);

/**
 * @brief Função que troca duas linhas de uma matriz
 * @param matriz é um ponteiro para a matriz a ser alterada
 * @param l1 é uma das linhas a ser trocada
 * @param l2 é uma das linhas a ser trocada
 *
 */
void trocaLinhas (MATRIZ *matriz, unsigned int l1, unsigned int l2);

/**
 * @brief Função que troca duas colunas de uma matriz
 * @param matriz é um ponteiro para a matriz a ser alterada
 * @param c1 é uma das colunas a ser trocada
 * @param c2 é uma das colunas a ser trocada
 *
 */
void trocaColunas (MATRIZ *matriz, unsigned int c1, unsigned int c2);

/**
 * @brief Função que realiza pivotamento parcial em uma matriz para a fatoração LU
 * @param matriz é um ponteiro para a matriz a ser alterada
 * @param col é a coluna onde deve ser realizado o pivotamento
 * \return @c -1 se não foi possível realizar o pivotamento
 * \return @c max Linha da matriz com o valor máxino da coluna 
 * 
 */

int pivotamentoParcial (MATRIZ *matriz, unsigned int col);


int alocaMatrizQuadrada(MATRIZ *matriz);
#endif