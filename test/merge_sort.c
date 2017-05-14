#include <stdio.h>
#include <stdlib.h>

void merge_array(int a[], int first, int mid, int last, int temp[]) {
    int i = first, j = mid + 1;
    int m = mid, n = last;
    int k = 0;

    while(i <= m && j <= n) {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= m)
        temp[k++] = a[i++];

    while(j <= n)
        temp[k++] = a[j++];

    for(i = 0; i < k; i ++)
        a[first+i] = temp[i];
}

void merge(int a[], int first, int last, int temp[])
{
    if (first < last) {
        int mid = (first + last) / 2;
        merge(a, first, mid, temp);
        merge(a, mid + 1, last, temp);
        merge_array(a, first, mid, last, temp);
    }
}

void merge_sort(int a[], int n) {
    int *p = (int*) malloc(n*sizeof(int));
    if (p == NULL)
        return;
    merge(a, 0, n-1, p);
    free(p);

}
int main() {
    int size = 9;
    int list[] = {1, 3, 2, 5, 4, -1, 6, 22, 7};
    int i;
    merge_sort(list, size);
    for (i = 0; i < size; i++)
        printf("%d ", list[i]);
    return 0;
}
