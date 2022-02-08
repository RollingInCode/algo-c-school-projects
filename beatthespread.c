#include <stdio.h>
#include <stdlib.h>

int main(void) {

    // Read in # of cases
    int numCases;
    scanf("%d", &numCases);

    // Process each case.
    for (int loop=0; loop<numCases;loop++)

        int sum, diff;
        scanf("d%d%", &sum, &diff);

        // Use system of equations to solve both scores
        int x = (sum+diff)/2;
        int y = (sum-diff)/2;


    return 0;
}
