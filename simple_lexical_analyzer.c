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

struct token *Token_new(enum kind kind, char* temp, int len, int row, int column) {
    struct token *t = malloc(sizeof(*t));
    t->kind = kind;
    if (len > 0) {
        t->lexeme = malloc(sizeof(char)*(len));
        memcpy(t->lexeme, temp, len);
    } else {
        t->lexeme = NULL;
    }
    t->row = row;
    t->column = column - len;
    return t;
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
    c = fgetc(pFile);
    return c;
}

/*
 * define S1 = [a-hj-zA-Z_]
 *        S2 = [a-zA-Z0-9_]
 *        S3 = [a-eg-zA-Z0-9_]
 *        S_other = [ \n]
 *        S_num = [0-9]
 */
bool isS1(char c) {
    if ((c >= 'a' && c <= 'h')
            || (c >= 'j' && c <= 'z')
            || (c >= 'A' && c <= 'Z')
            || c == '_') {
        return true;
    } else {
        return false;
    }
}

bool isS2(char c) {
    if ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z')
            || (c >= '0' && c <= '9')
            || c == '_') {
        return true;
    } else {
        return false;
    }
}

bool isS3(char c) {
    if ((c >= 'a' && c <= 'e')
            || (c >= 'g' && c <= 'z')
            || (c >= 'A' && c <= 'Z')
            || (c >= '0' && c <= '9')
            || c == '_') {
        return true;
    } else {
        return false;
    }
}

bool isSother(char c) {
    if (c == ' ' || c == '\n') {
        return true;
    } else {
        return false;
    }
}

bool isSnum(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    } else {
        return false;
    }
}


int main() {
    int row = 1;
    int column = 1;
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
        if (c == ' ') {
            column ++;
            continue;
        }
        if (c == '\n') {
            column = 1;
            row ++;
            continue;
        }
        temp[len++] = c;
        column ++;
        if (isS1(c)) {
            fgetpos(pFile, &position);
            column ++;
            while ((c = getChar()) != EOF) {
                if (isSother(c)) {
                    rollback();
                    addToList(Token_new(ID, temp, len, row, column));
                    len = 0;
                    break;
                }
                temp[len++] = c;
                fgetpos(pFile, &position);
                column ++;
            }
        } else if (c == 'i') {
            fgetpos(pFile, &position);
            c = getChar();
            if (c == 'f') {
                fgetpos(pFile, &position);
                temp[len++] = c;
                column ++;
                c = getChar();
                if (isSother(c)) {
                    rollback();
                    addToList(Token_new(IF, temp, len, row, column));
                    len = 0;
                } else {
                    temp[len++] = c;
                    fgetpos(pFile, &position);
                    column ++;
                    while ((c = getChar()) != EOF) {
                        if (isSother(c)) {
                            rollback();
                            addToList(Token_new(ID, temp, len, row, column));
                            len = 0;
                            break;
                        }
                        temp[len++] = c;
                        fgetpos(pFile, &position);
                        column ++;
                    }
                }
            } else if (isSother(c)) {
                rollback();
                addToList(Token_new(ID, temp, len, row, column));
                len = 0;
            } else {
                temp[len++] = c;
                fgetpos(pFile, &position);
                column ++;
                while ((c = getChar()) != EOF) {
                    if (isSother(c)) {
                        rollback();
                        addToList(Token_new(ID, temp, len, row, column));
                        len = 0;
                        break;
                    }
                    temp[len++] = c;
                    fgetpos(pFile, &position);
                    column ++;
                }
            }
        } else if (isSnum(c)) {
            fgetpos(pFile, &position);
            while ((c = getChar()) != EOF) {
                if (isSother(c)) {
                    rollback();
                    addToList(Token_new(NUM, temp, len, row, column));
                    len = 0;
                    break;
                }
                temp[len++] = c;
                fgetpos(pFile, &position);
                column ++;
            }
        }
    }
    List_reverse_print(head);
    return 0;
}

