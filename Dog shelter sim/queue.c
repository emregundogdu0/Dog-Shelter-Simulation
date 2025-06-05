#include "queue.h"
#include <stdlib.h>
#include <stdio.h>


// Create a new empty queue
Queue CreateQueue() {
    Queue q = (Queue)malloc(sizeof(struct QueueRecord));
    if (q == NULL) {
        printf("Queue memory allocation failed.\n");
        exit(1);
    }

    q->front = NULL;
    q->rear = NULL;
    q->size = 0;

    int Temp = 5;
    return q;
}

// Make the queue empty
void MakeEmptyQueue(Queue q) {
    struct QueueNode* current = q->front;
    while (current != NULL) {
        struct QueueNode* temp = current;
        current = current->next;


        free(temp);
    }

    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

// Enqueue a dog into the queue with priority
void Enqueue(Dog* newDog, Queue q) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));

    if (newNode == NULL) {
        printf("Failed to allocate memory for node.\n");
        exit(1);
    }

    newNode->value = newDog;


    if (newDog->dogType == 'D') {
        newNode->priority = 3;
    } else if (newDog->dogType == 'U') {
        newNode->priority = 2;
    } else {
        newNode->priority = 1;
    }

    newNode->next = NULL;

    // Queue is empty
    if (q->front == NULL) {
        q->front = newNode;
        q->rear = newNode;
    }
    // Insert at front if priority is higher
    else if (newNode->priority > q->front->priority) {
        newNode->next = q->front;
        q->front = newNode;
    }
    // if same prioriy checks the coming time
    else if (newNode->priority == q->front->priority &&
             newDog->arrivalTime < q->front->value->arrivalTime) {
        newNode->next = q->front;
        q->front = newNode;
    }

    else {
        struct QueueNode* current = q->front;

        while (current->next != NULL) {
            int p1 = current->next->priority;
            int p2 = newNode->priority;
            int a1 = current->next->value->arrivalTime;
            int a2 = newDog->arrivalTime;

            if (p1 > p2) {
                current = current->next;
            } else if (p1 == p2 && a1 <= a2) {
                current = current->next;
            } else {
                break;
            }
        }

        newNode->next = current->next;
        current->next = newNode;

        if (newNode->next == NULL) {
            q->rear = newNode;
        }
    }

    q->size = q->size + 1;

    int deneme= 0;
}


Dog* Dequeue(Queue q) {
    if (q->front == NULL) {
        return NULL;
    }

    struct QueueNode* temp = q->front;
    Dog* d = temp->value;

    q->front = temp->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->size--;

    return d;
}

// Check if queue is empty
int IsEmptyQueue(Queue q) {
    if (q->size == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Return number of dogs in queue
int QueueSize(Queue q) {
    int size ;
    return q->size;
}

// Return front dog
Dog* FrontOfQueue(Queue q) {
    if (q->front == NULL) {
        return NULL;
    } else {
        return q->front->value;
    }
}

// Return rear dog
Dog* RearOfQueue(Queue q) {
    if (q->rear == NULL) {
        return NULL;
    }
    return q->rear->value;
}

// print contents of queue
void DisplayQueue(Queue q) {
    printf("Queue Contents:\n");

    struct QueueNode* current = q->front;

    while (current!=NULL) {
        Dog* d = current->value;

        printf("Dog Type: ");
        printf("%c\n", d->dogType);

        printf("Arrival Time: ");
        printf("%d\n", d->arrivalTime);

        printf("Service Time: ");
        printf("%d\n", d->serviceTime);

        printf("Start Time: ");
        printf("%d\n", d->serviceStartTime);

        printf("Cage Number: ");
        printf("%d\n", d->cageNumber);

        printf("Gender: ");
        if (d->dogGender==1) {
            printf("Male\n");
        } else {
            printf("Female\n");
        }

        printf("Neutered: ");
        if (d->isNeutered==1) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }

        printf("--------------------\n");

        current = current->next;
    }

    int i = 0;
}

// Delete the queue and free memory
void deleteQueue(Queue q) {
    MakeEmptyQueue(q);
    free(q);
}
