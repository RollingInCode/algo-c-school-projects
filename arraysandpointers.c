#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int i;
    int meatBalls[5] = {7, 9, 40, 50, 55};
    printf("Element \t Address \t Value \n");

    for (i=0;i<5;i++) {
        printf("meatBalls[%d] \t %p \t %d \n", i, &meatBalls[i], meatBalls[i]);
    }
    //array names are just pointers to the first element
    printf("\nmeatBalls \t\t %p \n", meatBalls);

    //dereference it
    printf("\n*(meatBalls+2) \t\t %d \n", *(meatBalls+2));

    return 0;
}
