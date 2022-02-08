// Arup Guha
// 7/24/2020
// Solution to COP 3502 Program #5: Procrastination at its Finest

#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 10

// Stores all relevant information about a task.
typedef struct task {
    int ID;
    int timeGiven;
    int numPhases;
    int* times;
    int curTimeLeft;
    int curIdx;

} task;

// We need a heap of tasks.
typedef struct heap {
    task** arr;
    int curIdx;
    int capacity;
} heap;

// Heap functions.
int compareTo(task* t1, task* t2);
void initHeap(heap* hPtr);
void percolateUp(heap* hPtr, int idx);
void percolateDown(heap* hPtr, int idx);
void insert(heap* hPtr, task* tPtr);
task* deleteMin(heap* hPtr);
int size(heap* hPtr);

// Reads in a task into the struct pointed to by tPtr.
void readTask(task* tPtr, int myID);

// Executes the current phase of the task pointed to by tPtr.
int doPhase(task* tPtr, int curT);
int isDone(task* tPtr);

// Help to clean up.
void freeTaskArray(task* arr, int length);

int main(void) {

    int nTasks;
    task* taskArr;

    // Read in number of tasks, allocate array.
    scanf("%d", &nTasks);
    taskArr = calloc(nTasks, sizeof(task));

    // Go through and read in each task.
    for (int i=0; i<nTasks; i++)
        readTask(&taskArr[i], i);

    // Set up heap.
    heap myHeap;
    initHeap(&myHeap);

    // Stores our current time.
    int t = 0;

    // Stores the next item to insert into the heap.
    int heapIdx = 0;

    // Run simulation.
    while (1) {

        // Add all new tasks to heap.
        while (heapIdx < nTasks && taskArr[heapIdx].timeGiven <= t) {

            // Add item to heap.
            insert(&myHeap, &taskArr[heapIdx]);

            // Advance to the next heap item.
            heapIdx++;
        }

        // Case where no task is open so we have to advance time.
        if ( size(&myHeap) == 0 && heapIdx < nTasks  && t < taskArr[heapIdx].timeGiven) {

            // Update time.
            t = taskArr[heapIdx].timeGiven;

            // Add item to heap.
            insert(&myHeap, &taskArr[heapIdx]);

            // Advance to the next heap item.
            heapIdx++;
        }

        // This signifies that we are done.
        if (size(&myHeap) == 0) break;

        // This tells me the next task to do.
        task* toDo = deleteMin(&myHeap);

        // Do the phase and return the time it is after completing it.
        t = doPhase(toDo, t);

        // We only insert this back into the heap if it's not done.
        if (!isDone(toDo))
            insert(&myHeap, toDo);
    }

    // Free heap array.
    free(myHeap.arr);

    // Frees all dynamically associated memory with the task array.
    freeTaskArray(taskArr, nTasks);

    return 0;
}

// Frees all the dynamically allocated memory associated with arr.
void freeTaskArray(task* arr, int length) {
    for (int i=0; i<length; i++)
        free(arr[i].times);
    free(arr);
}

// Reads in task information into the struct pointed to by tPtr.
void readTask(task* tPtr, int myID) {

    // Set this first.
    tPtr->ID = myID;

    // Read in time given and # of phases.
    scanf("%d", &(tPtr->timeGiven));
    scanf("%d", &(tPtr->numPhases));

    // Allocate time array.
    tPtr->times = calloc(tPtr->numPhases, sizeof(int));
    tPtr->curTimeLeft = 0;

    // Read in the times, update total time.
    for (int i=0; i<tPtr->numPhases; i++) {
        scanf("%d", &(tPtr->times[i]));
        tPtr->curTimeLeft += tPtr->times[i];
    }

    // Our current task is 0.
    tPtr->curIdx = 0;
}

// Executes the current phase of this task, returning the time it took.
int doPhase(task* tPtr, int curT) {

    // Save time to return and update time left on this task.
    int retval = curT + tPtr->times[tPtr->curIdx];

    // Get the printing out of the way.
    printf("%d %d %d\n", curT+tPtr->times[tPtr->curIdx], tPtr->ID+1, tPtr->curIdx+1);

    // Update time left.
    tPtr->curTimeLeft -= tPtr->times[tPtr->curIdx];

    // Just add 1 here.
    tPtr->curIdx++;

    // We return this.
    return retval;
}

// Returns 1 iff the task pointed to by tPtr is done.
int isDone(task* tPtr) {
    return tPtr->curIdx == tPtr->numPhases;
}

// Initializes an empty heap.
void initHeap(heap* hPtr) {
    hPtr->arr = calloc(INIT_SIZE+1, sizeof(task*));
    hPtr->curIdx = 0;
    hPtr->capacity = INIT_SIZE;
}

// Runs percolateUp on index idx in the heap.
void percolateUp(heap* hPtr, int idx) {

    // This just prevents going out of bounds on the array.
    while (idx > 1) {

        // Here is where we go up.
        if (compareTo(hPtr->arr[idx], hPtr->arr[idx/2]) < 0) {
            task* tmp = hPtr->arr[idx];
            hPtr->arr[idx] = hPtr->arr[idx/2];
            hPtr->arr[idx/2] = tmp;
            idx /= 2;
        }

        // Or get out.
        else
            break;
    }
}

// Runs percolate down on the node at index idx.
void percolateDown(heap* hPtr, int idx) {

    // Just prevents going out of bounds on the heap.
    while (2*idx <= hPtr->curIdx) {

        // My default setting.
        int child = 2*idx;

        // See if right child beats this one out.
        if (hPtr->curIdx >= 2*idx+1 &&
            compareTo(hPtr->arr[2*idx+1], hPtr->arr[2*idx])< 0)

            child = 2*idx+1;

        // Swap and update idx.
        if (compareTo(hPtr->arr[child], hPtr->arr[idx]) < 0) {
            task* tmp = hPtr->arr[child];
            hPtr->arr[child] = hPtr->arr[idx];
            hPtr->arr[idx] = tmp;
            idx = child;
        }

        // Otherwise, we get out.
        else
            break;
    }
}

// Adds the task pointed to by tPtr to the heap pointed to b hPtr.
void insert(heap* hPtr, task* tPtr) {

    // Heap is full double the size.
    if (hPtr->capacity == hPtr->curIdx) {
        hPtr->arr = realloc(hPtr->arr, (2*hPtr->capacity+1)*sizeof(heap*));
        hPtr->capacity *= 2;
    }

    // Add to heap.
    hPtr->arr[hPtr->curIdx+1] = tPtr;
    hPtr->curIdx++;

    // Now, we can percolate up.
    percolateUp(hPtr, hPtr->curIdx);
}

// Deletes the minimum item from the heap pointed to by hPtr
// and returns a pointer to the task.
task* deleteMin(heap* hPtr) {

    // Nothing to delete.
    if (hPtr->curIdx == 0) return NULL;

    // What we will return.
    task* retVal = hPtr->arr[1];

    // Copy last item to the top and update size now.
    hPtr->arr[1] = hPtr->arr[hPtr->curIdx];
    hPtr->curIdx--;

    // Now, percolate down, if non-empty.
    if (hPtr->curIdx > 0)
        percolateDown(hPtr, 1);

    return retVal;
}

// Returns the size of the heap pointed to by hPtr.
int size(heap* hPtr) {
    return hPtr->curIdx;
}

// Returns a negative integer if t1 should be performed before
// t2, and a positive integer otherwise. (For this program this
// should never return 0.
int compareTo(task* t1, task* t2) {

    // Our procrastination rule.
    if (t1->curTimeLeft != t2->curTimeLeft)
        return t2->curTimeLeft - t1->curTimeLeft;

    // We can get away with this since the ID numbers of
    // tasks are in order of the time you receive the task and
    // no two tasks are given at the same time.
    return t1->timeGiven - t2->timeGiven;
}
