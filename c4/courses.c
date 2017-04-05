#include <stdio.h>
#include <string.h>

// 此处 courses 数据不要做任何改动
// courses 变量名不许修改
char *courses[] = {"C","C++","PHP","ASP","ASP.NET","C#","JAVA","BASIC","PASCAL","COBOL"};

void sort(char *p[], int n) {
    char *tmp;
    int i, j, k;
    for (i = 0; i < n; ++ i) {
        k = i;
        for (j = i+1; j < n; ++ j) {
            if (strcmp(p[k], p[j]) > 0
               // TODO:
                ) {
                k = j;
            }
        }
        if (k != j) {
            tmp = p[k];
            p[k] = p[i];
            p[i] = tmp;
        }
    }
}

int main() {
    int n = sizeof(courses) / sizeof(courses[0]);
    sort(courses, n);
    int i;
    for (i = 0; i < n; ++ i) {
        printf("%s\n", courses[i]);
    }
    return 0;
}
