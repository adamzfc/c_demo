#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semant.h"

#define TODO()\
    do{\
        printf ("TODO: add your code at file: \"%s\", line: %d\n", __FILE__, __LINE__);\
    }while(0)

//////////////////////////////////////
// the symbol table
List_t table = 0;

// lookup an "id" in the symbol table.
// return "type" on success; and -1 for failure
Type_t Table_lookup (char *id)
{
    List_t p = table;
    while (p){
        Dec_t d = (Dec_t)p->data;
        if (strcmp(d->id, id)==0)
            return d->type;
        p = p->next;
    }
    return -1;
}

void Table_insert (Dec_t dec)
{

    if (Table_lookup (dec->id) != -1){
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
    while (decs){
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
    /* TODO(); */
    switch(exp->kind) {
        case EXP_INT:
            return TYPE_INT;
        case EXP_TRUE:
            return TYPE_BOOL;
        case EXP_FALSE:
            return TYPE_BOOL;
        case EXP_ADD:
            {
                Exp_Add exp_add = (Exp_Add) exp;
                Type_t t1 = check_exp(exp_add->left);
                Type_t t2 = check_exp(exp_add->right);
                if (t1 != TYPE_INT || t2 != TYPE_INT) {
                    fprintf (stderr, "type mismatch");
                    exit (0);
                } else {
                    return TYPE_INT;
                }
            }
        case EXP_SUB:
            {
                Exp_Sub exp_sub = (Exp_Sub) exp;
                Type_t t1 = check_exp(exp_sub->left);
                Type_t t2 = check_exp(exp_sub->right);
                if (t1 != TYPE_INT || t2 != TYPE_INT) {
                    fprintf (stderr, "type mismatch");
                    exit (0);
                } else {
                    return TYPE_INT;
                }
            }
        case EXP_TIMES:
            {
                Exp_Times exp_times = (Exp_Times) exp;
                Type_t t1 = check_exp(exp_times->left);
                Type_t t2 = check_exp(exp_times->right);
                if (t1 != TYPE_INT || t2 != TYPE_INT) {
                    fprintf (stderr, "type mismatch");
                    exit (0);
                } else {
                    return TYPE_INT;
                }
            }
        case EXP_DIVIDE:
            {
                Exp_Divide exp_divide = (Exp_Divide) exp;
                Type_t t1 = check_exp(exp_divide->left);
                Type_t t2 = check_exp(exp_divide->right);
                if (t1 != TYPE_INT || t2 != TYPE_INT) {
                    fprintf (stderr, "type mismatch");
                    exit (0);
                } else {
                    return TYPE_INT;
                }
            }
        case EXP_AND:
            {
                Exp_And exp_and = (Exp_And) exp;
                Type_t t1 = check_exp(exp_and->left);
                Type_t t2 = check_exp(exp_and->right);
                if (t1 != TYPE_BOOL || t2 != TYPE_BOOL) {
                    fprintf (stderr, "type mismatch");
                    exit (0);
                } else {
                    return TYPE_BOOL;
                }
            }
        case EXP_OR:
            {
                Exp_Or exp_or = (Exp_Or) exp;
                Type_t t1 = check_exp(exp_or->left);
                Type_t t2 = check_exp(exp_or->right);
                if (t1 != TYPE_BOOL || t2 != TYPE_BOOL) {
                    fprintf (stderr, "type mismatch");
                    exit (0);
                } else {
                    return TYPE_BOOL;
                }
            }
        case EXP_ID:
            {
                Exp_Id exp_id = (Exp_Id) exp;
                Type_t t = Table_lookup(exp_id->id);
                if (t == -1) {
                    fprintf (stderr, "id not found");
                    exit (0);
                } else {
                    return t;
                }
            }
    }
}

////////////////////////////////////////
// stm

// Your job:
void check_stm (Stm_t stm)
{
    /* TODO(); */
    switch (stm->kind){
        case STM_ASSIGN:
            {
                Stm_Assign stm_assign = (Stm_Assign) stm;
                Type_t t1 = Table_lookup(stm_assign->id);
                Type_t t2 = check_exp(stm_assign->exp);
                if (t1 != t2) {
                    fprintf (stderr, "type mismatch");
                    exit (0);
                }else{
                    return;
                }
            }
        case STM_PRINTI:
            {
                Stm_Printi stm_printi = (Stm_Printi) stm;
                Type_t t = check_exp(stm_printi->exp);
                if (t != TYPE_INT) {
                    fprintf (stderr, "type mismatch");
                    exit (0);
                } else {
                    return;
                }
            }
        case STM_PRINTB:
            {
                Stm_Printb stm_printb = (Stm_Printb) stm;
                Type_t t = check_exp(stm_printb->exp);
                if (t != TYPE_BOOL) {
                    fprintf (stderr, "type mismatch");
                    exit (0);
                } else {
                    return;
                }
            }
    }
}

void check_stms(List_t stms)
{
    while (stms){
        Stm_t s = (Stm_t)stms->data;
        check_stm(s);
        stms = stms->next;
    }
    return;
    /* TODO(); */
}


void Semant_check(Prog_t prog)
{
    // create table
    check_decs(prog->decs);
    // check stm
    check_stms(prog->stms);
    return;
}
