#include <stdio.h>
#include <stdlib.h>


int isSorted(int *array, int max, int n);

int main(void) {
    int array[] = {3,6,7,7,12};
    int max = 12;
    int n = 4;
    isSorted(array, max, n);


}


int isSorted(int *array, int max, int n) {
    if (array[n] > max) {
        return isSorted(array, max, n-1);
    }
    else if (array[n] < max)
        return 0;


}
