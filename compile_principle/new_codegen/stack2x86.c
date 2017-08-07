#include <stdio.h>
#include <stdlib.h>
#include "stack2x86.h"

FILE *fp = 0;

static void genx86_64_ids (List_t ids)
{
    fputs("#--------------------Variables--------------------#\n", fp);
    fputs(".data\n", fp);
    while (ids)
    {
        char *id = (char *)ids->data;
        fprintf (fp, "\t%s:\t\t.int 0\n", id);
        ids = ids->next;
    }
    fputs("\n\n\n\n\n\n\n\n", fp);
    return;
}

static void genx86_64_instrs(List_t l) {
    while(l != NULL) {
        switch(((Stack_Instr_t) l-> data)->kind) {
        case STACK_INSTR_PUSH:
            fprintf(fp, "#push %d:\n\tmovl\t$%d, %%eax\n%s\n\n",
            ((Stack_Instr_Push) l->data)->n,
            ((Stack_Instr_Push) l->data)->n,
            "\tmovl\t%eax, (%rbx)\n"
            "\taddq\t$4, %rbx\n");
            break;

        case STACK_INSTR_LOAD:
            fprintf(fp, "#load %s:\n\tmovl\t%s, %%eax\n%s\n\n",
            ((Stack_Instr_Load) l->data)->x,
            ((Stack_Instr_Load) l->data)->x,
            "\tmovl\t%eax, (%rbx)\n\taddq\t$4, %rbx\n");
            break;

        case STACK_INSTR_STORE:
            fprintf(fp,
            "#store %s:\n"
            "\tsubq\t$4, %%rbx\n"
            "\tmovl\t(%%rbx), %%eax\n"
            "\tmovl\t%%eax, %s\n\n\n",
            ((Stack_Instr_Store) l->data)->x, ((Stack_Instr_Store) l->data)->x);
            break;

        case STACK_INSTR_ADD:
            fprintf(fp, "%s\n\n",
            "#add:\n"
            "\tsubq\t$4, %rbx\n"
            "\tmovl\t(%rbx), %ecx\n"
            "\tmovl\t-4(%rbx), %eax\n"
            "\taddl\t%ecx, %eax\n"
            "\tmovl\t%eax, -4(%rbx)\n");
            break;

        case STACK_INSTR_SUB:
            fprintf(fp, "%s\n\n",
            "#sub:\n"
            "\tsubq\t$4, %rbx\n"
            "\tmovl\t(%rbx), %ecx\n"
            "\tmovl\t-4(%rbx), %eax\n"
            "\tsubl\t%ecx, %eax\n"
            "\tmovl\t%eax, -4(%rbx)\n");
            break;

        case STACK_INSTR_TIMES:
            fprintf(fp, "%s\n\n",
            "#times:\n"
            "\tsubq\t$4, %rbx\n"
            "\tmovl\t(%rbx), %ecx\n"
            "\tmovl\t-4(%rbx), %eax\n"
            "\tmull\t%ecx\n"
            "\tmovl\t%eax, -4(%rbx)\n");
            break;

        case STACK_INSTR_DIV:
            fprintf(fp, "%s\n\n",
            "#div:\n"
            "\tmovl\t$0, %edx\n"
            "\tsubq\t$4, %rbx\n"
            "\tmovl\t(%rbx), %ecx\n"
            "\tmovl\t-4(%rbx), %eax\n"
            "\tdivl\t%ecx\n"
            "\tmovl\t%eax, -4(%rbx)\n");
            break;

        case STACK_INSTR_AND:
            fprintf(fp, "%s\n\n",
            "#and:\n"
            "\tsubq\t$4, %rbx\n"
            "\tmovl\t(%rbx), %ecx\n"
            "\tmovl\t-4(%rbx), %eax\n"
            "\tandl\t%ecx, %eax\n"
            "\tmovl\t%eax, -4(%rbx)\n");
            break;

        case STACK_INSTR_OR:
            fprintf(fp, "%s\n\n",
            "#or:\n"
            "\tsubq\t$4, %rbx\n"
            "\tmovl\t(%rbx), %ecx\n"
            "\tmovl\t-4(%rbx), %eax\n"
            "\torl\t%ecx, %eax\n"
            "\tmovl\t%eax, -4(%rbx)\n");
            break;

        case STACK_INSTR_PRINTI:
            fprintf(fp, "%s\n\n",
            "#printi:\n"
            "\tcallq\tprinti\n");
            break;

        case STACK_INSTR_PRINTB:
            fprintf(fp, "%s\n\n",
            "#printb:\n"
            "\tcallq\tprintb\n");
            break;

        }

        l = l->next;
    }
}

void Stack2x86_64_print (Stack_Prog_t p) {
#if !defined(_M_X64) && !defined(__x86_64__) && !defined(__amd64)
    fprintf(stderr, "%s\n", "This program can only generate codes for x86-64 linux system.");
    return;
#endif

    fp = fopen("temp.s", "w+");
    if(fp == NULL) {
        fprintf(stderr, "%s\n", "Cannot open or create the file \"temp.s\"");
        return;
    }

    //Generate variables here.
    genx86_64_ids(p->ids);

    //Generate common data here
    fputs(
    "#--------------------stack and strings--------------------#\n"
    ".section .data\n"
    "\t.comm space, 8192, 32\n"
    "\tstr_i: .string \"%d\\n\"\n"
    "\tstr_true: .string \"true\"\n"
    "\tstr_false: .string \"false\"\n"
    "\n\n\n\n\n\n\n\n",
    fp);

    fprintf(fp, "%s\n", "#--------------------codes--------------------#\n"
    ".text");

    //Generate "printi" here
    fputs(
    ".globl printi\n"
    "printi:\n"
    "\tsubq\t$4, %rbx\n"
    "\tmovl\t(%rbx), %esi\n"
    "\tmovq\t$str_i, %rdi\n"
    "\txorq\t%rax, %rax\n"
    "\tcallq\tprintf\n"
    "\tret\n"
    "\n\n\n\n",
    fp);

    //Generate "printb" here
    fputs(
    ".globl printb\n"
    "printb:\n"
    "\tmovq\t$str_true, %rdi\n"
    "\tsubq\t$4, %rbx\n"
    "\tmovl\t(%rbx), %eax\n"
    "\tcmpl\t$0, %eax\n"
    "\tjne\t.puts_on\n"
    "\tmovq\t$str_false, %rdi\n"
    ".puts_on:\n"
    "\txorq\t%rax, %rax\n"
    "\tcallq\tputs\n"
    "\tret\n"
    "\n\n\n\n",
    fp);

    //Genetate "main" here
    fputs(
    ".globl main\n"
    "main:\n"
    "\tmovq\t$space, %rbx\n\n\n",
    fp);

    //Generate the instructions
    genx86_64_instrs(p->instrs);

    fprintf(fp, "%s\n",
    "#exit:\n"
    "\txorq\t%rax, %rax\n"
    "\tcallq\texit\n");

    fclose(fp);
}
