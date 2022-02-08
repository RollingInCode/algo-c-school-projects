// Arup Guha
// 5/12/2020
// Solution to Sample COP 3502 Program #1: Sudoku Checker

#include <stdio.h>

const int SIZE = 9;
const int BOXSIZE = 3;

int checkRow(int grid[][SIZE], int rowNum);
int checkCol(int grid[][SIZE], int colNum);
int checkBox(int grid[][SIZE], int startRow, int startCol);
int checkAll(int grid[][SIZE]);

int main(void) {

    int numCases;
    scanf("%d", &numCases);

    // Process each case.
    for (int loop=0; loop<numCases; loop++) {

        int grid[SIZE][SIZE];

        // Read in the grid.
        for (int i=0; i<SIZE; i++) {

            // Read in the line.
            char line[SIZE+1];
            scanf("%s", line);

            // Converts each to an int.
            for (int j=0; j<SIZE; j++)
                grid[i][j] = line[j] - '0';
        }

        // Check it and print the appropriate response.
        if (checkAll(grid))
            printf("YES\n");
        else
            printf("NO\n");
    }


    return 0;
}

// Pre-condition: grid is 9 by 9.
// Returns 1 if grid is a valid Sudoku grid, 0 otherwise.
int checkAll(int grid[][SIZE]) {

    // If any row doesn't pass, say it's not valid.
    for (int i=0; i<SIZE; i++)
        if (!checkRow(grid, i))
            return 0;


    // If any column doesn't pass, say it's not valid.
    for (int i=0; i<SIZE; i++)
        if (!checkCol(grid, i))
            return 0;

    // If any box doesn't pass, say it's not valid.
    for (int i=0; i<SIZE; i+=BOXSIZE)
        for (int j=0; j<SIZE; j+=BOXSIZE)
            if (!checkBox(grid, i, j))
                return 0;

    // If we get here, we are good.
    return 1;
}

// Pre-condition: grid is 9 x 9, rowNum must be in between 0 and 8, inclusive.
// Post-condition: returns 1 if all values 1 to 9 appear on row rowNum, 0 otherwise.
int checkRow(int grid[][SIZE], int rowNum) {

    // Initialize frequency array.
    int freq[SIZE+1];
    for (int i=0; i<SIZE+1; i++)
        freq[i] = 0;

    // Go to each column.
    for (int i=0; i<SIZE; i++) {

        // Not in between 1 and 9.
        if (grid[rowNum][i] < 1 || grid[rowNum][i] > 9)
            return 0;

        // Update the frequency.
        freq[grid[rowNum][i]]++;

        // Found a repeated value.
        if (freq[grid[rowNum][i]] > 1)
            return 0;
    }

    // If we get here we are good.
    return 1;
}

// Pre-condition: grid is 9 x 9, colNum must be in between 0 and 8, inclusive.
// Post-condition: returns 1 if all values 1 to 9 appear on column colNum, 0 otherwise.
int checkCol(int grid[][SIZE], int colNum) {

    // Initialize frequency array.
    int freq[SIZE+1];
    for (int i=0; i<SIZE+1; i++)
        freq[i] = 0;

    // Go to each row.
    for (int i=0; i<SIZE; i++) {

        // Not in between 1 and 9.
        if (grid[i][colNum] < 1 || grid[i][colNum] > 9)
            return 0;

        // Update the frequency.
        freq[grid[i][colNum]]++;

        // Found a repeated value.
        if (freq[grid[i][colNum]] > 1)
            return 0;
    }

    // If we get here we are good.
    return 1;
}

int checkBox(int grid[][SIZE], int startRow, int startCol) {

    // Initialize frequency array.
    int freq[SIZE+1];
    for (int i=0; i<SIZE+1; i++)
        freq[i] = 0;

    // Go to each row,col in the box
    for (int i=startRow; i<startRow+BOXSIZE; i++) {
        for (int j=startCol; j<startCol+BOXSIZE; j++) {

            // Not in between 1 and 9.
            if (grid[i][j] < 1 || grid[i][j] > 9)
                return 0;

            // Update the frequency.
            freq[grid[i][j]]++;

            // Found a repeated value.
            if (freq[grid[i][j]] > 1)
                return 0;
        }
    }

    // If we get here we are good.
    return 1;
}
