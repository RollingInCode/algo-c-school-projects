#include <stdio.h>
#include <stdlib.h>

void my_malloc();

int main(void) {
    int *p;
    printf("%d\n", p);
    my_malloc(&p);



    return 0;


}

void my_malloc(int *p) {
    int q = 16;
    p = malloc(sizeof(int));
    printf("%d\n", p);
    p =  q;
    printf("%d", p);

}
