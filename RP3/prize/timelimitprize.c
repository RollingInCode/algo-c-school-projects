#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(int *a, int *b);
int partition(int* vals, int low, int high);
void quicksort(int* numbers, int low, int high);

int partition(int* vals, int low, int high)
{
    int i, lowpos;

    // Pick a random partition element and swap it into index low.
    i = low + rand()%(high-low+1);
    swap(&vals[low], &vals[i]);

	// Store the index of the partition element.
	lowpos = low;

	// Update our low pointer.
	low++;

	// Run the partition so long as the low and high counters don't cross.
	while (low <= high) {

		// Move the low pointer until we find a value too large for this side.
		while (low <= high && vals[low] <= vals[lowpos]) low++;

		// Move the high pointer until we find a value too small for this side.
		while (high >= low && vals[high] > vals[lowpos]) high--;

		// Now that we've identified two values on the wrong side, swap them.
		if (low < high)
		   swap(&vals[low], &vals[high]);
	}

	// Swap the partition element into it's correct location.
	swap(&vals[lowpos], &vals[high]);

	return high; // Return the index of the partition element.
}

// Swaps the values pointed to by a and b.
void swap(int *a, int *b) {
     int temp = *a;
     *a = *b;
     *b = temp;
}

void quicksort(int* numbers, int low, int high) {

    // Only have to sort if we are sorting more than one number
    if (low < high) {
        int split = partition(numbers,low,high);
        quicksort(numbers,low,split-1);
        quicksort(numbers,split+1,high);
    }
}

char* readAll()
{
	unsigned long long int maxSize     = 2,
						   currentSize = 0;

	char* str = calloc(maxSize, sizeof(char));
	char c = '\0';
	while ((c = getchar()) != EOF)
	{
		str[currentSize++] = c;
		if (currentSize == maxSize - 1)
		{
			maxSize *= 2;
			str = realloc(str, maxSize * sizeof(char));
		}
	}

	str = realloc(str, (currentSize + 1) * sizeof(char));
	str[currentSize] = '\0';

	return str;
}

int main(void)
{
	char* stream = readAll();
	char* token = strtok(stream, " \n\r");

	int n, x, i = 0;

	n = atoi(token);
	token = strtok(NULL, " \n\r");
	x = atoi(token);
	token = strtok(NULL, " \n\r");

	int arr[n];
	while (i < n)
	{
		arr[i++] = atoi(token);
		token = strtok(NULL, " \n\r");
	}

	quicksort(arr, 0, n - 1);

	int result = 1;
	for (int j = 1; j < n; j++)
	{
		if (arr[j] + arr[j - 1] > x)
			break;
		result++;
	}
	printf("%d", result);
	free(stream);
	return 0;
}
