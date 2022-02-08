#include <stdio.h>
#include <stdlib.h>


int productDigits(int n);

int main(void) {
    int n=969;

    productDigits(n);
    //printf("%d", n);

}

int productDigits(int n) {
    int someNum;
    if (n > 100) {
        someNum = n / 100;
        printf("%d\n", someNum);
        someNum = ((n % 100)/10);
        printf("%d\n", someNum);
        someNum = n % 10;
        printf("%d\n", someNum);
        return n;
    }

}
