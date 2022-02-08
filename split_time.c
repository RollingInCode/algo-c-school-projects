#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int tuna = 19;

    printf("Address \t\t Name \t Value \n");


    int * pTuna = &tuna;
    printf("%p\t %s \t %d \n", pTuna, "tuna", tuna);
    printf("%p\t %s \t %p \n", &pTuna, "pTuna", pTuna);

    printf("\n*pTuna: %d \n", *pTuna);

    *pTuna = 71;

    printf("\n*pTuna: %d \n", *pTuna);



    return 0;

}
