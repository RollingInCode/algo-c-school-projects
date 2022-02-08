// Arup Guha
// 11/10/2014
// Solution to Chapter 14 Practice Program #1: increment

#include <stdio.h>

void increment(int* ptrValue);

int main() {

    // Test increment.
    int n = 11;
    printf("n is now %d.\n", n);
    increment(&n);
    printf("n changed to %d.\n", n);

    return 0;
}

void increment(int* ptrValue) {
    (*ptrValue) += 1;
}
