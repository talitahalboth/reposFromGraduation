/* -------------------------------------------------------------------
 *            Arquivo: compilaodr.h
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [15/03/2012, 08h:22m]
 *
 * -------------------------------------------------------------------
 *
 * Tipos, protótipos e vaiáveis globais do compilador
 *
 * ------------------------------------------------------------------- */

#define TAM_TOKEN 16
#define DEFAULT_STRING_LENGTH 100
#define DEFAULT_STACK_SIZE 100

typedef enum simbolos { 
  simb_program, simb_var, simb_begin, simb_end, 
  simb_identificador, simb_numero,
  simb_ponto, simb_virgula, simb_ponto_e_virgula, simb_dois_pontos,
  simb_atribuicao, simb_abre_parenteses, simb_fecha_parenteses,
  simb_label, simb_type, simb_array,
  simb_procedure, simb_function, 
  simb_goto, simb_if, simb_then, simb_else, simb_while, simb_do, simb_not,
  simb_igual, simb_diferente, simb_menor, simb_menor_igual, simb_maior, simb_maior_igual,
  simb_soma, simb_subtrai, simb_or, 
  simb_multiplica, simb_divide, simb_and, 
  simb_read, simb_write,
  simb_true_t, simb_false_t


} simbolos;



/* -------------------------------------------------------------------
 * variáveis globais
 * ------------------------------------------------------------------- */

extern simbolos simbolo, relacao;
extern char token[TAM_TOKEN];
extern int nivel_lexico;
extern int desloc;
extern int nl;


simbolos simbolo, relacao;
char token[TAM_TOKEN];

void checaTipos();
void insereNaTabelaDeSimbolos();
char* geraRotulo(int colocaNaPilha);
char* tabelaTipos(int n);
void checaVariavel(int index, char* iden);
void checaCategoria(int index);
// DELETAR
void geraCodigo (char* rot, char* comando);
int imprimeErro ( char* erro );


