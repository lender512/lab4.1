%{
#include "Enums.h"

%}

%option yylineno noyywrap c++
DIGITO [0-9]
%%


[" "]+
[+ -]?{DIGITO}+ return Categoria::numero;

"+" return Categoria::opSuma;
"-" return Categoria::opResta;
"*" return Categoria::opMull;
"(" return Categoria::parIzquierdo;
")" return Categoria::parDerecho;


\n   return Categoria::END;
\t

. return Categoria::ERROR;

%%