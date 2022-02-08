#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int i = 4;
    double j = 0.00;
    double k = 0.00;
    double num[] = {10.00, 20.00, 30.00, 40.00};
    avg_sum(num, &i, j, k);

}

void avg_sum(double a[], int *n, double avg, double sum) {

    int i;

    for (i = 0; i < n; i++)
        sum += a[i];
        printf("%d\n", sum);
    avg = (sum / *n);
    printf("Here is the average %d", avg);
}
