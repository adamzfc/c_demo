#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

List_t all = 0;
// "constructors"
Exp_t Exp_Int_new (int n)
{
  Exp_Int p = malloc (sizeof (*p));
  p->kind = EXP_INT;
  p->n = n;
  return (Exp_t)p;
}

Exp_t Exp_Add_new (Exp_t left, Exp_t right)
{
  Exp_Add p = malloc (sizeof (*p));
  p->kind = EXP_ADD;
  p->left = left;
  p->right = right;
  return (Exp_t)p;
}

Exp_t Exp_Times_new (Exp_t left, Exp_t right)
{
  Exp_Add p = malloc (sizeof (*p));
  p->kind = EXP_TIMES;
  p->left = left;
  p->right = right;
  return (Exp_t)p;
}

Exp_t Exp_Sub_new (Exp_t left, Exp_t right)
{
  Exp_Sub p = malloc (sizeof (*p));
  p->kind = EXP_SUB;
  p->left = left;
  p->right = right;
  return (Exp_t)p;
}

Exp_t Exp_Divided_new (Exp_t left, Exp_t right)
{
  Exp_Divided p = malloc (sizeof (*p));
  p->kind = EXP_DIVIDED;
  p->left = left;
  p->right = right;
  return (Exp_t)p;
}

Exp_t Exp_Bracket_new (Exp_t exp)
{
  Exp_Bracket p = malloc (sizeof (*p));
  p->kind = EXP_BRACKET;
  p->exp = exp;
  return (Exp_t)p;
}
// all operations on "Exp"
void Exp_print (Exp_t exp)
{
  switch (exp->kind){
    case EXP_INT:{
		   Exp_Int p = (Exp_Int)exp;
		   printf ("%d", p->n);
		   return;
		 }
    case EXP_ADD:{
		   Exp_Add p = (Exp_Add)exp;
		   printf ("(");
		   Exp_print (p->left);
		   printf (") + (");
		   Exp_print (p->right);
		   printf (")");
		   return;
		 }
    case EXP_TIMES:{
		     Exp_Times p = (Exp_Times)exp;
		     printf ("(");
		     Exp_print (p->left);
		     printf (") * (");
		     Exp_print (p->right);
		     printf (")");
		     return;
		   }
    case EXP_SUB:{
		   Exp_Sub p = (Exp_Sub)exp;
		   printf ("(");
		   Exp_print (p->left);
		   printf (") - (");
		   Exp_print (p->right);
		   printf (")");
		   return;
		 }
    case EXP_DIVIDED:{
		       Exp_Divided p = (Exp_Divided)exp;
		       printf ("(");
		       Exp_print (p->left);
		       printf (") / (");
		       Exp_print (p->right);
		       printf (")");
		       return;
		     }
    case EXP_BRACKET:{
		       Exp_Bracket p = (Exp_Bracket)exp;
		       printf ("(");
		       Exp_print (p->exp);
		       printf (")");
		       return;
		     }

    default:
		     return;
  }
}

Stack_t Stack_Add_new()
{
  Stack_Add p = malloc(sizeof(*p));
  p->kind = STACK_ADD;
  return (Stack_t)p;
}

Stack_t Stack_Times_new()
{
  Stack_Times p = malloc(sizeof(*p));
  p->kind = STACK_TIMES;
  return (Stack_t)p;
}

Stack_t Stack_Sub_new()
{
  Stack_Sub p = malloc(sizeof(*p));
  p->kind = STACK_SUB;
  return (Stack_t)p;
}

Stack_t Stack_Divided_new()
{
  Stack_Divided p = malloc(sizeof(*p));
  p->kind = STACK_DIVIDED;
  return (Stack_t)p;
}

Stack_t Stack_Push_new (int i)
{
  Stack_Push p = malloc(sizeof(*p));
  p->kind = STACK_PUSH;
  p->i = i;
  return (Stack_t)p;
}


void List_reverse_print (List_t list)
{
  if(list == NULL)
  {
    return;
  }
  List_reverse_print(list->next);
  if(list->instr->kind == STACK_PUSH)
  {
    Stack_Push p = (Stack_Push)list->instr;
    printf("PUSH %d\n", p->i);
  }
  else if(list->instr->kind == STACK_ADD)
  {
    printf("ADD\n");
  }	
  else if(list->instr->kind == STACK_TIMES)
  {
    printf("TIMES\n");
  }
  else if(list->instr->kind == STACK_SUB)
  {
    printf("SUB\n");
  }
  else if(list->instr->kind == STACK_DIVIDED)
  {
    printf("DIVIDED\n");
  }
}


List_t List_new (Stack_t instr, List_t next)
{
  List_t p = malloc (sizeof (p));
  p->instr = instr;
  p->next = next;
  return p;
}

void emit (Stack_t instr)
{
  all = List_new (instr, all);
}

void compile (Exp_t exp)
{
  switch (exp->kind){
    case EXP_INT:{
		   Exp_Int p = (Exp_Int)exp;
		   emit (Stack_Push_new (p->n));
		   break;
		 }
    case EXP_ADD:{
		   Exp_Add p = (Exp_Add)exp;
		   compile(p->left);
		   compile(p->right);
		   emit(Stack_Add_new ());
		   break;
		 }
    case EXP_TIMES:{
		   Exp_Times p  = (Exp_Times)exp;
		   compile(p->left);
		   compile(p->right);
		   emit(Stack_Times_new ());
		   break;
		   }
    
    case EXP_SUB:{
		   Exp_Sub p  = (Exp_Sub)exp;
		   compile(p->left);
		   compile(p->right);
		   emit(Stack_Sub_new ());
		   break;
		 }
    
    case EXP_DIVIDED:{
		   Exp_Divided p  = (Exp_Divided)exp;
		   compile(p->left);
		   compile(p->right);
		   emit(Stack_Divided_new ());
		   break;
		 }

    default:
		 break;
  }
}




