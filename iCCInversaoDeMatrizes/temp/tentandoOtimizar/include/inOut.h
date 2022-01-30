#ifndef __INOUT_H__
#define __INOUT_H__

/**
 * @file inOut.h
 * @author Stephanie Briere Americo, Talita Halboth Cunha Fernandes
 * @date 23 Sep 2017
 * @brief Header com funções referentes à entrada 
 * e saída de arquivos
 *
 */



/** @brief Variável global que aponta para o arquivo de saída dos dados */
extern FILE *out; 

/**
 * @brief Função que trata os argumentos
 *
 * @param argc Tamanho do vetor de strings @p argv
 * @param argv Vetor de string com os argumentos passados na execução do programa
 * @param entrada Ponteiro para vetor de chars, que é alterado com o nome do arquivo de entrada (se houver)
 * @param saida Ponteiro para vetor de chars, que é alterado com o nome do arquivo de saida (se houver)
 * @param N ponteiro para um inteiro N, que é alterado com a dimensão da matriz de entrada a ser gerada aleatoriamente (se houver)
 * @param k ponteiro para um inteiro k, que é alterado com o número de iterações a serem realizadas durante o refinamento
 *
 */
void trataArgumentos (int argc, char** argv, char** entrada, char** saida, int *N, int*k);
/**
 * @brief Função que trata a entrada de dados por arquivo
 *
 * @param entrada Vetor de chars com o nome do arquivo a ser aberto (@c NULL se a entrada for stdin)
 * @param matriz Matriz onde serão lidos os dados
 * \return @c 0 se a abertura do arquivo não deu erro
 * \return @c -1 se houve erro ao abrir o arquivo ou ao alocar a matriz
 * 
 */
int entradaPorArquivo (char *entrada, MATRIZ *matriz);

/**
 * @brief Função que trata a saída de dados
 *
 * @param saida Vetor de chars com o nome do arquivo onde serão escritos os dados (@c NULL se a saída for stdout)
 * \return @c 0 se a abertura do arquivo não deu erro
 * \return @c -1 se houve erro ao abrir o arquivo
 * 
 */
int saidaPorArquivo (char *saida);

#endif