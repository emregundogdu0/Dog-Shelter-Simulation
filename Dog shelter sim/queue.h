#ifndef queue
#define queue

#include <stdio.h>
#include <stdlib.h>
#include "Dog.h"

/*A queue node to represent dogs in the queue*/
struct QueueNode{
	Dog* value;
    int priority;
	struct QueueNode *next;
};

/*Queue Record that will store the following:
size: total number of elements stored in the list
front: it shows the front node of the queue (front of the queue)
rear: it shows the rare node of the queue (rear of the queue)*/
struct QueueRecord
{
	struct QueueNode *front;   /* pointer to front of queue */
	struct QueueNode *rear;    /* pointer to rear of queue */
	int size;             /* number of items in queue */
};

// A typedef to represent the dogs.
typedef struct QueueRecord *Queue;

// To allocate an address for the queue structure with dummy node by using MakeEmptyQueue
Queue CreateQueue();

// To initialize an empty queue with dummy node.
void MakeEmptyQueue(Queue);

//To add a new node to queue by priority
void Enqueue(Dog*, Queue);

//To remove the first node from the front of the queue.
Dog* Dequeue(Queue);

// To get the size of the queue
int QueueSize(Queue);

// To get the address of the dog from in front of the queue without removing it
Dog* FrontOfQueue(Queue);

// To get the address of the dog from the rear of the queue without removing it
Dog* RearOfQueue(Queue);

// To check if the queue is empty, 1 if its empty, otherwise 0
int IsEmptyQueue(Queue);

// A function to display information of the dogs in the queue.
void DisplayQueue(Queue);

//A function to free nodes and dogs from the queue
void deleteQueue(Queue);

#endif
