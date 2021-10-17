%{
#include "Enums.h"
%}

%option noyywrap c++

%%
"a" return Categoria::A;
"b" return Categoria::B;

\n  return Categoria::END;
\t
.   return Categoria::ERROR;

%%
