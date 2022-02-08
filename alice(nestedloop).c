#include <stdio.h>
#include <stdlib.h>

//int subarray(int i, int m, int nums);

int main(void){
    int m,n, dataset, best=0;
    int nums = 0;
    //Dataset input
    scanf("%d", &dataset);

    //Holds n positive integers
    scanf("%d", &n);
    if (n>(10^5)) {
        exit(0); //Exit
    }
    int *a = malloc(n * sizeof(int)); //main array
    //int *b = malloc(n * sizeof(int)); //subarray

    //minimum element a subarray MUST have
    scanf("%d", &m);
    //if (m>(2^6)) {
        //exit(0); //Exit
    //}

    //if (dataset>20) {
        //exit(0); //Exit
    //}
    //printf("\nProcessing\n");
    for (int g =0; g<n;g++){
        scanf("%d", &a[g]);
        printf("%d ", a[g]);
        //b[g] = a[g];
    }
    //we're gonna have to figure out a way that best is greater than the sum or 2 (which is my min value)
    //but then again, sum is adding up all of these numbers, so that means I have to figure out a way to ignore the sum value because (1 is included in this subarray)

    for (int i=0; i<n;i++) {
            printf("\n LOOP NUMBER #%d : this is for i: %d", i,i);

        for (int j=1;j<n;j++) {
            printf("\n LOOP NUMBER #%d : this is for j: %d", j,j);
            int minVal = a[i];
            int sum = a[i];

            for (int k=i+1;k<=j;k++) { // 1 was ignored because k starts at 1
                printf("\n this is for k: %d", k);
                printf("\n this is for j: %d", j);
                printf("\n here is sum: %d", sum);
                sum += a[k];

                if (a[k] < minVal) {
                    minVal = a[k];
                    printf("\nThis is minVal here: %d", minVal);
                }

            }
            if((minVal == m) && (sum > best)) {
                    best = sum;


                    printf("\n the best number is: %d\n", best);

            }

        }
    printf("\n%d ", best);
    return 0;
    }
}
/*
int subarray(int i, int m, int nums) { //you want to pass j because
    //int temp = 0;
    int *b = malloc(nums * sizeof(int)); //subarray
    for (int p = n;i<j;i++) {
        if (b[i] < m) {
            *b = calloc(0, sizeof(int)); //clear subarray
            return best;
        }

    }
}
            if (a[i] < m) {
                sum -= a[i];
            }
            if ((a[i+1] < m) && (a[i] < m)) { // not true statement
                sum -= a[+1];// use an if else statement if you want to get around the two arrays and comparing the two.

            }
*/
