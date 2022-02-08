#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int back();
int forth();

int main(void){
    int m,n,*a, dataset, minVal=2, best=0, sum = 0;
    //Dataset input c
    scanf("%d", &dataset);

    //Holds n positive integers
    scanf("%d", &n);
    if (n>(10^5)) {
        exit(0); //Exit
    }
    a = malloc(n * sizeof(int));

    //minimum element a subarray MUST have
    scanf("%d", &m);
    if (m>(2^6)) {
        exit(0); //Exit
    }

    if (dataset>20) {
        exit(0); //Exit
    }

    else {
        for (int i=0; i<dataset;i++) {
            for (int j=0;j<n;j++) {
                //a[j] = (rand() % (2^6));
                scanf("%d ", a[j]);
            }
            for (int k=0;k<a[n-1];k++) {
                sum += a[k];
                if (a[k] < minVal) {
                minVal = a[k];
                }
            }
            if((minVal == m) && (sum > best)) {
                    best = sum;
                    printf("\n%d ", best);
            }


        }
    }

    return 0;
}
