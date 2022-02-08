// Arup Guha
// 11/10/2014
// Solution to Chapter 13 Problem #1: isPrime function

#include <stdio.h>

int isPrime(int n);

int main() {

    int i;

    // Test function by print all primes to 100.
    printf("Primes up to 100 are:\n");
    for (i=0; i<100; i++)
        if (isPrime(i))
            printf("%d ", i);
    printf("\n");

    return 0;
}

// Note: This function can be written more efficiently.
//       This is a straight-forward implementation.
int isPrime(int n) {

    // First prime is 2.
    if (n < 2) return 0;

    // Look for proper divisor using brute force.
    int i;
    for (i=2; i<n; i++)
        if (n%i == 0)
            return 0;

    // If we get here, n must be prime.
    return 1;
}
