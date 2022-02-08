#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int a[10], *p;
    p = &a[0];

    *p = 5;

    printf("%d", *p);

    return 0;



}
