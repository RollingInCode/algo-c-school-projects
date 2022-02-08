#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int i=5;
    int j=0;
    printf("Before with values: %d and %d\n", i, j);
    printf("Before with memory addresses: %p and %p\n", &i, &j);
    swap(&i, &j);

    return 0;
}

void swap(int *p, int *q) {

    int temp;
    printf("After with values: %d and %d\n", *p, *q);
    printf("After with memory addresses: %p and %p\n", &p, &q);
    temp = *p;
    p = *q;
    q = temp;
    printf("After swap: %d and %d\n", *p, *q);
}
