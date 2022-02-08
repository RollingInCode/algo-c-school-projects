//Franklyn Gonzalez
//COP3502 - Computer Science I
//last edited 05/20/2020
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDSIZE 8
#define NUMOFWORDS 100

const int TILESCORES[] =
{1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10}; // all of these numbers represent a multiplier by the alphabet

int score(char **dictionary, char *playerTiles, int c, int n);
//void word(char *word);
//int turns(int *timesToPlay);
int wordCheck(char let, char **dictionary, char *playerTiles, int n);

int main() {

    char dictionary[NUMOFWORDS][WORDSIZE+1];
    char playerTiles[8];
    int bestScore = 0;

    //number of input cases
    int c;
    scanf("%d", &c);

    //number of words in the dictionary
    int n;
    scanf("%d", &n);



    //add words to dictionary
    for (int i = 0; i<n;i++) {
        scanf("%s", &dictionary[i]);
    }

    //add playertiles to input
    scanf("%s", &playerTiles);






    //How many times to play?
    //int timesToPlay;
    //int length, j;
    //printf("How many times to play?");
    //scanf("%d", turns(&timesToPlay)); //how many times do you want to play?


    bestScore = score(&dictionary, &playerTiles, c, n);


    //return the best score

    printf("%d", bestScore);
    return 0;
}



//Player's score from multiplier
int score(char **dictionary, char *playerTiles, int c, int n) {
    int bestScore[n];//represents the max score possible for the game

    char let;
    int i=0,j=0;
    int best = 0;


    //Use this to compare score values
    for (i = 0; i<NUMOFWORDS;i++) { //NUMOFWORDS shows the number of words made in the dictionary
        bestScore[i] = wordCheck(let, dictionary[i], &playerTiles, n);
        printf("\n %d of the best scores is %d ", i, bestScore[i]);
    }



    return best;
}

    //take the best score you find****
    //make sure you have an if, else statement for the null character '\0'






int wordCheck(char let, char **dictionary, char *playerTiles, int n) {
    //verify if each word has "this" tile with a for loop
    char verify[n];
    int playerScore = 1; //any number multiplied by one is kept
    int length, j=0;
    int m = 0;


    //Verify if the player's tiles are WORDS
    for (int i=0;i<n;i++) {
            length = strlen(dictionary[i]);
            printf("\nThe length of the word is :%d", length);
            printf("\n%s", dictionary[i]);
            printf("\n%s", playerTiles);
        if (strcmp(dictionary[i],playerTiles) == 0) { //If the two letters matched, it was added into the array "verify"
            verify[m] = dictionary[i]; //Collect letters from each word

            m++; //increment for the array
        }
    }

    //only verified letters were multiplied and added to the player's score
    for (j=0;j<length;j++) {
        let = verify[j]; //'let' will take the char value
        printf("\nThis is from the player's tile, part of the word. %d ", let);
        playerScore = playerScore * TILESCORES[let-'A']; //and then multiply!
    }


    return playerScore;

    //find a way to get words to continue, so you can have more words in your player score bank
}
/*
int turns(int *timesToPlay) {
    if (*timesToPlay>0) {
        return timesToPlay;
    }
    else {
        return 0;
    }

}
*/
