#ifndef AST_H
#define AST_H

enum Exp_Kind_t{
  EXP_INT,
  EXP_ADD,
  EXP_TIMES,
  EXP_SUB,
  EXP_DIVIDED,
  EXP_BRACKET};



/*
   E -> n
      | E + E
      | E * E
*/
typedef struct Exp_t *Exp_t;
struct Exp_t{
  enum Exp_Kind_t kind;
};

// all operations on "Exp"
void Exp_print (Exp_t exp);
int Exp_numStacks (Exp_t exp);

typedef struct Exp_Int *Exp_Int;
struct Exp_Int{
  enum Exp_Kind_t kind;
  int n;
};
Exp_t Exp_Int_new (int n);

typedef struct Exp_Add *Exp_Add;
struct Exp_Add{
  enum Exp_Kind_t kind;
  Exp_t left;
  Exp_t right;
};
Exp_t Exp_Add_new (Exp_t left, Exp_t right);

typedef struct Exp_Times *Exp_Times;
struct Exp_Times{
  enum Exp_Kind_t kind;
  Exp_t left;
  Exp_t right;
};
Exp_t Exp_Times_new (Exp_t left, Exp_t right);

typedef struct Exp_Sub *Exp_Sub;
struct Exp_Sub{
  enum Exp_Kind_t kind;
  Exp_t left;
  Exp_t right;
};
Exp_t Exp_Sub_new (Exp_t left, Exp_t right);

typedef struct Exp_Divided *Exp_Divided;
struct Exp_Divided{
  enum Exp_Kind_t kind;
  Exp_t left;
  Exp_t right;
};
Exp_t Exp_Divided_new (Exp_t left, Exp_t right);

typedef struct Exp_Bracket *Exp_Bracket;
struct Exp_Bracket{
  enum Exp_Kind_t kind;
  Exp_t exp;
};
Exp_t Exp_Bracket_new (Exp_t exp);

//树上结点类型
enum Stack_Kind_t
{
  STACK_ADD,
  STACK_TIMES,
  STACK_SUB,
  STACK_DIVIDED,
  STACK_PUSH
};

typedef struct Stack_t *Stack_t;
struct Stack_t
{
  enum Stack_Kind_t kind;
};

typedef struct Stack_Add *Stack_Add;
struct Stack_Add
{
  enum Stack_Kind_t kind;
};

typedef struct Stack_Times *Stack_Times;
struct Stack_Times
{
  enum Stack_Kind_t kind;
};

typedef struct Stack_Sub *Stack_Sub;
struct Stack_Sub
{
  enum Stack_Kind_t kind;
};

typedef struct Stack_Divided *Stack_Divided;
struct Stack_Divided
{
  enum Stack_Kind_t kind;
};

typedef struct Stack_Push *Stack_Push;
struct Stack_Push
{
  enum Stack_Kind_t kind;
  int i;
};

Stack_t Stack_Add_new();

Stack_t Stack_Times_new();

Stack_t Stack_Sub_new();

Stack_t Stack_Divided_new();

Stack_t Stack_Push_new(int i);

typedef struct List_t *List_t;
struct List_t
{
  Stack_t instr;
  List_t next;
};


List_t List_new(Stack_t instr, List_t next);

void List_reverse_print(List_t list);

void emit (Stack_t instr);

void compile (Exp_t exp);

#endif
