#include <stdio.h>
#include "ast.h"


extern Exp_t tree;
extern List_t all;
void yyparse ();

int main (int argc, char **argv)
{
  yyparse();
  Exp_print (tree);
  printf("\n");
  compile(tree);
  List_reverse_print(all);
  return 0;
}
