#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    double input = 0.00;
    double radius = 0.00;
    printf("What is the area of the circle\n");
    scanf("%d", &input);
    radius = (sqrt((input)/(3.14)));
    printf("%d", radius);
    return 0;
}
