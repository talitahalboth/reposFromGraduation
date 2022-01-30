/*! \mainpage notitle
 *
 * \authors Stephanie Briere Americo @b GRR20165313
 * \authors Talita Halboth Cunha Fernandes @b GRR20165399
 * @date 23 Sep 2017
 * \section intro_sec Introdução
 *
 * O objetivo deste trabalho é,  
 * dada uma matriz quadrada A de dimensão n, 
 * encontrar sua matriz inversa (inv(A)), tal que A * inv(A) 
 * = I, onde I é a matriz identidade.
 * Para tal, o programa utiliza o Método da Eliminação de Gauss com Pivotamento Parcial, Fatoração LU e Refinamento.
 *
 * \subsection install_sec Compilação
 * Há uma makefile no projeto que compila o código, gerando o executável @c invmat
 *
 * \subsection run_sec Rodando o programa
 * @verbatim invmat [-e arquivo_entrada] [-o arquivo_saida] [-r N] [-i k]@endverbatim
 *
 *<ul>
 *	<li>@c -e @c arquivo_entrada: parâmetro opcional no qual @c arquivo_entrada é o caminho completo para o arquivo contendo a matriz a ser invertida. Em caso de ausência do parâmetro, a entrada será lida de @c stdin.
 *	<li>@c -o @c arquivo_saida: parâmetro opcional no qual @c arquivo_saida é o caminho completo para o arquivo que vai conter a matriz inversa. Em caso de ausência do parâmetro, a saída será impressa em @c stdout.
 *	<li>@c -r @c N: parâmetro opcional no qual @c N é a dimensão da matriz de entrada a ser gerada aleatoriamente
 *	<li>@c -i @c k: Número de iterações de refinamento a serem executadas (>0)
 *
 *
 */


/**
 * @file encontraMatrizInversa.c
 * @author Stephanie Briere Americo GRR29165313
 * @author Talita Halboth Cunha Fernandes GRR29165399
 * @date 23 Sep 2017
 * @brief Código que realiza a inversão de matrizes através da fatoração LU, resolução de sistemas lineares e refinamento
 *
 */

#include "matriz.h"
#include "inOut.h"
#include <math.h>
#include <time.h>
#include <sys/time.h>

/**inf positivo*/ 
#define P_INF (1.0/0.0)
/**inf negativo*/ 
#define N_INF (-1.0/0.0)
/**Not a Number*/ 
#define NaN (0.0/0.0)

/**
 * @brief Função que faz a fatoração LU de uma matriz quadrada.
 *
 * 
 * @param matriz É a matriz a ser fatorada.
 * @param trocas É um vetor de inteiros que salva quais linhas da matriz 
 * foram trocadas para realizar a fatoração
 * \return @c 0 se a fatoração não deu erro
 * \return @c -1 se houve erro na fatoração
 *
 */
int fatoracaoLU (MATRIZ *__restrict matriz, int * __restrict trocas) ;

/**
 * @brief Função que faz a retrosubstituição de um sistema linear
 *
 * Esta funlção é implementada especificamente para resolver
 * sistemas lineares utilizando matrizes LU, através da resolução
 * de sistemas do tipo LU*X=B, calculando o sistema com base
 * em cada coluna de X e B. 
 * O sistema linear foi dividido em L*Y=B e U*X=Y. substituicao_Lyb resolve
 * o sistema L*y=b. 
 * @param L É uma matriz do tipo #MATRIZ, resultante da fatoração LU
 * da matriz original.
 * @param y É uma matriz do tipo #MATRIZ, que será usada para guardar
 * os elementos da solução do sistema.
 * @param b é um vetor auxiliar do tipo double.
 */
void substituicao_Lyb (MATRIZ L, MATRIZ *__restrict y, double *__restrict b);

/**
 * @brief Função que faz a substituição avançada de um sistema linear
 *
 * Esta função é implementada especificamente para resolver
 * sistemas lineares utilizando matrizes LU, através da resolução
 * de sistemas do tipo LU*X=B, calculando o sistema com base
 * em cada coluna de X e B. 
 * O sistema linear foi dividido em L*Y=B e U*X=Y. substituicao_Uxy resolve
 * o sistema U*x=y. 
 * @param U É uma matriz do tipo #MATRIZ, resultante da fatoração LU
 * da matriz original.
 * @param y É uma matriz do tipo #MATRIZ, que será usada para guardar
 * os elementos da solução do sistema.
 * @param b é um vetor auxiliar do tipo double.
 * \return @c 0 se a fatoração não deu erro
 * \return @c -1 se houve erro na fatoração
 * 
 */
int substituicao_Uxy (MATRIZ U, MATRIZ *__restrict y, double *__restrict b);

/**
 * @brief Função que realiza o refinamento da solução obtida pela resolução do S.L.
 * e calcula o residuo a cada nova iteração do refinamento.
 *
 * @param A é uma matriz do tipo #MATRIZ, que guarda o valor inicial em cima do
 * qual calculamos a inversa.
 * @param inv_A é uma matriz do tipo #MATRIZ, que guarda o valor da matriz inversa
 * resultante da solução do S.L. A*inv_A=I, A=LU
 * @param LU é uma matriz do tipo #MATRIZ, que guarda o valor da matriz original
 * após a fatoração LU
 * @param aux é um vetor auxiliar do tipo double
 * @param iter é o número de iterações do refinamento que devem ser realizadas
 * @param tempoIter é o tempo médio para calcular o S.L. (incluindo refinamento)
 * @param tempoResiduo é o tempo médio para calcular o resíduo
 *
 * \return @c 0 se não houve nenhum erro
 * \return @c -1 se houve algum erro
 * 
 */
int refinamento(MATRIZ A, MATRIZ *__restrict inv_A, MATRIZ LU, double *__restrict aux, int iter, double *tempoIter, double *tempoResiduo);
/**
 * @brief Função que encontra a #MATRIZ R resultado de R = I - A*A_inv.
 * Além disso, calcula o resíduo da iteração atual do refinamento.
 *
 * @param A é uma matriz do tipo #MATRIZ, que guarda o valor inicial em cima do
 * qual calculamos a inversa.
 * @param inv_A é uma matriz do tipo #MATRIZ, que guarda o valor da matriz inversa
 * resultante da solução do S.L. A*inv_A=I, A=LU
 * @param R é uma matriz do tipo #MATRIZ, que guarda o resultado de R = I - A*A_inv
 * @param iter é o número da iteração atual do refinamento
 * @param tempoResiduo é o tempo médio para calcular o resíduo
 *
 * \return @c 0 se não houve nenhum erro
 * \return @c 1 se o calculo do residuo resultou em NaN ou inf (não consideramos erro)
 * 
 */
int calculaResiduo(MATRIZ A, MATRIZ inv_A, MATRIZ *__restrict R, int iter, double *tempoResiduo);
/**
 * @brief Função para contagem do tempo
 *
 * \return @c o valor atual do tempo
 * 
 */
double timestamp (void);

/**
 * @brief Função que multiplica duas matrizes
 *
 * 
 */
void multiplica(MATRIZ A, MATRIZ B);

int main (int argc, char** argv) {
/*##############################################*/
/*  [INICIO] DECLARACAO DAS VARIAVEIS UTILIZADAS*/
	srand( 20172 );
	int n, iteracoes; // tam da matriz e iteracoes do refinamento
	int *trocas; // vetor que guarda historico do pivotamento
	char *arqEntrada , *arqSaida;
	MATRIZ original, originalLU, inversa; // matrizes utilizadas
	double *aux = NULL;
	double tempoLU=0, tempoIter=0, tempoResiduo=0;
	out = stdout;
/*  [FIM] DECLARACAO DAS VARIAVEIS UTILIZADAS*/
/*##############################################*/

/*##############################################*/
/*  [INICIO] LEITURA/CRIACAO DA MATRIZ ORIGINAL */
	trataArgumentos(argc, argv, &arqEntrada, &arqSaida, &n, &iteracoes);	   
	if (arqSaida != NULL) 
		saidaPorArquivo(arqSaida);
	
	//leitura dos dados da matriz
	if (n == -1) {
		if (entradaPorArquivo(arqEntrada,&original) == -1) {
			fprintf(stderr, "[main] Erro ao abrir o arquivo de entrada.\n");
			return -1;
		}
		n = original.tam; // usaremos n como tam da matriz
	}
	else { //caso não se defina nenhum arquivo de entrada e nem o tamanho da matriz, cria uma matriz aleatoria
		original.tam = n;
		if(! (original.dados = geraMatrizQuadradaRandomica(n)) ) {
			fprintf(stderr, "[main] Erro ao alocar a matriz original.\n");
			return -1;
		}
	}


/*  [FIM] LEITURA/CRIACAO DA MATRIZ ORIGINAL */
/*##############################################*/

/*##############################################*/
/*  [INICIO] FATORACAO A=L*U DA MATRIZ ORIGINAL */
	// alocando a matriz que guardará a fatoração LU
	originalLU.tam = n; 
	if(alocaMatrizQuadrada(&originalLU) == -1) {
		fprintf(stderr, "[main] Erro ao alocar a matriz originalLU\n");
		return -1;
	}

	// copia matriz original para a matriz que sofrerá a fatoração LU
	unsigned int tam =  n +(4 - n%4);
	for (unsigned int i = 0; i < tam*tam; ++i)
		originalLU.dados[i] = original.dados[i];

	// vetor que guarda historico do pivotamento
	trocas = (int*) malloc(original.tam*sizeof(int));

	// fatora a matriz original em uma LU
	tempoLU = timestamp();
	if(fatoracaoLU(&originalLU, trocas) == -1)
		return -1;
	tempoLU = timestamp() - tempoLU;

	// aplica pivotamento na matriz original
	for (unsigned int i = 0; i < original.tam; ++i)
		if ((int)i != trocas[i]) trocaLinhas(&original, i, trocas[i]);
	

/*  [FIM] FATORACAO A=L*U DA MATRIZ ORIGINAL */
/*##############################################*/

/*##############################################*/
/*  [INICIO] RESOLUCAO DO SISTEMA LINEAR LU*X=B */
	if (!(aux = (double*) malloc(n*sizeof(double)))) {
		fprintf(stderr, "[main] Erro ao alocar o vetor auxiliar.\n");
		return -1;		
	}

	// alocando a matriz que guardará a inversa
	inversa.tam = n; 
	if(alocaMatrizQuadrada(&inversa) == -1) {
		fprintf(stderr, "[main] Erro ao alocar a matriz inversa\n");
		return -1;
	} 

	// inversa inicia como uma matriz identidade
	for (int i = 0; i < n; ++i) 
		inversa.dados[pos(i, i, n)] = 1;

	tempoIter = timestamp();
	// resolve o sistema L*y=b (o resultado é armazenado na inversa)
	substituicao_Lyb(originalLU, &inversa, aux); 
	// resolve o sistema U*x=y (o resultado é armazenado na inversa)
	if (substituicao_Uxy(originalLU, &inversa, aux) == -1)
		return -1;
	tempoIter = timestamp() - tempoIter;



/*  [FIM] RESOLUCAO DO SISTEMA LINEAR LU*X=B */
/*##############################################*/
	fprintf(out, "#\n");
	
/*##############################################*/
/*  [INICIO] REFINAMENTO DA SOLUCAO PARA LU*X=B */
	// neste ponto, a inversa deveria estar correta... partimos para o refinamento
	if(refinamento(original, &inversa, originalLU, aux, iteracoes, &tempoIter, &tempoResiduo) == -1)
		return -1;
/*  [FIM] REFINAMENTO DA SOLUCAO PARA LU*X=B */
/*##############################################*/

	// arruma a inversa (pivotamento)

	for (int i = inversa.tam-1; i >= 0; --i)
		if (i != trocas[i]) trocaLinhas (&inversa, i, trocas[i]);


/*##############################################*/
/*  [INICIO] IMPRIME VALORES DE SAIDA ESPERADOS */
	fprintf(out, "# Tempo LU: %.17lf\n", tempoLU); // tempo levado para calcular a matriz LU
	fprintf(out, "# Tempo iter: %.17lf\n",((tempoIter/(iteracoes+1)))/original.tam); // tempo medio levado para calcular o S.L.
	fprintf(out, "# Tempo residuo: %.17lf\n", tempoResiduo/(iteracoes+1)); // tempo medio levado para calcular o residuo
	fprintf(out, "%d\n", n);
	imprimeMatrizTransposta(inversa, out);
#ifdef DEBUG
	for (int i = inversa.tam-1; i >= 0; --i)
		if (i != trocas[i]) trocaLinhas (&original, i, trocas[i]);
	multiplica(original,inversa);
#endif
/*  [FIM] IMPRIME VALORES DE SAIDA ESPERADOS */
/*##############################################*/

	// libera memoria utilizada
	free(original.dados);
	free(originalLU.dados);
	free(inversa.dados);
	free(arqEntrada);
	free(arqSaida);
	free(aux);
	fclose(out);
	return 0;
}

int fatoracaoLU (MATRIZ *__restrict matriz, int * __restrict trocas) {
#ifdef DEBUG
	fprintf(out, "[fatoracaoLU] Iniciando a fatoracao LU.\n");
#endif
	double m;
	for (unsigned int col = 0; col < matriz->tam-1; ++col) { // zerando colunas
		if((trocas[col] = pivotamentoParcial(matriz, col)) == -1) { // se o pivotamento falha, a matriz é inválida
			fprintf(stderr, "[fatoracaoLU] Matriz singular, impossivel fatorar.\n");
			return -1;
		}
		trocas[matriz->tam-1] = matriz->tam-1;
		for (unsigned int lin = col+1; lin < matriz->tam; ++lin) { // calcula o modificador m para cada linha
			m = (matriz->dados[pos(lin, col, matriz->tam)]*1.0)/matriz->dados[pos(col, col, matriz->tam)];
			// U
			for (unsigned int j = col; j < matriz->tam; ++j) // percorrendo linha para aplicar m
				matriz->dados[pos(lin, j, matriz->tam)] -= m*matriz->dados[pos(col, j, matriz->tam)];
			// L
			matriz->dados[pos(lin, col, matriz->tam)] = m; // armazena o modificador m onde seria 0
		}
	} 
#ifdef DEBUG
	fprintf(out, "[fatoracaoLU] Fatoracao LU completa.\n");
#endif 
	return 0;
}

void substituicao_Lyb (MATRIZ L, MATRIZ *__restrict y, double *__restrict b) {
#ifdef DEBUG
	fprintf(out, "[substituicao_Lyb] Iniciando a resolucao do sistema Ly=b.\n");
#endif
	// variavel auxiliar pro tamanho das matrizes
	unsigned int tam = L.tam;

	for (unsigned int sl = 0; sl < tam; ++sl) { // cada coluna da matriz é um vetor b (A*x=b) para resolver o sistema
		for (unsigned int k = 0; k < tam; ++k)
				b[k] = y->dados[pos(sl,k,tam)];
		
		y->dados[pos(sl,0,tam)] = (b[0]*1.0);
		for (unsigned int lin = 1; lin < tam; ++lin) { // da segunda linha em diante (a primeira sofre alteração)
			y->dados[pos(sl,lin,tam)] = b[lin];
			for (unsigned int col = 0; col < lin; ++col)
				y->dados[pos(sl, lin, tam)] -= L.dados[pos(lin, col, tam)]*y->dados[pos(sl, col, tam)];
		}
	}
#ifdef DEBUG
	fprintf(out, "[substituicao_Lyb] Resolucao do sistema Ly=b completa.\n");
#endif 
}

int substituicao_Uxy (MATRIZ U, MATRIZ *__restrict y, double *__restrict b) {
#ifdef DEBUG
	fprintf(out, "[substituicao_Uxy] Iniciando a resolucao do sistema Ux=y.\n");
#endif
	// variavel auxiliar pro tamanho das matrizes
	unsigned int tam = U.tam;
	// i é a coluna da matriz na qual estamos realizando a substituição (cada coluna é o vetor b de um sistema linear A*x=b)
	for (unsigned int i = 0; i < tam; ++i) {
		// y será alterado para armazenar a matriz resultante (funcionando como x em Ax = b)
		// a coluna i de y é copiada para o vetor b
		for (unsigned int k = 0; k < tam; ++k)
			b[k] = y->dados[pos(i,k,tam)];
		// faz a retrosubstituição 
		if(U.dados[pos(tam-1, tam-1, tam)] == 0) {
			fprintf(stderr, "[substituicao_Uxy] Operacao gera NaN/inf.\n");
			return -1;
		}

		y->dados[pos(i,tam-1,tam)] = (b[tam-1]*1.0)/U.dados[pos(tam-1, tam-1, tam)];
		for (int k = tam-1; k >= 0; --k) {
			y->dados[pos(i,k,tam)] = b[k];
			for (int j = tam-1; j > k; --j)
				y->dados[pos(i,k,tam)] -= U.dados[pos(k,j,tam)]*y->dados[pos(i,j,tam)];
			if(U.dados[pos(k,k,tam)] == 0) {
				fprintf(stderr, "[substituicao_Uxy] Operacao gera NaN/inf.\n");
				return -1;
			}
			y->dados[pos(i,k,tam)]=(y->dados[pos(i,k,tam)]*1.0)/U.dados[pos(k,k,tam)];
		}        
	}
#ifdef DEBUG
	fprintf(out, "[substituicao_Uxy] Resolucao do sistema Ux=y completa.\n");
#endif 
	return 0;
}

int refinamento(MATRIZ A, MATRIZ *inv_A, MATRIZ LU, double *aux, int iter, double *tempoIter, double *tempoResiduo) {
	MATRIZ R;
	unsigned int tam = A.tam;
	unsigned int tam2 = tam +(4 -tam%4);
	double tempo_i = 0;
	R.tam = tam; 
	// alocando a matriz que guardará o residuo
	if(alocaMatrizQuadrada(&R) == -1) {
		fprintf(stderr, "[refinamento] Erro ao aloca a matriz R\n");
		return -1;
	}

	for (int i = 0; i < iter; ++i) {
		if(calculaResiduo(A, *inv_A, &R, i+1, tempoResiduo) == 1)
			return 0;

		tempo_i = timestamp() - tempo_i;
		substituicao_Lyb(LU, &R, aux);
		if (substituicao_Uxy(LU, &R, aux) == -1) 
			return -1;

		for(unsigned int j = 0; j < tam2*tam2; ++j) {
			inv_A->dados[j] += R.dados[j];
		}
		tempo_i = timestamp() - tempo_i;
		*tempoIter += tempo_i;
	}

	free(R.dados);
	return 0;
}

int calculaResiduo(MATRIZ A, MATRIZ inv_A, MATRIZ *R, int iter, double *tempoResiduo) {

	//void saxpy(int n, float alpha, float *X, float *Y) {
	//	__m128 x_vec, y_vec, a_vec, res_vec; /* Vector variables */
	//	int i;
	//	a_vec = _mm_set1_ps(alpha); /* Vector of 4 alpha values */
	//	for (i=0; i<n; i+=4) {
	//		x_vec = _mm_load_ps(&X[i]); /* Load 4 values from X */
	//		y_vec = _mm_load_ps(&Y[i]); /* Load 4 values from Y */
	//		res_vec = _mm_add_ps(_mm_mul_ps(a_vec, x_vec), y_vec); /* Compute */
	//		_mm_store_ps(&Y[i], res_vec); /* Store the result */
	//	}
	//}
	//__m128 A_vec, inv_A_vec, R_vec, soma_vec, c_vec, C_vec, y_vec, t_vec;
	unsigned int tam = A.tam;
	double C, r = 0;
	double tempo_r = timestamp();
	for (unsigned int lin = 0; lin < tam; lin++) {
		for (unsigned int col = 0; col < tam; col++) {

			C = 0;
			for (unsigned int k = 0; k < tam; k++) {
				C+= A.dados[pos(lin,k,tam)]*inv_A.dados[pos(col,k,tam)];
			}
			C = (lin == col ? 1.0 - C : -C);
			R->dados[pos(col, lin, tam)] = C; // R = I - A*inv_A
			r += C*C; // ||r|| = sum(R[i,j]^2)
		}
	}
	r = sqrt(r); // ||r|| = sqrt(sum(R[i,j]^2))
	tempo_r = timestamp() - tempo_r;
	*tempoResiduo += tempo_r;
	if (r == N_INF || r == P_INF || r == NaN) {
		#ifdef DEBUG
			fprintf(out, "Residuo se tornou inf/NaN, iteracoes interrompidas.\n");
		#endif
		return 1;
	}
	fprintf(out, "# iter %d: %.17g\n", iter, r);
	return 0;
}

double timestamp(void){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

void multiplica(MATRIZ A, MATRIZ B)
{
    unsigned int i, j, k;
    for (i = 0; i < A.tam; i++)
    {
        for (j = 0; j < A.tam; j++)
        {
            double C = 0;
            for (k = 0; k < A.tam; k++)
                C += A.dados[pos(i,k,A.tam)]*B.dados[pos(j,k,B.tam)];
           
            printf("%s%.20lf ",C>=0?" ":"",C );
        }
        printf("\n");
    }
}