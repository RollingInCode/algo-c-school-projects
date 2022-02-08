#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int lucasNumbers(int n);
int power(int base, int exp);

int main(void){
    int n=7;
    //int m = 0;
    //scanf("%d", &n);
    //scanf("%d", &m);
    n = n^2;
    printf("%d", n);
    //lucasNumbers(n);
    //printf("%d", m);

}

int lucasNumbers(int n) {
    if (n == 11){
        return n;
    }
    else
        printf("%d \n", n);
        system("pause");
        lucasNumbers(power( ((1+sqrt(5))/2) , n-1)+(power( ((1-sqrt(5))/2), n-2)));


}

int power(int base, int exp) {
    int i, result = 1;
    for (i = 0; i < exp; i++) {
        result *= base;
    }
    return result;

}
