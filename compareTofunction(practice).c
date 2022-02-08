#include <stdio.h>
#include <stdlib.h>

struct node{
    struct node *front;
    struct node *back;
    int *ptrP1;
    int *ptrP2;
}

int compareTo(int *ptrP1, int *ptrP2);

int main(void) {


}

int compareTo(node *front) {
    struct node temp;
    temp = malloc(sizeof(struct node));
    temp = front;

    if (temp->back) {
        return -1;
    }
    else if (temp->front == NULL) {
        return 1;
    }
    else if (temp->front == temp->back) {
        return 0;
    }


}

int binsearch(int low, int high, int searchVal, int array[]) {

    if (low > high) return 0;
    int mid = (low+high)/2;

    // my value is smaller than the one in index mid.
    if (searchVal < array[mid])
        return binsearch(low, mid-1, searchVal, array);

    // here it's larger
    else if (searchVal > array[mid])
        return binsearch(mid+1, high, searchVal, array);

    // found it!
    else
        return 1;
}
