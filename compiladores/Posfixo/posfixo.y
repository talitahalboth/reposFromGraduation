
%{
#include <stdio.h>
%}

%token IDENT BOOL MAIS MENOS OR AND ASTERISCO DIV ABRE_PARENTESES FECHA_PARENTESES

%%

choice     : expr | 
			 exprBool
;

expr       : expr MAIS termo {printf ("+"); } |
             expr MENOS termo {printf ("-"); } | 
             termo
;

exprBool   : exprBool OR termoBool { printf (" or "); } |
             termoBool
;


termo      : termo ASTERISCO fator  {printf ("*"); }| 
             termo DIV fator  {printf ("/"); }|
             fator
;

termoBool : termoBool AND fator { printf (" and "); }|
		    fator
;


fator      : IDENT {printf ("A"); }|
			 BOOL  {printf ("B"); }
;


%%

int main (int argc, char** argv) {
   yyparse();
   printf("\n");
}

