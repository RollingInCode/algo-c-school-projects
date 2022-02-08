#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(int *a, int *b);
int partition(int* vals, int low, int high);
void quicksort(int* numbers, int low, int high);

void insertionSort(int arr[], int left, int right)
{
    int i;
    for (i = left + 1; i <= right; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            int j = i;

            do
            {
                swap(&arr[j], &arr[j-1]);
				j--;
            } while (j > left && arr[j] < arr[j - 1]);
        }
    }
}

int median(int a, int b, int c)
{
	if (a >= b)
		if (b >= c)
			return b;
		else
			if (c >= a)
				return c;
			else
				return a;
	else
		if (b >= c)
			if (a >= c)
				return a;
			else
				return c;
		else
			return b;
}

int partition(int* vals, int low, int high) 
{
    int i, lowpos;

    // Pick a random partition element and swap it into index low.
	int a = low + rand()%(high-low+1),
	    b = low + rand()%(high-low+1),
	    c = low + rand()%(high-low+1);
	int m = median(vals[a], vals[b], vals[c]);

	if (m == vals[a])
		i = a;
	else if (m == vals[b])
		i = b;
	else
		i = c;

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
		if (high - low < 100) {
			insertionSort(numbers, low, high);
			return;
		}
        int split = partition(numbers,low,high);
        quicksort(numbers,low,split-1);
        quicksort(numbers,split+1,high);
    }
}

int main(int argc, char **argv)
{
	int n, x, i = 0;

	scanf("%i", &n);
	scanf("%i", &x);
	
	int arr[n];

	while (i < n)
		scanf("%i", &arr[i++]);
	
	quicksort(arr, 0, n - 1);
		
	int result = 1;
	for (int j = 1; j < n; j++)
	{
		if (arr[j] + arr[j - 1] > x)
			break;
		result++;
	}
	printf("%d", result);
	return 0;
}