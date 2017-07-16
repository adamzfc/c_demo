#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int bool;
enum { false, true };
enum kind { IF, NUM, ID};
struct token {
    enum kind kind;
    char *lexeme;
    int row;
    int column;
};

struct List_token
{
  struct token *t;
  struct List_token *next;
};

FILE *pFile = NULL;
fpos_t position;
struct List_token *head = NULL;

struct List_token *List_new (struct token *t, struct List_token *next)
{
  struct List_token *p = malloc (sizeof (*p));
  p->t = t;
  p->next = next;
  return p;
}

void List_reverse_print (struct List_token *list)
{
    struct List_token *prev = 0;
    struct List_token *next;
    while (list != 0) {
        next = list->next;
        list->next = prev;
        prev = list;
        list = next;
    }
    list = prev;
    printf("\n");
    while(0 != list) {
        switch (list->t->kind){
        case ID:{
        //struct STACK_ADD *p = (struct STACK_ADD *)list->instr;
        printf ("ID(%s)(%d,%d)\n", list->t->lexeme, list->t->row, list->t->column);
        break;
        }
        case IF:{
        printf ("IF\t(%d,%d)\n", list->t->row, list->t->column);
        break;
        }
        case NUM:{
        printf("NUM(%s)(%d,%d)\n", list->t->lexeme, list->t->row, list->t->column);
        break;
        }
        default:
        break;
        }
        list = list->next;
    }
}

void addToList (struct token *t)
{
  head = List_new (t, head);
}

void rollback() {
    if (!pFile) {
        perror("FILE do not be NULL");
        return;
    }
    fsetpos(pFile, &position);
}

char getChar() {
    char c;
    fread(&c, sizeof(char), 1, pFile);
    return c;
}



int main() {
    int row = 1;
    int column = 0;
    int len = 0;
    char temp[32];
    bool isNumber = false;
    bool isBlank = true;
    pFile = fopen("./lexical_test.txt", "r");
    if (!pFile) {
        perror("Error opening file");
        return 1;
    }
    char c;
    while ((c = getChar()) != EOF) {
        if (c != ' ')
            isBlank = false;
        column ++;
        temp[len++] = c;
        fgetpos(pFile, &position);
        switch (c) {
            case 'i':
                c = getChar();
                if (c == 'f') {
                    c = getChar();
                    if (c == ' ') {
                        struct token *t = malloc(sizeof(*t));
                        t->kind = IF;
                        t->lexeme = NULL;
                        t->row = row;
                        t->column = column;
                        column += 2;
                        len = 0;
                        addToList(t);
                        isBlank = true;
                    } else {
                        rollback();
                    }
                } else {
                    rollback();
                }
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                isNumber = true;
                break;
            case '\n':
                row ++;
                column = 0;
            case ' ':
                if (isNumber) {
                    struct token *t = malloc(sizeof(*t));
                    t->kind = NUM;
                    t->lexeme = malloc(sizeof(char)*(len-1));
                    memcpy(t->lexeme, temp, len-1);
                    t->row = row;
                    t->column = column;
                    addToList(t);
                    len = 0;
                    isNumber = false;
                }
                if (!isBlank) {
                    struct token *t = malloc(sizeof(*t));
                    t->kind = ID;
                    t->lexeme = malloc(sizeof(char)*(len-1));
                    memcpy(t->lexeme, temp, len-1);
                    t->row = row;
                    t->column = column;
                    len = 0;
                    addToList(t);
                }
                isBlank = true;
                break;
            default:
                break;
        }
    }
    List_reverse_print(head);

    return 0;
}

