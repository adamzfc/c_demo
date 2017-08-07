#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semant.h"
#include "todo.h"

//////////////////////////////////////
// the symbol table
List_t table = 0;

// lookup an "id" in the symbol table.
// return "type" on success; and -1 for failure
Type_t Table_lookup (char *id)
{
    List_t p = table;
    while (p)
    {
        Dec_t d = (Dec_t)p->data;
        if (strcmp(d->id, id)==0)
            return d->type;
        p = p->next;
    }
    return -1;
}

void Table_insert (Dec_t dec)
{

    if (Table_lookup (dec->id) != -1)
    {
        fprintf (stderr, "Error: the variable "
                 "\"%s\" has been declared!\n", dec->id);
        exit (0);
    }
    table = List_new (dec, table);
    return;
}

//////////////////////////////////////////
// dec
void check_dec(Dec_t d)
{
    Table_insert (d);
}

void check_decs(List_t decs)
{
    while (decs)
    {
        Dec_t d = (Dec_t)decs->data;
        check_dec(d);
        decs = decs->next;
    }
    return;
}

////////////////////////////////////////
// exp

// Your job:
Type_t check_exp (Exp_t exp)
{
    //TODO();
    Type_t l, r;
    switch(exp->kind) {
    case EXP_INT:
        return TYPE_INT;

    case EXP_TRUE:
    case EXP_FALSE:
        return TYPE_BOOL;

    case EXP_ID:
        l = Table_lookup(((Exp_Id) exp)->id);
        if((int) l == -1) {
            fprintf(stderr, "Error: The variable \"%s\" is not defined yet.\n", ((Exp_Id) exp)->id);
            exit(0);
        }

        return l;

    case EXP_ADD:
    case EXP_SUB:
    case EXP_TIMES:
    case EXP_DIVIDE:
        l = check_exp(((Exp_Add) exp)->left);
        if(l != TYPE_INT) {
            fprintf(stderr, "%s\n", "Error: The operant(s) of \"+\", \"-\", \"*\", \"/\" is not of type integer.");
            exit(0);
        }

        r = check_exp(((Exp_Add) exp)->right);
        if(r != TYPE_INT) {
            fprintf(stderr, "%s\n", "Error: The operant(s) of \"+\", \"-\", \"*\", \"/\" is not of type integer.");
            exit(0);
        }

        return TYPE_INT;

    case EXP_AND:
    case EXP_OR:
        l = check_exp(((Exp_And) exp)->left);
        if(l != TYPE_BOOL) {
            fprintf(stderr, "%s\n", "Error: The operant(s) of \"and\", or\" is not of type bool.");
            exit(0);
        }

        r = check_exp(((Exp_And) exp)->right);
        if(r != TYPE_BOOL) {
            fprintf(stderr, "%s\n", "Error: The operant(s) of \"and\", or\" is not of type bool.");
            exit(0);
        }

        return TYPE_BOOL;

    default:
        fprintf(stderr, "%s\n", "Error: Unknown expression.");
        exit(0);
    }

    return TYPE_INT; //To supress the warnings the compiler generates.
}

////////////////////////////////////////
// stm

// Your job:
void check_stm (Stm_t stm)
{
    //TODO();
    Type_t l, r;
    switch(stm->kind)
    {
    case STM_ASSIGN:
        l = Table_lookup(((Stm_Assign) stm)->id);
        if((int) l == -1) {
            fprintf(stderr, "Error: The variable \"%s\" is not defined yet.\n", ((Stm_Assign) stm)->id);
            exit(0);
        }

        r = check_exp(((Stm_Assign) stm)->exp);
        if(l != r) {
            fprintf(stderr, "%s\n", "Error: The types of the l-value and r-value of one assignment statement is different.");
            exit(0);
        }

        break;

    case STM_PRINTI:
        l = check_exp(((Stm_Printi) stm)->exp);
        if(l != TYPE_INT) {
            fprintf(stderr, "%s\n", "Error: The type of the expression inside the function \"printi\" must be integer.");
            exit(0);
        }

        break;

    case STM_PRINTB:
    l = check_exp(((Stm_Printi) stm)->exp);
        if(l != TYPE_BOOL) {
            fprintf(stderr, "%s\n", "Error: The type of the expression inside the function \"printb\" must be boolean.");
            exit(0);
        }

        break;

    default:
        fprintf(stderr, "%s\n", "Error: Unknown type of statement.");
        exit(0);
    }
}

void check_stms(List_t stms)
{
    while (stms)
    {
        Stm_t s = (Stm_t)stms->data;
        check_stm(s);
        stms = stms->next;
    }
    return;
    TODO();
}


void Semant_check(Prog_t prog)
{
    // create table
    check_decs(prog->decs);
    // check stm
    check_stms(prog->stms);
    return;
}
