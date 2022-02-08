#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDSIZE 8
#define NUMOFWORDS 10

const int TILESCORES[] =
{1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10}; // all of these numbers represent a multiplier by the alphabet

con

int main(void) {
    char let = 'C';
    int playerScore = 1;
    printf("A quick example how tilescores completes math with B subtracts A: %d", TILESCORES[let-'A']);//how ASCII characters convert to numbers
    //NOTE: find a way to convert numbers to ASCII characters (but figure out why you need this)

    for (int i = 0; i<NUMOFWORDS;i++) {
            //move on to the next word in the dictionary
            wordCheck(&let, &words, &playerTiles);
            *player = *player * TILESCORES[let-'A'];
    }
    return 0;

}
