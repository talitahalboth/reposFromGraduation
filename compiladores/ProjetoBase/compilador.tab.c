/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 6 "compilador.y" /* yacc.c:339  */

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


int tagCounter;
int contador_subrotinas;
int calledSubprogram;
int declarouFuncao;
int setouVariavelFuncao;
pilha elementosExpressao;


#line 118 "compilador.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "compilador.tab.h".  */
#ifndef YY_YY_COMPILADOR_TAB_H_INCLUDED
# define YY_YY_COMPILADOR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROGRAM = 258,
    ABRE_PARENTESES = 259,
    FECHA_PARENTESES = 260,
    VIRGULA = 261,
    PONTO_E_VIRGULA = 262,
    DOIS_PONTOS = 263,
    PONTO = 264,
    LABEL = 265,
    TYPE = 266,
    ARRAY = 267,
    PROCEDURE = 268,
    FUNCTION = 269,
    GOTO = 270,
    IF = 271,
    THEN = 272,
    ELSE = 273,
    WHILE = 274,
    DO = 275,
    NOT = 276,
    IGUAL = 277,
    DIFERENTE = 278,
    MENOR = 279,
    MENOR_IGUAL = 280,
    MAIOR = 281,
    MAIOR_IGUAL = 282,
    SOMA = 283,
    SUBTRAI = 284,
    OR = 285,
    MULTIPLICA = 286,
    DIVIDE = 287,
    AND = 288,
    T_BEGIN = 289,
    T_END = 290,
    VAR = 291,
    IDENT = 292,
    ATRIBUICAO = 293,
    NUMERO = 294,
    READ = 295,
    WRITE = 296,
    TRUE_T = 297,
    FALSE_T = 298,
    LOWER_THAN_ELSE = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_COMPILADOR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 214 "compilador.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   139

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  78
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  201

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    75,    75,    75,    88,    97,   106,    88,   137,   138,
     139,   160,   177,   159,   183,   184,   189,   206,   188,   241,
     240,   264,   286,   291,   263,   331,   335,   333,   344,   345,
     349,   355,   363,   368,   388,   390,   395,   396,   401,   401,
     405,   406,   411,   414,   411,   424,   428,   429,   432,   441,
     442,   457,   458,   462,   466,   467,   468,   469,   474,   475,
     480,   479,   501,   502,   503,   504,   519,   520,   525,   535,
     536,   541,   576,   608,   617,   607,   623,   629,   690,   694,
     710,   719,   708,   737,   736,   760,   775,   789,   798,   774,
     839,   840,   843,   843,   868,   877,   882,   884,   886,   888,
     890,   892,   899,   905,   904,   926,   931,   931,   951,   956,
     961,   971,   972,   977,   982,   991,   992,  1004,  1005,  1007,
    1018,  1033,  1032,  1044,  1144,  1142
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "ABRE_PARENTESES",
  "FECHA_PARENTESES", "VIRGULA", "PONTO_E_VIRGULA", "DOIS_PONTOS", "PONTO",
  "LABEL", "TYPE", "ARRAY", "PROCEDURE", "FUNCTION", "GOTO", "IF", "THEN",
  "ELSE", "WHILE", "DO", "NOT", "IGUAL", "DIFERENTE", "MENOR",
  "MENOR_IGUAL", "MAIOR", "MAIOR_IGUAL", "SOMA", "SUBTRAI", "OR",
  "MULTIPLICA", "DIVIDE", "AND", "T_BEGIN", "T_END", "VAR", "IDENT",
  "ATRIBUICAO", "NUMERO", "READ", "WRITE", "TRUE_T", "FALSE_T",
  "LOWER_THAN_ELSE", "$accept", "programa", "$@1", "bloco", "$@2", "$@3",
  "$@4", "parte_declaracoes", "parte_declara_procedimento", "$@5", "$@6",
  "ponto_virgula", "declara_procedimento", "$@7", "$@8",
  "parte_declara_funcao", "$@9", "declara_funcao", "$@10", "$@11", "$@12",
  "parametros_formais", "$@13", "secao_parametros_formais_helper",
  "secao_parametros_formais", "lista_idents_param",
  "parte_declara_vars_helper", "parte_declara_vars", "var", "$@14",
  "declara_vars", "declara_var", "$@15", "$@16", "tipo", "lista_id_var",
  "identificador_var", "lista_idents", "comando_compost_ou_sem_rotulo",
  "comando_composto", "comandos", "comando", "comando_sem_rotulo", "$@17",
  "lista_idents_write", "expressao_leitura", "lista_idents_read",
  "identificador_leitura", "regra_oper_esq", "$@18", "$@19",
  "regra_oper_esq_helper", "comando_condicional", "cond_if", "if_then",
  "$@20", "$@21", "cond_else", "$@22", "comando_repetitivo", "$@23",
  "$@24", "$@25", "lista_de_expressoes", "lista_de_expressoes_helper",
  "$@26", "expressao", "relacao", "expressao_simples", "$@27",
  "expressao_simples_helper", "$@28", "termo", "fator", "variavel", "$@29",
  "direita", "$@30", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
# endif

#define YYPACT_NINF -159

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-159)))

#define YYTABLE_NINF -43

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -159,     8,    20,  -159,   -10,    30,     7,  -159,    55,    31,
      26,  -159,  -159,    46,    35,  -159,  -159,    35,  -159,    49,
    -159,  -159,  -159,    62,    59,  -159,    60,  -159,  -159,    45,
    -159,  -159,  -159,  -159,    18,  -159,    61,    63,    33,  -159,
      60,    64,  -159,  -159,  -159,  -159,    40,  -159,  -159,    91,
      98,    99,    -4,  -159,  -159,  -159,  -159,    86,  -159,  -159,
    -159,  -159,   101,   100,   101,  -159,  -159,  -159,   -12,    -8,
      -2,    40,     1,    43,    69,    40,    33,  -159,  -159,  -159,
     102,    41,  -159,  -159,  -159,  -159,    -8,  -159,    93,    40,
      40,    40,    40,    40,    40,  -159,    -2,    -2,    -2,    40,
      -2,  -159,  -159,  -159,  -159,   -15,  -159,  -159,  -159,  -159,
      40,  -159,  -159,  -159,  -159,    76,  -159,    87,  -159,  -159,
    -159,    17,  -159,    71,  -159,   104,  -159,    24,   105,   106,
      -8,  -159,  -159,  -159,  -159,  -159,  -159,  -159,   -15,   -15,
     -15,   108,  -159,   111,    -2,    -2,    -2,    96,  -159,  -159,
    -159,    69,  -159,    40,  -159,  -159,  -159,    42,    41,   112,
      81,    82,  -159,    83,    17,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,   115,  -159,    40,  -159,  -159,    85,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,    17,  -159,   118,  -159,
    -159,   117,    89,  -159,  -159,  -159,  -159,  -159,  -159,   119,
    -159
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    50,     0,     0,
       0,     4,    49,     0,    34,     3,     5,    35,    36,     0,
      10,    37,    42,     6,    39,    41,     0,    11,    19,     0,
       8,     9,    40,    48,     0,    47,     0,     0,    57,     7,
       0,     0,    16,    12,    21,    20,   106,    86,    60,     0,
       0,     0,     0,    54,    59,    63,    78,    85,    62,    46,
      45,    43,    25,    14,    25,   106,   103,    80,    95,   105,
       0,   106,    77,     0,     0,   106,    56,    53,    83,    79,
       0,     0,    17,    15,    13,    22,   102,   106,     0,   106,
     106,   106,   106,   106,   106,    94,     0,     0,     0,   106,
       0,   121,   116,   119,   120,   107,   111,   115,    87,    73,
     106,    61,    76,    58,    71,     0,    69,     0,    66,    68,
      55,     0,    44,     0,    33,    26,    28,     0,     0,     0,
     104,    81,    96,    97,    98,    99,   100,   101,   108,   109,
     110,     0,   118,   123,     0,     0,     0,     0,    92,    72,
      65,     0,    64,   106,    84,    51,    52,     0,     0,     0,
       0,     0,     4,     0,     0,   117,   124,   122,   112,   113,
     114,    88,    74,    90,   106,    70,    67,     0,    29,    27,
      32,    30,    18,    23,    82,    92,     0,    92,     0,    93,
      31,     0,     0,    89,    91,    77,     4,   125,    75,     0,
      24
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -159,  -159,  -159,  -153,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,    65,  -159,  -159,   -33,     4,  -159,  -159,   113,  -159,
    -159,   107,  -159,  -159,  -159,  -159,    92,  -159,  -158,   109,
    -159,   -34,    66,  -159,  -159,   -20,  -159,   -17,  -159,  -159,
    -159,   -60,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,   -49,   -50,  -159,   -46,  -159,    -3,  -159,
     -58,  -159,   -31,   -99,  -159,  -159,  -159,  -159
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    13,    14,    20,    29,    23,    30,    36,
      63,    84,    43,    62,   128,    31,    37,    45,    64,   129,
     191,    82,   159,   125,   126,   127,    16,    17,    18,    19,
      24,    25,    26,    80,    61,    34,    35,     8,   154,   155,
      52,   156,    54,    72,   117,   118,   115,   116,   111,   148,
     188,   112,    55,    56,    57,    88,   164,    79,   121,    58,
      71,   147,   186,   172,   173,   174,   119,    95,    68,    87,
      69,    70,   105,   106,   107,   143,   167,   185
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      67,   142,    99,    76,    53,   109,   184,    86,     3,   182,
      89,    90,    91,    92,    93,    94,   144,   145,   146,   100,
      96,    97,    98,     4,    40,   108,    41,     5,   193,   130,
     160,    77,   161,    46,     6,   101,    47,   102,    11,   110,
     103,   104,   120,   199,     7,   168,   169,   170,   160,    46,
     177,    38,    47,   141,    48,    15,    49,    50,    51,    46,
       9,    10,    47,    12,   149,   138,   139,   140,    65,    66,
      48,   -38,    49,    50,    51,    27,    28,   123,   124,    38,
      48,   150,   151,    50,    51,    22,   132,   133,   134,   135,
     136,   137,   152,   153,   197,   187,   -42,    33,    42,    73,
      44,    60,    74,    75,    78,    81,   114,    83,   124,   122,
     131,   158,   162,   165,   163,   166,   171,   179,   180,   181,
     183,   187,   190,   195,   196,   178,   200,   157,   189,    85,
      21,    32,    59,   176,   175,   198,   192,   194,    39,   113
};

static const yytype_uint8 yycheck[] =
{
      46,   100,     4,     7,    38,     4,   164,    65,     0,   162,
      22,    23,    24,    25,    26,    27,    31,    32,    33,    21,
      28,    29,    30,     3,     6,    71,     8,    37,   186,    87,
       6,    35,     8,    16,     4,    37,    19,    39,     7,    38,
      42,    43,    76,   196,    37,   144,   145,   146,     6,    16,
       8,    34,    19,    99,    37,     9,    39,    40,    41,    16,
       5,     6,    19,    37,   110,    96,    97,    98,    28,    29,
      37,    36,    39,    40,    41,    13,    14,    36,    37,    34,
      37,     5,     6,    40,    41,    36,    89,    90,    91,    92,
      93,    94,     5,     6,     5,     6,    37,    37,    37,     8,
      37,    37,     4,     4,    18,     4,    37,     7,    37,     7,
      17,     7,     7,     5,     8,     4,    20,     5,    37,    37,
      37,     6,    37,     5,     7,   158,     7,   123,   174,    64,
      17,    24,    40,   153,   151,   195,   185,   187,    29,    73
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    46,    47,     0,     3,    37,     4,    37,    82,     5,
       6,     7,    37,    48,    49,     9,    71,    72,    73,    74,
      50,    73,    36,    52,    75,    76,    77,    13,    14,    51,
      53,    60,    76,    37,    80,    81,    54,    61,    34,    84,
       6,     8,    37,    57,    37,    62,    16,    19,    37,    39,
      40,    41,    85,    86,    87,    97,    98,    99,   104,    81,
      37,    79,    58,    55,    63,    28,    29,   111,   113,   115,
     116,   105,    88,     8,     4,     4,     7,    35,    18,   102,
      78,     4,    66,     7,    56,    66,   115,   114,   100,    22,
      23,    24,    25,    26,    27,   112,    28,    29,    30,     4,
      21,    37,    39,    42,    43,   117,   118,   119,   111,     4,
      38,    93,    96,    87,    37,    91,    92,    89,    90,   111,
      86,   103,     7,    36,    37,    68,    69,    70,    59,    64,
     115,    17,   113,   113,   113,   113,   113,   113,   117,   117,
     117,   111,   118,   120,    31,    32,    33,   106,    94,   111,
       5,     6,     5,     6,    83,    84,    86,    70,     7,    67,
       6,     8,     7,     8,   101,     5,     4,   121,   118,   118,
     118,    20,   108,   109,   110,    92,    90,     8,    69,     5,
      37,    37,    48,    37,    83,   122,   107,     6,    95,   111,
      37,    65,   108,    83,   109,     5,     7,     5,    96,    48,
       7
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    47,    46,    49,    50,    51,    48,    52,    52,
      52,    54,    55,    53,    56,    56,    58,    59,    57,    61,
      60,    63,    64,    65,    62,    66,    67,    66,    68,    68,
      69,    69,    70,    70,    71,    71,    72,    72,    74,    73,
      75,    75,    77,    78,    76,    79,    80,    80,    81,    82,
      82,    83,    83,    84,    85,    85,    85,    85,    86,    86,
      88,    87,    87,    87,    87,    87,    89,    89,    90,    91,
      91,    92,    93,    94,    95,    93,    93,    96,    97,    98,
     100,   101,    99,   103,   102,   102,   105,   106,   107,   104,
     108,   108,   110,   109,   111,   111,   112,   112,   112,   112,
     112,   112,   113,   114,   113,   113,   116,   115,   115,   115,
     115,   117,   117,   117,   117,   118,   118,   118,   118,   118,
     118,   120,   119,   121,   122,   121
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     0,     0,     0,     6,     2,     2,
       0,     0,     0,     5,     0,     1,     0,     0,     6,     0,
       3,     0,     0,     0,    10,     0,     0,     4,     1,     3,
       3,     4,     3,     1,     0,     1,     1,     2,     0,     3,
       2,     1,     0,     0,     6,     1,     3,     1,     1,     3,
       1,     1,     1,     3,     1,     3,     2,     0,     3,     1,
       0,     3,     1,     1,     4,     4,     1,     3,     1,     1,
       3,     1,     2,     0,     0,     6,     1,     0,     1,     2,
       0,     0,     6,     0,     3,     0,     0,     0,     0,     7,
       1,     3,     0,     2,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     0,     3,     1,     0,     2,     3,     3,
       3,     1,     3,     3,     3,     1,     1,     3,     2,     1,
       1,     0,     3,     0,     0,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 75 "compilador.y" /* yacc.c:1646  */
    { 
      geraCodigo (NULL, "INPP"); 
    }
#line 1448 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 82 "compilador.y" /* yacc.c:1646  */
    {
      geraCodigo (NULL, "PARA"); 
    }
#line 1456 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 88 "compilador.y" /* yacc.c:1646  */
    {
            // stores the previous dislocation in case we need it to use again
            prevDeslocamento[nivelLexico] = deslocamento[nivelLexico];
            // sets dislocation to 0 since its starting to declare things here
            deslocamento[nivelLexico]=0;

 
    }
#line 1469 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 97 "compilador.y" /* yacc.c:1646  */
    {
        // generate a tag to enter the subprogram that we're in
        char rotuloIni[DEFAULT_STRING_LENGTH];
        strcpy(rotuloIni, geraRotulo(1));          
        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "DSVS %s", rotuloIni);
        geraCodigo(NULL, str);
    }
#line 1482 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 106 "compilador.y" /* yacc.c:1646  */
    { 
        // enter the subprogram
        char rotuloIni[DEFAULT_STRING_LENGTH];
        strcpy(rotuloIni,pilhaRotuloInicio[pilhaRotuloInicioTopo]);
        pilhaRotuloInicioTopo--;
        geraCodigo(rotuloIni, "NADA");
    }
#line 1494 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 114 "compilador.y" /* yacc.c:1646  */
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
#line 1517 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 160 "compilador.y" /* yacc.c:1646  */
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
#line 1538 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 177 "compilador.y" /* yacc.c:1646  */
    {
        nivelLexico--;
    }
#line 1546 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 189 "compilador.y" /* yacc.c:1646  */
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
#line 1567 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 206 "compilador.y" /* yacc.c:1646  */
    {
        // fill parameters array of procedure
        setaParametros(&p, l_oper);
    }
#line 1576 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 212 "compilador.y" /* yacc.c:1646  */
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
#line 1595 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 241 "compilador.y" /* yacc.c:1646  */
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
#line 1616 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 258 "compilador.y" /* yacc.c:1646  */
    {
        nivelLexico--;
    }
#line 1624 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 264 "compilador.y" /* yacc.c:1646  */
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
#line 1650 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 286 "compilador.y" /* yacc.c:1646  */
    {
        // fill parameters array of function
        setaParametros(&p, l_oper);
    }
#line 1659 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 291 "compilador.y" /* yacc.c:1646  */
    {
        setaTipoEDeslocamentoFuncao(&p, token);
    }
#line 1667 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 295 "compilador.y" /* yacc.c:1646  */
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
#line 1695 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 335 "compilador.y" /* yacc.c:1646  */
    {
        // after declaring all parameters, set their dislocation
        setaDeslocamento(&p);
        // imprimeTS(&p);
    }
#line 1705 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 350 "compilador.y" /* yacc.c:1646  */
    {
        setaTipo(&p, token);
        setaPassagem(&p, VALOR);
    }
#line 1714 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 356 "compilador.y" /* yacc.c:1646  */
    {
        setaTipo(&p, token);
        setaPassagem(&p, REFERENCIA);
    }
#line 1723 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 364 "compilador.y" /* yacc.c:1646  */
    {
        insereNaTabelaDeSimbolos(PARAM_FORMAL,"");
        numeroParametros.elementos[numeroParametros.topo]++;
    }
#line 1732 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 369 "compilador.y" /* yacc.c:1646  */
    {
        insereNaTabelaDeSimbolos(PARAM_FORMAL,"");
        numeroParametros.elementos[numeroParametros.topo]++;
    }
#line 1741 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 401 "compilador.y" /* yacc.c:1646  */
    { }
#line 1747 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 411 "compilador.y" /* yacc.c:1646  */
    { contadorVariaveis = 0; }
#line 1753 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 414 "compilador.y" /* yacc.c:1646  */
    { 
      /* Allocates memory */
      char str[DEFAULT_STRING_LENGTH];
      sprintf(str, "%s %d","AMEM",contadorVariaveis); 
      geraCodigo(NULL, str);
    }
#line 1764 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 424 "compilador.y" /* yacc.c:1646  */
    {setaTipo(&p, token);}
#line 1770 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 433 "compilador.y" /* yacc.c:1646  */
    {
      /* insere vars na tabela de símbolos */
        insereNaTabelaDeSimbolos(VAR_SIMPLES, "");
    }
#line 1779 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 480 "compilador.y" /* yacc.c:1646  */
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
#line 1794 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 491 "compilador.y" /* yacc.c:1646  */
    {
        calledSubprogram = ( (pilhaIdentificadorEsquerdaTopo-=calledSubprogram) < -1);
        // calledSubprogram=0;
        // if (calledSubprogram)
        // {
        //     calledSubprogram=0;
        //     pilhaIdentificadorEsquerdaTopo--;
        // }

    }
#line 1809 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 526 "compilador.y" /* yacc.c:1646  */
    { 
        geraCodigo(NULL, "IMPR");
        removeElemento(&typesStack, 1);

    }
#line 1819 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 542 "compilador.y" /* yacc.c:1646  */
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
#line 1845 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 577 "compilador.y" /* yacc.c:1646  */
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
#line 1879 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 608 "compilador.y" /* yacc.c:1646  */
    {
        // count parameters
        // contadorParametros = 0;

        insereElemento(&SeccontadorParametros, 0);
        calledSubprogram=1;

    }
#line 1892 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 617 "compilador.y" /* yacc.c:1646  */
    {

    }
#line 1900 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 629 "compilador.y" /* yacc.c:1646  */
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
#line 1952 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 695 "compilador.y" /* yacc.c:1646  */
    {
        // if "else" statement present, tag to leave if statement.
        // if not, tag where code jumps to when if expression false
        char rotuloSai[DEFAULT_STRING_LENGTH];
        strcpy(rotuloSai,pilhaRotuloInicio[pilhaRotuloInicioTopo]);
        pilhaRotuloInicioTopo--;
        geraCodigo(rotuloSai, "NADA");

    }
#line 1966 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 710 "compilador.y" /* yacc.c:1646  */
    {
        // check if boolean expression

        insereElemento(&typesStack, BOOL);
        checaTipos();        
        removeElemento(&typesStack, 1);

    }
#line 1979 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 719 "compilador.y" /* yacc.c:1646  */
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
#line 1996 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 737 "compilador.y" /* yacc.c:1646  */
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
#line 2022 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 775 "compilador.y" /* yacc.c:1646  */
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
#line 2040 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 789 "compilador.y" /* yacc.c:1646  */
    {
        // this needs to be a bool 
        // since while tests only if something is true of false
        insereElemento(&typesStack, BOOL);
        checaTipos();        
        removeElemento(&typesStack, 1);

    }
#line 2053 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 798 "compilador.y" /* yacc.c:1646  */
    {

        char rotulo[DEFAULT_STRING_LENGTH];
        strcpy(rotulo,pilhaRotuloInicio[pilhaRotuloInicioTopo]);
        // pilhaRotuloInicioTopo--;

        char str[DEFAULT_STRING_LENGTH];
        sprintf(str, "DSVF %s", rotulo);
        geraCodigo(NULL, str); 


    }
#line 2070 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 811 "compilador.y" /* yacc.c:1646  */
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
#line 2089 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 843 "compilador.y" /* yacc.c:1646  */
    {
        insereElemento(&elementosExpressao, 0);  
    }
#line 2097 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 847 "compilador.y" /* yacc.c:1646  */
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
#line 2119 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 869 "compilador.y" /* yacc.c:1646  */
    {
        // if has relationship, it's a boolean expression
        // relationship: if is has greater or lesser than, must be between integers (no booleans allowed)
        checaTipos();
        removeElemento(&typesStack, 1);
        insereElemento(&typesStack, BOOL);       
    }
#line 2131 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 883 "compilador.y" /* yacc.c:1646  */
    {geraCodigo(NULL, "CMIG");}
#line 2137 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 885 "compilador.y" /* yacc.c:1646  */
    {geraCodigo(NULL, "CMDG");}
#line 2143 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 887 "compilador.y" /* yacc.c:1646  */
    {geraCodigo(NULL, "CMME");}
#line 2149 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 889 "compilador.y" /* yacc.c:1646  */
    {geraCodigo(NULL, "CMEG");}
#line 2155 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 891 "compilador.y" /* yacc.c:1646  */
    {geraCodigo(NULL, "CMMA");}
#line 2161 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 893 "compilador.y" /* yacc.c:1646  */
    {geraCodigo(NULL, "CMAG");}
#line 2167 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 900 "compilador.y" /* yacc.c:1646  */
    {
        if (elementosExpressao.topo>=0)
            elementosExpressao.elementos[elementosExpressao.topo]+=2;
    }
#line 2176 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 905 "compilador.y" /* yacc.c:1646  */
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
#line 2194 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 919 "compilador.y" /* yacc.c:1646  */
    {
      // restore to 0 since we already dealed with it
      countTermo[nivelExpressao] = 0;
      // decreases level
      nivelExpressao--;
    }
#line 2205 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 931 "compilador.y" /* yacc.c:1646  */
    {
          // only increments if it was initialized with one
          // that means only expression levels with minus signals will be incremented
          countTermo[nivelExpressao]+= countTermo[nivelExpressao] > 0;
    }
#line 2215 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 939 "compilador.y" /* yacc.c:1646  */
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
#line 2232 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 952 "compilador.y" /* yacc.c:1646  */
    { 
        checaTipos();
        geraCodigo(NULL, "SOMA"); 
    }
#line 2241 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 957 "compilador.y" /* yacc.c:1646  */
    {
        checaTipos();
        geraCodigo(NULL, "SUBT");
    }
#line 2250 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 962 "compilador.y" /* yacc.c:1646  */
    {
        checaTipos();
        geraCodigo(NULL, "DISJ");
    }
#line 2259 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 973 "compilador.y" /* yacc.c:1646  */
    {
        checaTipos();
        geraCodigo(NULL, "MULT");
    }
#line 2268 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 978 "compilador.y" /* yacc.c:1646  */
    {
        checaTipos();
        geraCodigo(NULL, "DIVI");
    }
#line 2277 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 983 "compilador.y" /* yacc.c:1646  */
    { 
        checaTipos();
        geraCodigo(NULL, "CONJ");
    }
#line 2286 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 993 "compilador.y" /* yacc.c:1646  */
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
#line 2301 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1005 "compilador.y" /* yacc.c:1646  */
    {geraCodigo(NULL, "NEGA");}
#line 2307 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1008 "compilador.y" /* yacc.c:1646  */
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
#line 2322 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1019 "compilador.y" /* yacc.c:1646  */
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
#line 2337 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1033 "compilador.y" /* yacc.c:1646  */
    {
        if (elementosExpressao.topo>=0)
            elementosExpressao.elementos[elementosExpressao.topo]+=1;
        pilhaIdentificadorEsquerdaTopo++;
        strcpy(pilhaIdentificadorEsquerda[pilhaIdentificadorEsquerdaTopo], token);
    }
#line 2348 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1044 "compilador.y" /* yacc.c:1646  */
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
#line 2450 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1144 "compilador.y" /* yacc.c:1646  */
    {
        // count parameters
        insereElemento(&SeccontadorParametros, 0);
        // contadorParametros = 0;
        calledSubprogram=1;
        // elementosExpressao.elementos[elementosExpressao.topo]+=1;
         {geraCodigo(NULL, "AMEM 1");}
    }
#line 2463 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1155 "compilador.y" /* yacc.c:1646  */
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
#line 2514 "compilador.tab.c" /* yacc.c:1646  */
    break;


#line 2518 "compilador.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1204 "compilador.y" /* yacc.c:1906  */

// function to check if types match to make operation
void checaTipos()
{
    if (typesStack.topo && 
        typesStack.elementos[typesStack.topo] != typesStack.elementos[typesStack.topo-1] )
    {
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
    char* tipo = (char*)malloc(sizeof(char)*DEFAULT_STRING_LENGTH);
    if (n == INTEGER)
        sprintf(tipo, "INTEGER");
    else if (n == BOOL)
        sprintf(tipo, "BOOLEAN");
    else
        sprintf(tipo, "DESCONHECIDO");

    return tipo;
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
    inicializaPilha(&typesStack);
    inicializaPilha(&numeroParametros);
    inicializaPilha(&elementosExpressao);
    inicializaPilha(&SeccontadorParametros);
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
