/// Franklyn Gonzalez, COP3502, Computer Science I, last edited July 28th, 2020, 21:56
// ***
// ***
// ***


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Some macro functions to get the children of our heap from the index of a node
// in the array
#define getParent(_i) (int)floor(((float) _i - 1.0) / 2.0)
#define getLeft(_i) 2* _i + 1
#define getRight(_i) 2* _i + 2

// ======================== Task-Related Functions ===========================

typedef struct Task
{
    int id,
	assignedAt,
	numPhases,
	totalPhases,
	timeLeft,
	nextTask;
    int* phaseLength;
} Task;

/**
   Compares two Tasks, returning -1 if the first is less than the second
in their ordering, 0 if they are equal, and 1 if the first is greater than the second
in their ordering.
*/
int compareTo(Task* t1, Task* t2)
{
    if (t1->timeLeft < t2->timeLeft)
	return -1;
    else if (t1->timeLeft > t2->timeLeft)
	return 1;
    else if (t1->id > t2->id)
	return -1;
    else if (t1->id < t2->id)
	return 1;
    else
	return 0;
}

// ======================== Heap-Related Functions ===========================

typedef struct BinaryHeap
{
    Task* task;
    int size,
	maxSize;
} BinaryHeap;

/**
   Initializes a pointer to a BinaryHeap struct
 */
BinaryHeap* newBinaryHeap()
{
    BinaryHeap* heap = malloc(sizeof(BinaryHeap));
    heap->maxSize = 10;
    heap->size = 0;
    heap->task = calloc(sizeof(Task), heap->maxSize);

    return heap;
};

/**
   Doubles a heap's size for when it reaches capacity
 */
void extendHeap(BinaryHeap* heap)
{
    heap->maxSize *= 2;
    heap->task = realloc(heap->task, sizeof(Task) * heap->maxSize);
    return;
}

/**
   A convenience function for swapping two Tasks in a heap's internal array
 */
void swapTasks(BinaryHeap* heap, int t1, int t2)
{
    Task temp = heap->task[t1];
    heap->task[t1] = heap->task[t2];
    heap->task[t2] = temp;

    return;
}

/**
   If a node is larger than its parent, "bubbles" it up until its parent is larger
 */
void upHeap(BinaryHeap* heap, int node)
{
    if (node == 0)
	return;

    int parent = getParent(node);

    if (compareTo(&heap->task[parent], &heap->task[node]) == -1)
    {
	swapTasks(heap, node, parent);
	upHeap(heap, parent);
    }

    return;
}

/**
   Inserts a new task into the heap by 'up-heaping' and extending it as needed
 */
void insert(Task* t, BinaryHeap* heap)
{
    if (heap->size >= heap->maxSize)
	extendHeap(heap);

    heap->task[heap->size] = *t;
    upHeap(heap, heap->size);

    heap->size++;

    return;
}

/**
   After an element is extracted from the heap, a small element becomes the root. This
function "bubbles" that node downwards until it is no longer smaller than any of its children.
 */
void downHeap(BinaryHeap* heap, int node)
{
    int leftChildIndex = getLeft(node),
	rightChildIndex = getRight(node);

    Task *leftChild = 0,
	*rightChild = 0,
	*current = &heap->task[node];

    if (leftChildIndex < heap->size)
	leftChild = &heap->task[leftChildIndex];
    if (rightChildIndex < heap->size)
	rightChild = &heap->task[rightChildIndex];

    if (leftChild && rightChild)
    {
	if (compareTo(current, leftChild) == -1)
	    if (compareTo(leftChild, rightChild) == -1)
	    {
		swapTasks(heap, node, rightChildIndex);
		downHeap(heap, rightChildIndex);
	    }
	    else
	    {
		swapTasks(heap, node, leftChildIndex);
		downHeap(heap, leftChildIndex);
	    }
	else if (compareTo(current, rightChild) == -1)
	{
	    swapTasks(heap, node, rightChildIndex);
	    downHeap(heap, rightChildIndex);
	}
    }
    else if (leftChild)
    {
	if (compareTo(current, leftChild) == -1)
	{
	    swapTasks(heap, node, leftChildIndex);
	    downHeap(heap, leftChildIndex);
	}
    }
    else if (rightChild)
    {
	if (compareTo(current, rightChild) == -1)
	{
	    swapTasks(heap, node, rightChildIndex);
	    downHeap(heap, rightChildIndex);
	}
    }

    return;
}

/**
   Removes and returns the top element off the heap
 */
Task extract(BinaryHeap* heap)
{
    Task max;
    max = heap->task[0];

    heap->size--;
    heap->task[0] = heap->task[heap->size];
    downHeap(heap, 0);

    return max;
}

// ======================== Simulation-Related Functions =====================

/**
   A convenience function meant to read a line from stdin representing a Task into a Task
 */
Task readTask(int id)
{
    Task task;
    task.id = id;
    task.timeLeft = 0;
    task.nextTask = 0;

    fscanf(stdin, "%d", &task.assignedAt);
    fscanf(stdin, "%d", &task.numPhases);
    task.totalPhases = task.numPhases;

    task.phaseLength = malloc(task.numPhases*sizeof(int));

    int i;
    for (i = task.numPhases - 1; i >= 0; i--)
    {
	fscanf(stdin, "%d", &task.phaseLength[i]);
	task.timeLeft += task.phaseLength[i];
    }

    return task;
}

/**
   Achieves ultimate procrastination by continuously only doing the task which is
furthest from completion
 */
void runSimulation(Task* task, int numTasks)
{
    // Start the simulation at the time the first task was given to us
    int time = task[0].assignedAt;
    int tasksAdded = 0;

    BinaryHeap* heap = newBinaryHeap();

    // We'll add the first task to the heap, along with every task assigned at the same
    // time as it
    do
    {
	insert(&task[tasksAdded], heap);
	tasksAdded++;
    } while (tasksAdded < numTasks && task[tasksAdded].assignedAt == task[0].assignedAt);

    while (heap->size > 0) {

	// Get the task furthest from being done, print out information about it, then simulate
	// completing a phase of it
	Task currentTask = extract(heap);
	time += currentTask.phaseLength[currentTask.numPhases - 1];
	fprintf(stdout, "%d %d %d\n", time, currentTask.id + 1, currentTask.totalPhases - currentTask.numPhases + 1);
	currentTask.timeLeft -= currentTask.phaseLength[currentTask.numPhases - 1];
	currentTask.numPhases--;

	// If we're not done with this task, we need to add it back to the heap
	if (currentTask.numPhases > 0)
	    insert(&currentTask, heap);

	// Add any tasks which were given to us while working on the previous phase
	while (tasksAdded < numTasks && task[tasksAdded].assignedAt <= time)
	    insert(&task[tasksAdded++], heap);

	// We did everything assigned but haven't completely finished. Fast-forward to the next task
	if (heap->size == 0 && tasksAdded < numTasks){
	    insert(&task[tasksAdded], heap);
	    time = task[tasksAdded].assignedAt;
	    tasksAdded++;
        }
    }
    free(heap);

    return;
}

/**
   Initializes the tasks and begins the simulation
 */
int main(void)
{
    int numTasks = 0;
    fscanf(stdin, "%d", &numTasks);

    if (numTasks == 0)
	return 0;

    Task* task = malloc(numTasks*sizeof(Task));
    int i;
    for (i = 0; i < numTasks; i++)
        task[i] = readTask(i);

    fprintf(stdout, "\n");
    runSimulation(task, numTasks);

    free(task);

    return 0;
}

