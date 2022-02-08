#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int i=10;
    int* p, q;
    q = &i;
    p = &q;

    printf("%d", &p);

    return 0;
}
