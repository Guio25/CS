
%{
#include <stdlib.h>	
#include <stdio.h>
#include "funzioni.h"

nodeType *opr (nodeType *left, nodeType *right, char *token);
nodeType *id (int i);
void printTree(nodeType *tree);
void yyerror(char *s);
int yylex(void);

%}

%union {
	
 int ivalue; 
 struct nodeTypetag *nodePointer;

};

%token <ivalue> INTEGER 
%token END

%left '+' '-'
%left '*' '/'

%type <nodePointer> expr 


%%

lines : 
        | lines line

;

line : expr END {printTree($1); printf("\n"); }         

;


expr : INTEGER              {$$ = id($1);}
    | '-' expr  %prec '*'   {$$ = opr(NULL,$2,"-");}
    | expr expr '+'          {$$ = opr($1,$2,"+");}
    | expr expr '*'          {$$ = opr($1,$2,"*");}
    | expr expr '/'          {$$ = opr($1,$2,"/");}
    | expr expr '-'          {$$ = opr($1,$2,"-");}
  
  ;


%%

nodeType *opr(nodeType *left, nodeType *right, char *token) {
   
        nodeType *p = malloc(sizeof(nodeType));
        p->type = typeOpr;
        p->opr.left = left;
        p->opr.right = right;
        p->opr.token = token;

        return p;
}


nodeType *id(int i){
   
    nodeType *p = malloc(sizeof(nodeType));
    p->type = typeId;
    p->con.i = i;

    return p;
}


void printTree(nodeType *tree){
   

if (tree->type == typeId) {
   
   printf("%d ",tree->con.i);

}

printTree(tree->opr.left);

printTree(tree->opr.right);

printf("%s ",tree->opr.token);

}
 

int main(void){
   
   return yyparse();
}


void yyerror(char *s) {
   
   fprintf(stdout, "%s\n", s);
}
