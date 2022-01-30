
// Testar se funciona corretamente o empilhamento de parâmetros
// passados por valor ou por referência.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "tabelaDeSimbolos.h"
#include "pilha.h"

int num_vars;
// counts vars to allocate memory 
int contadorVariaveis;
// symbols table
ts p;
// used to know in which lexical level we are
int nivelLexico;
// used to know the dislocation in each of the lexical levels
int prevDeslocamento[DEFAULT_STACK_SIZE];
int deslocamento[DEFAULT_STACK_SIZE];
// string used to store the left operand when making attributions
char l_oper[DEFAULT_STRING_LENGTH];
// used to deal with minus signal before expression
int countTermo[DEFAULT_STACK_SIZE];
int nivelExpressao;
// used to know the type of the operands to know if an expression is valid
pilha typesStack;
// number of parameters
pilha numeroParametros;
// int contadorParametros;
pilha SeccontadorParametros;
// used as a control variable
int saveLeftOperand;
// stack of tags
char pilhaRotuloInicio[DEFAULT_STACK_SIZE][DEFAULT_STRING_LENGTH];
int pilhaRotuloInicioTopo;
// 
char pilhaIdentificadorEsquerda[DEFAULT_STACK_SIZE][DEFAULT_STRING_LENGTH];
int pilhaIdentificadorEsquerdaTopo;
// stack of function identifiers
char pilhaIdentificadorFuncao[DEFAULT_STACK_SIZE][DEFAULT_STRING_LENGTH];
int pilhaIdentificadorFuncaoTopo;

//serves as a type of map from an integer to a string
// this string corresponds to the name of the type that has that value
char valorTipoPraString[1000][DEFAULT_STRING_LENGTH];

// used to know what is the subtype of a variable with type i
int controleSubtipo[DEFAULT_STACK_SIZE];



int tagCounter;
int contador_subrotinas;
int calledSubprogram;
int declarouFuncao;
int setouVariavelFuncao;
pilha elementosExpressao;

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
 
%token LABEL TYPE ARRAY 
%token PROCEDURE FUNCTION
%token GOTO IF THEN ELSE WHILE DO NOT
%token IGUAL DIFERENTE MENOR MENOR_IGUAL MAIOR MAIOR_IGUAL SOMA SUBTRAI OR MULTIPLICA DIVIDE AND
%token T_BEGIN T_END VAR IDENT ATRIBUICAO NUMERO
%token READ WRITE
%token TRUE_T FALSE_T


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%

programa    :
    { 
      geraCodigo (NULL, "INPP"); 
    }
    PROGRAM IDENT 
    ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
    bloco 
    PONTO 
    {
      geraCodigo (NULL, "PARA"); 
    }
;

bloco       : 
    {
            // stores the previous dislocation in case we need it to use again
            prevDeslocamento[nivelLexico] = deslocamento[nivelLexico];
            // sets dislocation to 0 since its starting to declare things here
            deslocamento[nivelLexico]=0;

 
    }
    // rule to declare types

    parte_declara_tipos_helper

    parte_declara_vars_helper
    {
        // generate a tag to enter the subprogram that we're in
        char rotuloIni[DEFAULT_STRING_LENGTH];
        strcpy(rotuloIni, geraRotulo(1));          
        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "DSVS %s", rotuloIni);
        geraCodigo(NULL, str);
    }
    parte_declaracoes
    { 
        // enter the subprogram
        char rotuloIni[DEFAULT_STRING_LENGTH];
        strcpy(rotuloIni,pilhaRotuloInicio[pilhaRotuloInicioTopo]);
        pilhaRotuloInicioTopo--;
        geraCodigo(rotuloIni, "NADA");
    }
    comando_composto 
    {
        // remove subprograms from symbols table
        int deleteSubRot = contaSubrotinaPorNivel(&p, nivelLexico+1);
        deleta(&p, deleteSubRot);
        // dmem variables and remove variables from smnbols table
        int dmemVar = contaVarPorNivel(&p, nivelLexico, 0);
        if (dmemVar )
        {
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "%s %d","DMEM",dmemVar ); 
            geraCodigo(NULL, str);
            deleta(&p, dmemVar);

        }
        deslocamento[nivelLexico]=prevDeslocamento[nivelLexico];

      
    }

;

parte_declaracoes:
    // parte_declaracoes parte_declara_vars_helper
    parte_declaracoes parte_declara_procedimento
    | parte_declaracoes parte_declara_funcao
    | 

;

 /*
**------------------------------------------------------------------
  _______   _____ ___ 
 |_   _\ \ / / _ \ __|
   | |  \ V /|  _/ _| 
   |_|   |_| |_| |___|
                                                            
**------------------------------------------------------------------
*/                      

parte_declara_tipos_helper:
    | parte_declara_tipos
;

parte_declara_tipos:
    TYPE definicao_tipo_helper PONTO_E_VIRGULA
;

definicao_tipo_helper:
    definicao_tipo
    | definicao_tipo_helper PONTO_E_VIRGULA definicao_tipo   
;
  
definicao_tipo:
    IDENT
    {
        // copies teh token to the l_oper variable
        strcpy(l_oper, token);
    }
    IGUAL
    IDENT
    {
        // check if type hasn' alreaby been declared before
        for (int i = 0; i < taMvetorDeTipos; ++i)
        {
            if (!strcmp(vetorDeTipos[i].nome, l_oper))
            {
                char str[DEFAULT_STRING_LENGTH];
                sprintf(str, "Tipo ja declarado: %s", l_oper);
                imprimeErro(str);
            }
        }
        int existe=0;
        // searches for subtype 
        for (int i = 0; i < taMvetorDeTipos; ++i)
        {
            if (!strcmp(vetorDeTipos[i].nome, token))
            {
                existe = 1;

                vetorDeTipos[taMvetorDeTipos].valor = taMvetorDeTipos;
                vetorDeTipos[taMvetorDeTipos].ValorsubTipo = vetorDeTipos[i].valor;
                strcpy(vetorDeTipos[taMvetorDeTipos].nome, l_oper);
                strcpy(valorTipoPraString[taMvetorDeTipos], l_oper);
                controleSubtipo[taMvetorDeTipos] = vetorDeTipos[taMvetorDeTipos].ValorsubTipo;
                
                taMvetorDeTipos++;
            }
        }
        // if subtype hasn't been found, error
        if (!existe)
        {

            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Tipo de onde deriva nao declarado: %s", token);
            imprimeErro(str);
        }



    }
;

/*
**------------------------------------------------------------------
  ___ ___  ___   ___ ___ ___  _   _ ___ ___ 
 | _ \ _ \/ _ \ / __| __|   \| | | | _ \ __|
 |  _/   / (_) | (__| _|| |) | |_| |   / _| 
 |_| |_|_\\___/ \___|___|___/ \___/|_|_\___|
                                                            
**------------------------------------------------------------------
*/


parte_declara_procedimento:
    PROCEDURE 
    {

        nivelLexico++; 
        // variable to count subprograms
        // we only generate tag for the main program upon finding the first subprogram
        contador_subrotinas++; 
        if (contador_subrotinas == 1)
        {
            // char rotuloIni[DEFAULT_STRING_LENGTH];
            // strcpy(rotuloIni, geraRotulo(1));          
            // char str[DEFAULT_STRING_LENGTH];
            // sprintf(str, "DSVS %s", rotuloIni);
            // geraCodigo(NULL, str); 

        }
    } 
    declara_procedimento 
    {
        nivelLexico--;
    }
    ponto_virgula
;

ponto_virgula:
    | PONTO_E_VIRGULA
;

declara_procedimento:
    IDENT 
    {
        // put the name of the procedure in l_oper variable
        strcpy(l_oper, token);
        // generates tag to enter this procedure
        char rotuloProc[DEFAULT_STRING_LENGTH];
        strcpy(rotuloProc, geraRotulo(0));    
        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "ENPR %d", nivelLexico);
        geraCodigo(rotuloProc, str);
        // insert procedure in symbolts table
        insereNaTabelaDeSimbolos(PROCEDIMENTO, rotuloProc);
        #ifdef DEBUG 
        #endif 
        // insert 0 in number of parameters stack (since we don't konw how many parameters are there yet)
        insereElemento(&numeroParametros, 0);
    }
    parametros_formais 
    {
        // fill parameters array of procedure
        setaParametros(&p, l_oper);
    }

    PONTO_E_VIRGULA bloco
    {  
        char str[DEFAULT_STRING_LENGTH];
        int parametros = 0;
        if (numeroParametros.topo > -1)
        {
            parametros =  numeroParametros.elementos[numeroParametros.topo ];
            removeElemento(&numeroParametros, 1);
        }
        sprintf(str, "RTPR %d, %d", nivelLexico,parametros);
        geraCodigo(NULL, str); 
        // remove parameters from symbols table
        deleta(&p, parametros);

    }

;

/*
**------------------------------------------------------------------
  ___ _   _ _  _  ___ _____ ___ ___  _  _ 
 | __| | | | \| |/ __|_   _|_ _/ _ \| \| |
 | _|| |_| | .` | (__  | |  | | (_) | .` |
 |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|
                                                                                                      
**------------------------------------------------------------------
*/

parte_declara_funcao:
    FUNCTION 
    {

        nivelLexico++; 
        // variable to count subprograms
        // we only generate tag for the main program upon finding the first subprogram
        contador_subrotinas++; 
        if (contador_subrotinas == 1)
        {
            // char rotuloIni[DEFAULT_STRING_LENGTH];
            // strcpy(rotuloIni, geraRotulo(1));        
            // char str[DEFAULT_STRING_LENGTH];
            // sprintf(str, "DSVS %s", rotuloIni);
            // geraCodigo(NULL, str); 

        }
    } 
    declara_funcao
    {
        nivelLexico--;
    }
;
declara_funcao:
    IDENT 
    {

        setouVariavelFuncao = 0;
        pilhaIdentificadorFuncaoTopo++;
        strcpy(pilhaIdentificadorFuncao[pilhaIdentificadorFuncaoTopo], token);
        declarouFuncao = 1;
        // put the name of the function in l_oper variable
        strcpy(l_oper, token);
        // generates tag to enter this function
        char rotuloProc[DEFAULT_STRING_LENGTH];
        strcpy(rotuloProc, geraRotulo(0));    
        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "ENPR %d", nivelLexico);
        geraCodigo(rotuloProc, str);
        // insert function in symbolts table
        insereNaTabelaDeSimbolos(FUNCAO, rotuloProc);
        #ifdef DEBUG 
        #endif 
        // insert 0 in number of parameters stack (since we don't konw how many parameters are there yet)
        insereElemento(&numeroParametros, 0);
    }
    parametros_formais 
    {
        // fill parameters array of function
        setaParametros(&p, l_oper);
    }
    DOIS_PONTOS IDENT 
    {
        if (setaTipoEDeslocamentoFuncao(&p, token) == -1)
        {
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Tipo nao definido: %s",token); 
            imprimeErro(str);
        }
        
    }
    PONTO_E_VIRGULA bloco PONTO_E_VIRGULA
    {  
        if (!setouVariavelFuncao)
        {   
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Resultado de funcao %s nao foi setada",pilhaIdentificadorFuncao[pilhaIdentificadorFuncaoTopo]); 
            imprimeErro(str);
        }
        pilhaIdentificadorFuncaoTopo--;
        declarouFuncao=0;
        // to-do: check if value was assigned to name of function
        char str[DEFAULT_STRING_LENGTH];
        int parametros = 0;
        if (numeroParametros.topo > -1)
        {
            parametros =  numeroParametros.elementos[numeroParametros.topo ];
            removeElemento(&numeroParametros, 1);
        }
        sprintf(str, "RTPR %d, %d", nivelLexico,parametros);
        geraCodigo(NULL, str); 
        // remove parameters from symbols table
        deleta(&p, parametros);

    }
;


/*
**------------------------------------------------------------------
  ___  _   ___    _   __  __ ___ _____ ___ ___  ___ 
 | _ \/_\ | _ \  /_\ |  \/  | __|_   _| __| _ \/ __|
 |  _/ _ \|   / / _ \| |\/| | _|  | | | _||   /\__ \
 |_|/_/ \_\_|_\/_/ \_\_|  |_|___| |_| |___|_|_\|___/
                                                                   
**------------------------------------------------------------------
*/

parametros_formais:
    |
    ABRE_PARENTESES 
    secao_parametros_formais_helper
    {
        // after declaring all parameters, set their dislocation
        setaDeslocamento(&p);
        // imprimeTS(&p);
    }
    FECHA_PARENTESES
;

secao_parametros_formais_helper:
    secao_parametros_formais
    | secao_parametros_formais_helper PONTO_E_VIRGULA secao_parametros_formais
;

secao_parametros_formais:
    lista_idents_param DOIS_PONTOS IDENT
    {
        if (setaTipo(&p, token) == -1)
        {
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Tipo nao definido: %s",token); 
            imprimeErro(str);
        }
        setaPassagem(&p, VALOR);
    }

    | VAR lista_idents_param DOIS_PONTOS IDENT
    {
        if (setaTipo(&p, token) == -1)
        {
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Tipo nao definido: %s",token); 
            imprimeErro(str);
        }
        setaPassagem(&p, REFERENCIA);
    }
;

lista_idents_param:
    lista_idents_param VIRGULA IDENT  
    {
        insereNaTabelaDeSimbolos(PARAM_FORMAL,"");
        numeroParametros.elementos[numeroParametros.topo]++;
    }
    | IDENT 
    {
        insereNaTabelaDeSimbolos(PARAM_FORMAL,"");
        numeroParametros.elementos[numeroParametros.topo]++;
    }
;



/*
**------------------------------------------------------------------
 __   ___   ___ 
 \ \ / /_\ | _ \
  \ V / _ \|   /
   \_/_/ \_\_|_\
                
**------------------------------------------------------------------
*/


parte_declara_vars_helper:
    
    | parte_declara_vars
;


parte_declara_vars:  
    var 
    | parte_declara_vars var
;


var         : 
    { } VAR declara_vars 
;

declara_vars: 
    declara_vars declara_var 
    | declara_var 

;

declara_var : 
    { contadorVariaveis = 0; } 
    lista_id_var DOIS_PONTOS 
    tipo 
    { 
      /* Allocates memory */
      char str[DEFAULT_STRING_LENGTH];
      sprintf(str, "%s %d","AMEM",contadorVariaveis); 
      geraCodigo(NULL, str);
    }
    PONTO_E_VIRGULA
;

tipo        : 
    IDENT 
    {
        if (setaTipo(&p, token) == -1)
        {
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Tipo nao definido: %s",token); 
            imprimeErro(str);
        }
    }
;

lista_id_var: 
    lista_id_var VIRGULA identificador_var
    | identificador_var
;
identificador_var:
    IDENT 
    {
      /* insere vars na tabela de símbolos */
        insereNaTabelaDeSimbolos(VAR_SIMPLES, "");
    }

;

lista_idents:
    lista_idents VIRGULA IDENT  
    | IDENT 
;

/*
**------------------------------------------------------------------
   ___ ___  __  __ __  __   _   _  _ ___  ___ 
  / __/ _ \|  \/  |  \/  | /_\ | \| |   \/ __|
 | (_| (_) | |\/| | |\/| |/ _ \| .` | |) \__ \
  \___\___/|_|  |_|_|  |_/_/ \_\_|\_|___/|___/
                                              
**------------------------------------------------------------------
*/


comando_compost_ou_sem_rotulo:
    comando_composto
    | comando
;

comando_composto: 
    T_BEGIN comandos T_END
     /* ! can it not have any comands? */
;
comandos:
    comando
    | comandos PONTO_E_VIRGULA comando
    | comandos PONTO_E_VIRGULA
    |

;

comando:
    NUMERO DOIS_PONTOS comando_sem_rotulo 
    | comando_sem_rotulo
;

comando_sem_rotulo : 
    IDENT 
    {
        int index = busca(&p, token, -1);
        if (p.elementos[index].categoria == FUNCAO || p.elementos[index].categoria == PROCEDIMENTO )
        {
            calledSubprogram=1;
            pilhaIdentificadorEsquerdaTopo++;
            strcpy(pilhaIdentificadorEsquerda[pilhaIdentificadorEsquerdaTopo], token);
        }
        strcpy(l_oper, token); 
    } 
    regra_oper_esq
    {
        calledSubprogram = ( (pilhaIdentificadorEsquerdaTopo-=calledSubprogram) < -1);
        // calledSubprogram=0;
        // if (calledSubprogram)
        // {
        //     calledSubprogram=0;
        //     pilhaIdentificadorEsquerdaTopo--;
        // }

    }
    | comando_repetitivo
    | comando_condicional
    | WRITE ABRE_PARENTESES lista_idents_write FECHA_PARENTESES
    | READ  ABRE_PARENTESES lista_idents_read  FECHA_PARENTESES 
;


/*
**------------------------------------------------------------------
  ___ ___   _   ___   ___      _____ ___ _____ ___ 
 | _ \ __| /_\ |   \ / | \    / / _ \_ _|_   _| __|
 |   / _| / _ \| |) / / \ \/\/ /|   /| |  | | | _| 
 |_|_\___/_/ \_\___/_/   \_/\_/ |_|_\___| |_| |___|
                                                   
**------------------------------------------------------------------
*/

lista_idents_write: 
    expressao_leitura
    | lista_idents_write VIRGULA expressao_leitura
;

expressao_leitura:
    // load whats in the token and print
    expressao
    { 
        geraCodigo(NULL, "IMPR");
        removeElemento(&typesStack, 1);

    }

;

lista_idents_read: 
    identificador_leitura
    | lista_idents_read VIRGULA identificador_leitura
;

identificador_leitura:
    // read something and store in token
    IDENT
    {
        int index = busca(&p, token,-1);
        checaVariavel(index, token);
        checaCategoria(index);
        if (p.elementos[index].categoria != VAR_SIMPLES)
        {
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Categoria Invalida para leitura %s",token);      
            imprimeErro(str);
        }
        geraCodigo(NULL, "LEIT");
        char str[DEFAULT_STRING_LENGTH];
        if (p.elementos[index].passagem == REFERENCIA)
            sprintf(str, "%s", "ARMI");
        else
            sprintf(str, "%s", "ARMZ");
        sprintf(str, "%s %d, %d",str, p.elementos[index].nivel,p.elementos[index].deslocamento); 
        geraCodigo(NULL, str);  


    }

/*
**------------------------------------------------------------------
  _    ___ ___ _____    ___  ___ ___ ___    _   _  _ ___  
 | |  | __| __|_   _|  / _ \| _ \ __| _ \  /_\ | \| |   \ 
 | |__| _|| _|  | |   | (_) |  _/ _||   / / _ \| .` | |) |
 |____|___|_|   |_|    \___/|_| |___|_|_\/_/ \_\_|\_|___/ 
                                                                                                                  
**------------------------------------------------------------------
*/

regra_oper_esq:
    // atribuicao
    ATRIBUICAO expressao 
    {
        // used to check if function result was set.
        if (declarouFuncao && strcmp(pilhaIdentificadorFuncao[pilhaIdentificadorFuncaoTopo], l_oper));
        {
            setouVariavelFuncao = 1;
        }
    // get the index of the left operand and check if it's type is the same as the expression's type
        int index = busca(&p, l_oper, -1);
        checaVariavel(index, l_oper);
        if (p.elementos[index].categoria != VAR_SIMPLES && p.elementos[index].categoria != PARAM_FORMAL && p.elementos[index].categoria != FUNCAO)
        {
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Identificador \"%s\" nao corresponde a variavel ou parametro",l_oper);      
            imprimeErro(str);
        }
        insereElemento(&typesStack, p.elementos[index].tipo);
        checaTipos();        
        removeElemento(&typesStack, 1);
        // save to memory at level, dislocation of variable
        char str[DEFAULT_STRING_LENGTH];
        if (p.elementos[index].passagem == REFERENCIA)
            sprintf(str, "%s", "ARMI");
        else
            sprintf(str, "%s", "ARMZ");
        sprintf(str, "%s %d, %d",str, p.elementos[index].nivel,p.elementos[index].deslocamento); 
        geraCodigo(NULL, str);  
        l_oper[0] = '\0';
        saveLeftOperand=0;
    }
    // chama proc com parametros
    | ABRE_PARENTESES
    {
        // count parameters
        // contadorParametros = 0;

        insereElemento(&SeccontadorParametros, 0);
        calledSubprogram=1;

    } 
    lista_de_expressoes 
    {

    }
    FECHA_PARENTESES
    regra_oper_esq_helper
    // chama proc sem parametros
    | regra_oper_esq_helper
    
;

regra_oper_esq_helper:

    {
        int index = busca(&p, l_oper, -1);
        checaVariavel(index, l_oper);
        calledSubprogram=0;
        printf("%d\n",p.elementos[index].categoria );
        // check if procedure or function, if not, cant be called here
        if (SeccontadorParametros.elementos[SeccontadorParametros.topo] == -1)SeccontadorParametros.elementos[SeccontadorParametros.topo]=0;
        if (p.elementos[index].categoria != PROCEDIMENTO && p.elementos[index].categoria != FUNCAO)
        {
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Identificador \"%s\" nao corresponde a procedimento ou funcao",l_oper);      
            imprimeErro(str);
        }
        // check if number os parameters passed to procedure/function is the same as expected
        else if (SeccontadorParametros.elementos[SeccontadorParametros.topo] != p.elementos[index].numeroParametros)
        {
            printf("%d\n", p.elementos[index].numeroParametros );
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Numero errado de parametros passados para %s, esperados: %d, obtido:%d",
                l_oper, 
                p.elementos[index].numeroParametros,
                SeccontadorParametros.elementos[SeccontadorParametros.topo]);      
            imprimeErro(str);

        }
        else
        {
            removeElemento(&SeccontadorParametros, 1);
            // check parameters types
            for (int i =  p.elementos[index].numeroParametros-1; i >= 0 ; --i)
            {
                insereElemento(&typesStack, p.elementos[index].parametros[i].tipo);
                checaTipos();
                removeElemento(&typesStack, 1);
            }
            // checar se variaveis passadas certo
            if (p.elementos[index].categoria == FUNCAO)
            {
                geraCodigo(NULL, "AMEM 1");  
            }
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "%s %s, %d","CHPR", p.elementos[index].rotulo, nivelLexico); 
            geraCodigo(NULL, str);  

        }

    }

;



/*
**------------------------------------------------------------------
  ___ ___   _____ _  _ ___ _  _   ___ _    ___ ___ 
 |_ _| __| |_   _| || | __| \| | | __| |  / __| __|
  | || _|    | | | __ | _|| .` | | _|| |__\__ \ _| 
 |___|_|     |_| |_||_|___|_|\_| |___|____|___/___|
                                                   
**------------------------------------------------------------------
*/
comando_condicional: cond_if
;

cond_if: 
    if_then cond_else
    {
        // if "else" statement present, tag to leave if statement.
        // if not, tag where code jumps to when if expression false
        char rotuloSai[DEFAULT_STRING_LENGTH];
        strcpy(rotuloSai,pilhaRotuloInicio[pilhaRotuloInicioTopo]);
        pilhaRotuloInicioTopo--;
        geraCodigo(rotuloSai, "NADA");

    }
;


if_then: 
    IF
    expressao
    {
        // check if boolean expression

        insereElemento(&typesStack, BOOL);
        checaTipos();        
        removeElemento(&typesStack, 1);

    }
    THEN
    {
        // tag that either jumps to else statement or to the rest of the code
        char rotuloElseOuSai[DEFAULT_STRING_LENGTH];
        strcpy(rotuloElseOuSai, geraRotulo(1));        
        printf("%s\n",rotuloElseOuSai );
        
        char str[DEFAULT_STRING_LENGTH];
        strcpy(rotuloElseOuSai,pilhaRotuloInicio[pilhaRotuloInicioTopo]);
        sprintf(str, "DSVF %s", rotuloElseOuSai);
        geraCodigo(NULL, str); 

    }
    comando_compost_ou_sem_rotulo 

;

cond_else: 
    ELSE
    {
        // there's else statement, so tag will be used to jump here
        // in the case of false if statement expression
        char rotuloElse[DEFAULT_STRING_LENGTH];
        strcpy(rotuloElse,pilhaRotuloInicio[pilhaRotuloInicioTopo]);
        pilhaRotuloInicioTopo--;
        // stacks new tag that jumps to the rest of the code
        // and skips else, in case the expression of the if statement was true
        char rotuloSai[DEFAULT_STRING_LENGTH];
        strcpy(rotuloSai, geraRotulo(1));
        printf("%s\n",rotuloSai );        
        char str[DEFAULT_STRING_LENGTH];
        strcpy(rotuloSai,pilhaRotuloInicio[pilhaRotuloInicioTopo]);
        sprintf(str, "DSVS %s", rotuloSai);
        geraCodigo(NULL, str); 


        geraCodigo(rotuloElse, "NADA");


    }
    comando_compost_ou_sem_rotulo

    | %prec LOWER_THAN_ELSE
;


/*
**------------------------------------------------------------------
 __      ___  _ ___ _    ___ 
 \ \    / / || |_ _| |  | __|
  \ \/\/ /| __ || || |__| _| 
   \_/\_/ |_||_|___|____|___|
                             
**------------------------------------------------------------------
*/
comando_repetitivo:
    WHILE
    {
        // generate first tag (get in while)
        char rotuloEntra[DEFAULT_STRING_LENGTH];
        strcpy(rotuloEntra, geraRotulo(1));
        printf("%s\n",rotuloEntra );
        char str[DEFAULT_STRING_LENGTH];
        geraCodigo(rotuloEntra, "NADA"); 
        // generate second tag (leave while)
        char rotuloSai[DEFAULT_STRING_LENGTH];
        strcpy(rotuloSai, geraRotulo(1));
        printf("%s\n",rotuloSai );

    }
    expressao
    {
        // this needs to be a bool 
        // since while tests only if something is true of false
        insereElemento(&typesStack, BOOL);
        checaTipos();        
        removeElemento(&typesStack, 1);

    }
    DO
    {

        char rotulo[DEFAULT_STRING_LENGTH];
        strcpy(rotulo,pilhaRotuloInicio[pilhaRotuloInicioTopo]);
        // pilhaRotuloInicioTopo--;

        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "DSVF %s", rotulo);
        geraCodigo(NULL, str); 


    }
    comando_compost_ou_sem_rotulo
    {
        char rotuloEntra[DEFAULT_STRING_LENGTH];
        char rotuloSai[DEFAULT_STRING_LENGTH];
        char str[DEFAULT_STRING_LENGTH];
        strcpy(rotuloSai,pilhaRotuloInicio[pilhaRotuloInicioTopo]);
        pilhaRotuloInicioTopo--;
        strcpy(rotuloEntra,pilhaRotuloInicio[pilhaRotuloInicioTopo]);
        pilhaRotuloInicioTopo--;
        sprintf(str, "DSVS %s", rotuloEntra);
        geraCodigo(NULL, str); 
        geraCodigo(rotuloSai, "NADA"); 
        
        
    }
    
;
/*
**------------------------------------------------------------------
  _____  _____ ___ ___ ___ ___ ___ ___  _  _ ___ 
 | __\ \/ / _ \ _ \ __/ __/ __|_ _/ _ \| \| / __|
 | _| >  <|  _/   / _|\__ \__ \| | (_) | .` \__ \
 |___/_/\_\_| |_|_\___|___/___/___\___/|_|\_|___/
                                                 
**------------------------------------------------------------------
*/


lista_de_expressoes:
    lista_de_expressoes_helper
    | lista_de_expressoes VIRGULA lista_de_expressoes_helper
;
lista_de_expressoes_helper:
    {
        insereElemento(&elementosExpressao, 0);  
    }
    expressao 
    {
        // check if its subprogram
        if (calledSubprogram)
        {
            int indexSubprogram = busca(&p, pilhaIdentificadorEsquerda[pilhaIdentificadorEsquerdaTopo], -1);
            int in = p.elementos[indexSubprogram].numeroParametros - 1 - SeccontadorParametros.elementos[SeccontadorParametros.topo] ;

            if (in>=0 && p.elementos[indexSubprogram].parametros[in].passagem == REFERENCIA)
            {
                if(elementosExpressao.elementos[elementosExpressao.topo] > 1)
                    imprimeErro ("Esperava variavel, recebeu expressao ou numero");
            }

        }
        removeElemento(&elementosExpressao, 1);
        SeccontadorParametros.elementos[SeccontadorParametros.topo]++;
    }

;

expressao : 
    expressao_simples relacao 
    {
        // if has relationship, it's a boolean expression
        // relationship: if is has greater or lesser than, must be between integers (no booleans allowed)
        checaTipos();
        removeElemento(&typesStack, 1);
        insereElemento(&typesStack, BOOL);       
    }
    |
    expressao_simples

;

relacao: 
    IGUAL expressao_simples
    {geraCodigo(NULL, "CMIG");}
    | DIFERENTE expressao_simples
    {geraCodigo(NULL, "CMDG");}
    | MENOR expressao_simples
    {geraCodigo(NULL, "CMME");}
    | MENOR_IGUAL expressao_simples
    {geraCodigo(NULL, "CMEG");}
    | MAIOR expressao_simples
    {geraCodigo(NULL, "CMMA");}
    | MAIOR_IGUAL expressao_simples
    {geraCodigo(NULL, "CMAG");}
;

expressao_simples: 
    // since + signal doesn't change the signal of the expression, we just consume it
    // and we don't need to deal with it like the - signal
    SOMA expressao_simples_helper 
    {
        if (elementosExpressao.topo>=0)
            elementosExpressao.elementos[elementosExpressao.topo]+=2;
    }
    | SUBTRAI 
    {
    if (elementosExpressao.topo>=0)
        elementosExpressao.elementos[elementosExpressao.topo]+=2;
    // deals with minus signal before expression
    // since there may be an expression inside another expression (using parenthesis)
    // we must know in which level we are 
      nivelExpressao++;
      char str[DEFAULT_STRING_LENGTH];
      sprintf(str, "%s %s","CRCT","0"); 
      geraCodigo(NULL, str);
      // initialize with 1 so se know we have a minus signal to deal with
      countTermo[nivelExpressao] = 1;
    }
    expressao_simples_helper 
    {
      // restore to 0 since we already dealed with it
      countTermo[nivelExpressao] = 0;
      // decreases level
      nivelExpressao--;
    }

    | expressao_simples_helper
;

expressao_simples_helper: 
    // chamada_funcao |
    {
          // only increments if it was initialized with one
          // that means only expression levels with minus signals will be incremented
          countTermo[nivelExpressao]+= countTermo[nivelExpressao] > 0;
    }

    termo 

    {
        // decreases counter. 
        // We only generate the SUBT code if we're in the "first" term of the tree
        // i can explain this but it's too big an explanation to put in comments
        countTermo[nivelExpressao]-= countTermo[nivelExpressao] > 0;
        // if expression started with minus signal, generate SUBT code
        if (countTermo[nivelExpressao] == 1) 
        {
        geraCodigo(NULL, "SUBT");
        }

    } 
    | expressao_simples_helper  SOMA termo 
    { 
        checaTipos();
        geraCodigo(NULL, "SOMA"); 
    }
    | expressao_simples_helper SUBTRAI termo  
    {
        checaTipos();
        geraCodigo(NULL, "SUBT");
    }
    | expressao_simples_helper OR termo 
    {
        checaTipos();
        geraCodigo(NULL, "DISJ");
    }
;



termo: 
    fator 
    | termo MULTIPLICA fator 
    {
        checaTipos();
        geraCodigo(NULL, "MULT");
    }
    | termo DIVIDE fator  
    {
        checaTipos();
        geraCodigo(NULL, "DIVI");
    }
    | termo AND fator 
    { 
        checaTipos();
        geraCodigo(NULL, "CONJ");
    }
;

fator: 
    // chamada_funcao |
    variavel
    | NUMERO 
    {
        // since we got a number/variable, increment the number of elements
        // in the expression
        if (elementosExpressao.topo>=0)
            elementosExpressao.elementos[elementosExpressao.topo]+=2;
        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "%s %s","CRCT",token); 
        geraCodigo(NULL, str);
        insereElemento(&typesStack, INTEGER);
    }
    // | chamada_funcao
    | ABRE_PARENTESES expressao FECHA_PARENTESES
    | NOT fator {geraCodigo(NULL, "NEGA");}

    | TRUE_T
    {
        // since we got a number/variable, increment the number of elements
        // in the expression
        if (elementosExpressao.topo>=0)
            elementosExpressao.elementos[elementosExpressao.topo]+=2;
        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "%s %d","CRCT",1); 
        geraCodigo(NULL, str);
        insereElemento(&typesStack, BOOL);
    }
    | FALSE_T
    {
        // since we got a number/variable, increment the number of elements
        // in the expression
        if (elementosExpressao.topo>=0)
            elementosExpressao.elementos[elementosExpressao.topo]+=2;
        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "%s %d","CRCT",0); 
        geraCodigo(NULL, str);
        insereElemento(&typesStack, BOOL);
    }
;

variavel:
    IDENT 
    {
        if (elementosExpressao.topo>=0)
            elementosExpressao.elementos[elementosExpressao.topo]+=1;
        pilhaIdentificadorEsquerdaTopo++;
        strcpy(pilhaIdentificadorEsquerda[pilhaIdentificadorEsquerdaTopo], token);
    }
    direita;
    
;

direita:
{ 
        int index = busca(&p, pilhaIdentificadorEsquerda[pilhaIdentificadorEsquerdaTopo],-1);
        pilhaIdentificadorEsquerdaTopo--;
        checaVariavel(index, token);
        if ( p.elementos[index].categoria != VAR_SIMPLES &&
        p.elementos[index].categoria != FUNCAO &&
        p.elementos[index].categoria != PARAM_FORMAL )
        {
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Variavel/Funcao nao definida %s",token);      
            imprimeErro(str);
        }
        if (saveLeftOperand && strlen(l_oper) == 0)
        {
            strcpy(l_oper, token); 
        }
        else
        {
            // if isn't a function
            if (p.elementos[index].categoria != FUNCAO )
            {               
                int esperadoEnderecoParametro=0;
                // check if a subprogram was called
                // check if variable is passe by value or refecence

                if (calledSubprogram)
                {
                    int indexSubprogram = busca(&p, pilhaIdentificadorEsquerda[pilhaIdentificadorEsquerdaTopo], -1);
                    int in = p.elementos[indexSubprogram].numeroParametros - 1 - SeccontadorParametros.elementos[SeccontadorParametros.topo] ;

                    if (in>=0 && p.elementos[indexSubprogram].parametros[in].passagem == REFERENCIA)
                    {
                        esperadoEnderecoParametro=1;
                    }

                }
                // if (calledSubprogram)
                // {
                //     int indexSubprogram = busca(&p, l_oper, -1);
                //     if (p.elementos[indexSubprogram].numeroParametros - 1 - SeccontadorParametros.elementos[SeccontadorParametros.topo] >= 0)
                //     {
                //         int in = p.elementos[indexSubprogram].numeroParametros - 1 - SeccontadorParametros.elementos[SeccontadorParametros.topo] ;
                //         if (p.elementos[indexSubprogram].parametros[in].passagem == REFERENCIA)
                //         {
                //            esperadoEnderecoParametro=1;

                //         }
                //     }
                // }
                if (esperadoEnderecoParametro)
                {
                    int indexSubprogram = busca(&p, pilhaIdentificadorEsquerda[pilhaIdentificadorEsquerdaTopo], -1);
                    int in = p.elementos[indexSubprogram].numeroParametros - 1 - SeccontadorParametros.elementos[SeccontadorParametros.topo] ;
                    if (p.elementos[indexSubprogram].parametros[in].passagem == REFERENCIA)
                    {
                        // printf("tipo da variavel%d\n", );
                        char str[DEFAULT_STRING_LENGTH];
                        // checks if the parameter is already passed by reference
                        // then we need to use it like is is since already is the address
                        // if we don't, we'll load the address oh the address
                        if (p.elementos[index].passagem==REFERENCIA)
                            sprintf(str, "%s", "CRVL");
                        else
                            sprintf(str, "%s", "CREN");

                        sprintf(str, "%s %d, %d",str, p.elementos[index].nivel,p.elementos[index].deslocamento); 
                        geraCodigo(NULL, str);  
                        insereElemento(&typesStack, p.elementos[index].tipo); 

                    }
                }
                else
                {
                    char str[DEFAULT_STRING_LENGTH];
                    if (p.elementos[index].passagem == REFERENCIA)
                        sprintf(str, "%s", "CRVI");
                    else
                        sprintf(str, "%s", "CRVL");
                    sprintf(str, "%s %d, %d",str, p.elementos[index].nivel,p.elementos[index].deslocamento); 
                    geraCodigo(NULL, str);  
                    insereElemento(&typesStack, p.elementos[index].tipo);        
                }

            }
            else
            {
                geraCodigo(NULL, "AMEM 1");
                char str[DEFAULT_STRING_LENGTH];
                sprintf(str, "%s %s, %d","CHPR", p.elementos[index].rotulo, nivelLexico); 
                geraCodigo(NULL, str);  
                // insert type of function in types stack
                insereElemento(&typesStack, p.elementos[index].tipo);


            }
        }
    }
    | 
     ABRE_PARENTESES

    {
        // count parameters
        insereElemento(&SeccontadorParametros, 0);
        // contadorParametros = 0;
        calledSubprogram=1;
        // elementosExpressao.elementos[elementosExpressao.topo]+=1;
         {geraCodigo(NULL, "AMEM 1");}
    }
    lista_de_expressoes

    FECHA_PARENTESES
    {

        calledSubprogram=0;
        // pega string topo da pilha de funções chamadas
        int index = busca(&p, pilhaIdentificadorEsquerda[pilhaIdentificadorEsquerdaTopo],-1);
        // pilhaIdentificadorEsquerdaTopo--;
        checaVariavel(index, pilhaIdentificadorEsquerda[pilhaIdentificadorEsquerdaTopo]);
        pilhaIdentificadorEsquerdaTopo--;
        // check if procedure or function, if not, cant be called here
        if (p.elementos[index].categoria != FUNCAO)
        {
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Identificador \"%s\" nao corresponde a funcao",l_oper);      
            imprimeErro(str);
        }
        // check if number os parameters passed to procedure/function is the same as expected
        else if (SeccontadorParametros.elementos[SeccontadorParametros.topo] != p.elementos[index].numeroParametros)
        {
            printf("%d\n", p.elementos[index].numeroParametros );
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Numero errado de parametros passados para %s, esperados: %d, obtido:%d",
                l_oper, 
                p.elementos[index].numeroParametros,
                SeccontadorParametros.elementos[SeccontadorParametros.topo]);      
            imprimeErro(str);

        }
        else
        {
            // check parameters types
            for (int i =  p.elementos[index].numeroParametros-1; i >= 0 ; --i)
            {
                insereElemento(&typesStack, p.elementos[index].parametros[i].tipo);
                checaTipos();
                removeElemento(&typesStack, 1);
            }
            removeElemento(&SeccontadorParametros, 1);
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "%s %s, %d","CHPR", p.elementos[index].rotulo, nivelLexico); 
            geraCodigo(NULL, str);  
            // insert type of function in types stack
            insereElemento(&typesStack, p.elementos[index].tipo);

        }

    }
;


%%
// function to check if types match to make operation
void checaTipos()
{
    if (typesStack.topo && 
        typesStack.elementos[typesStack.topo] != typesStack.elementos[typesStack.topo-1] )
    {
        int tipo1, tipo2;
        tipo1 = typesStack.elementos[typesStack.topo];
        tipo2 = typesStack.elementos[typesStack.topo-1];
        // tests if subtype match type (or the other way around)
        if (controleSubtipo[tipo1] == tipo2 || controleSubtipo[tipo2] == tipo1)
        {

            removeElemento(&typesStack, 2);
            insereElemento(&typesStack, controleSubtipo[tipo1] );
            return;
        }
        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "Tipos incompativeis: %s/%s", 
        tabelaTipos(typesStack.elementos[typesStack.topo]),
        tabelaTipos(typesStack.elementos[typesStack.topo-1]));      
        imprimeErro(str);
    }
    removeElemento(&typesStack, 1);

}

void insereNaTabelaDeSimbolos(int categoria, char *rotulo)
{
        ssimbolo s; 
    if (categoria == VAR_SIMPLES)
    {
        // check if var with that name exists in this lexical level
        int wasDeclared = busca(&p, token, nivelLexico);
        if (wasDeclared!= -1)
        {
    
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Overload de Identificador: %s",token );   
            imprimeErro(str);
        }
        contadorVariaveis++; 
        inicializasSimboloVar(&s, token, nivelLexico, deslocamento[nivelLexico]); 
        deslocamento[nivelLexico]++;
    }
    else if (categoria == PROCEDIMENTO)
    {
        // check if var with that name exists in this lexical level
        int wasDeclared = busca(&p, token, -1);
        if (wasDeclared!= -1)
        {
    
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Overload de Identificador: %s",token );   
            imprimeErro(str);
        }
        inicializasSimboloProc(&s, 
            token, 
            nivelLexico, 
            deslocamento[nivelLexico],
            rotulo); 

    }
    else if (categoria == FUNCAO)
    {
        // check if var with that name exists in this lexical level
        int wasDeclared = busca(&p, token, -1);
        if (wasDeclared!= -1)
        {
    
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Overload de Identificador: %s",token );   
            imprimeErro(str);
        }
        inicializasSimboloFunc(&s, 
            token, 
            nivelLexico, 
            rotulo); 

    }
    else if (categoria == PARAM_FORMAL)
    {
        // check if var with that name exists in this lexical level
        int wasDeclared = busca(&p, token, nivelLexico );
        if (wasDeclared!= -1)
        {
    
            char str[DEFAULT_STRING_LENGTH];
            sprintf(str, "Overload de Identificador: %s",token );   
            imprimeErro(str);
        }
        inicializasSimboloParamFormal(&s, 
            token, 
            nivelLexico); 

    }
    insere(&p, &s); 
}

void checaVariavel(int index, char* iden)
{
    if (index == -1)
    {
        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "Identificador nao definido %s",iden);      
        imprimeErro(str);
    }
}

void checaCategoria(int index)
{
    if (p.elementos[index].categoria != VAR_SIMPLES)
    {
        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "Categoria Invalida para leitura %s",token);      
        imprimeErro(str);
    }
}
// funtion to generate next tag 
char* geraRotulo(int colocaNaPilha)
{
    char* rotulo = (char*)malloc(sizeof(char)*DEFAULT_STRING_LENGTH);
    sprintf(rotulo, "R%s%d", tagCounter<10?"0":"", tagCounter);
    tagCounter++;
    if (colocaNaPilha)
    {
        pilhaRotuloInicioTopo++;
        strcpy(pilhaRotuloInicio[pilhaRotuloInicioTopo], rotulo);
       
    }
    return rotulo;
}

char* tabelaTipos(int n)
{
    return valorTipoPraString[n];
}

int main (int argc, char** argv) {
    FILE* fp;
    extern FILE* yyin;

    if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

    fp=fopen (argv[1], "r");
    if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
    }


    /* -------------------------------------------------------------------
    *  Inicia a Tabela de Símbolos
    * ------------------------------------------------------------------- */
    inicializaTS(&p);
    /* -------------------------------------------------------------------
    *  INICIALIZAÇÃO VARIÁVEIS DE CONTROLE
    * ------------------------------------------------------------------- */
    nivelLexico=0;
    nivelExpressao=0;
    saveLeftOperand=0;
    tagCounter = 0;
    contador_subrotinas = 0;
    // contadorParametros=0;
    calledSubprogram = 0;
    setouVariavelFuncao=0;
    declarouFuncao=0;

    pilhaRotuloInicioTopo=-1;
    pilhaIdentificadorEsquerdaTopo=-1;
    pilhaIdentificadorFuncaoTopo=-1;

    memset(deslocamento, 0, sizeof(deslocamento));
    memset(l_oper, 0, sizeof(l_oper));
    memset(countTermo, 0, sizeof(countTermo));
    memset(controleSubtipo, 0, sizeof controleSubtipo);
    inicializaPilha(&typesStack);
    inicializaPilha(&numeroParametros);
    inicializaPilha(&elementosExpressao);
    inicializaPilha(&SeccontadorParametros);

    // initialize types array with known types (and one type "desconhecido")
    vetorDeTipos[0].valor = 0;
    vetorDeTipos[0].ValorsubTipo = 0;
    strcpy(vetorDeTipos[0].nome, "desconhecido");
    vetorDeTipos[1].valor = 1;
    vetorDeTipos[1].ValorsubTipo = 1;
    strcpy(vetorDeTipos[1].nome, "integer");
    vetorDeTipos[2].valor = 2;
    vetorDeTipos[2].ValorsubTipo = 2;
    strcpy(vetorDeTipos[2].nome, "boolean");
    taMvetorDeTipos=3;
    controleSubtipo[0]=0;
    controleSubtipo[1]=1;
    controleSubtipo[2]=2;
    // valorTipoPraString[1000][DEFAULT_STRING_LENGTH];
    strcpy(valorTipoPraString[0], "desconhecido");
    strcpy(valorTipoPraString[1], "integer");
    strcpy(valorTipoPraString[2], "boolean");


    /* -------------------------------------------------------------------
    *  FIM INICIALIZAÇÕES
    * ------------------------------------------------------------------- */
    

    yyin=fp;
    yyparse();
    #ifdef DEBUG 
    printf("%d\n",numeroParametros.topo );
    printf("%d\n",elementosExpressao.topo );
    printf("%d\n",typesStack.topo );
    printf("%d\n",pilhaIdentificadorFuncaoTopo );
    printf("%d\n",pilhaRotuloInicioTopo );
    printf("%d\n",pilhaIdentificadorEsquerdaTopo );
    imprimeTS(&p);
    #endif 
    

   return 0;
}

/*
http://patorjk.com/software/taag 
*/