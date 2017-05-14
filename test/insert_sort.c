#include <stdio.h>

void sort(int* list, int size) {
    int i, j;
    if (size <= 1) {
        return;
    }
    for (j = 1; j < size; j ++) {
        i = j - 1;
        int key = list[j];
        while (i >= 0 && list[i] > key) {
            list[i+1] = list[i];
            i = i - 1;
        }
        list[i+1] = key;
    }
}

int main() {
    int size = 9;
    int list[] = {1, 3, 2, 5, 4, -1, 6, 22, 7};
    int i;
    sort(list, size);
    for (i = 0; i < size; i++)
        printf("%d ", list[i]);
    return 0;
}
