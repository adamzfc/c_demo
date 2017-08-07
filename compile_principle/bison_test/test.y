%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
 
int yylex();
void yyerror(const char *s);
%}
 
%token DIGIT
 
%left '+' '-'
%left '*' '/'
 
%%
 
lines   :   lines line
    |   line
    ;
 
line    :   expr '\n'  { printf("%d\n", $1); }
    ;
 
expr    :   number      { $$ = $1; }
    |   expr '+' expr { $$ = $1 + $3; }
    |  expr '-' expr { $$ = $1 - $3; }
    |   expr '*' expr { $$ = $1 * $3; }
    |   expr '/' expr { $$ = $1 / $3; }
    |  '(' expr ')'  { $$ = $2; }
    ;
 
number  :   number DIGIT   { $$ = $1 * 10 + $2; }
    |   DIGIT       { $$ = $1; }
    ;
 
%%
 
int yylex() {
    int c = getchar();
    if(isdigit(c)) {
        yylval = c - '0';
        return DIGIT;
    }
 
    return c;
}
 
void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}
 
int main(int argc, char **argv) {
    yyparse();
    return 0;
}
