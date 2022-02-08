// Arup Guha
// Simple Grid Game - move around a 2D grid.
// Written in COP 3223 class 3/1/2011
// Edited on 1/17/2017 in COP3502 to show another use of DX/DY arrays.

// Note: Still no error checking - lots of opportunity to edit and practice!!!

#include <stdio.h>

#define ROWS 5
#define COLS 10

// Allows movement up, left, right and down.
const int DX[] = {-1,0,0,1};
const int DY[] = {0,-1,1,0};

int main() {

    int i, j;
    char board[ROWS][COLS];

    // Initialize the game board.
    for (i=0; i<ROWS; i++)
        for (j=0; j<COLS; j++)
            board[i][j] = '_';

    // Ask the user where they want to start.
    int row, col;
    printf("Where do you want to start (row, col)?\n");
    scanf("%d%d", &row, &col);

    // Place an X on the starting square - no error checking here.
    board[row][col] = 'X';

    // Print out the board.
    for (i=0; i<ROWS; i++) {
        for (j=0; j<COLS; j++)
            printf("%c", board[i][j]);
        printf("\n");
    }

    // Set up a loop we'll break out of.
    while (1) {

        // See if the user wants to move again.
        int choice;
        printf("Do you want to move again?(1=yes, 0=no)\n");
        scanf("%d", &choice);

        // Time to stop!
        if (choice == 0)
            break;

        // Get the user's move.
        int dir;
        printf("Where do you want to move? (0=up,1=left,2=right,3=down,\n");
        scanf("%d", &dir);

        // Moving is this easy!
        row += DX[dir];
        col += DY[dir];

        // Place an X in the new square.
        board[row][col] = 'X';

        // Reprint the board.
        for (i=0; i<ROWS; i++) {
            for (j=0; j<COLS; j++)
                printf("%c", board[i][j]);
            printf("\n\n");
        }

    }

    return 0;
}
