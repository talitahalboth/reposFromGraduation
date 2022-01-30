
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

termoBool : termoBool AND fatorBool { printf (" and "); }|
		    fatorBool
;


fator      : IDENT {printf ("A"); }
;


fatorBool   : BOOL  {printf ("B"); }
;

%%

int main (int argc, char** argv) {
   yyparse();
   printf("\n");
}

