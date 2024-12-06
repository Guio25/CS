
%{
#include "y.tab.h"
#include <stdlib.h>
#include "funzioni.h"
%}

%%

[0-9]+  {yylval.ivalue = atoi(yytext);
         return INTEGER;
        }

[\t\n] ;

";" {return END;}

[+-/*] {return *yytext;}



%%


int yywrap (void) {

	return 1;
}




