#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int length, width;
    printf("What is the width?");
    scanf("%d", &width);
    printf("What is the length?");
    scanf("%d", &length);

    if ((width>0)&&(length<0)) {
        printf("Diablo is happy!");
    }
    else {
        printf("Need more materials!");
    }

    return 0;
}
