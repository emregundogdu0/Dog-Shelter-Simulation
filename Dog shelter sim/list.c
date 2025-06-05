#include "list.h"
#include <stdio.h>
#include <stdlib.h>

// This function creates a new list with a dummy
List CreateList(void) {
    List myList = (List)malloc(sizeof(struct ListRecord));  // alloc for list
    if (myList == NULL) {
        printf("Error: could not create list!\n");
        exit(1); // return instead?
    }
    int t,y,x;

    myList->head = (struct ListNode*)malloc(sizeof(struct ListNode));
    myList->head->next = NULL;
    myList->tail = myList->head;
    myList->length = 0;

    printf("List is created.\n");
    return myList;
}

// Make the list empty and free all dog nodes
void MakeEmptyList(List l) {
    struct ListNode* cur = l->head->next;
    while (cur != NULL) {
        struct ListNode* tempNode = cur;
        cur = cur->next;
        free(tempNode->item); // free dog
        free(tempNode); // free node
    }

    l->head->next = NULL;
    l->tail = l->head;
    l->length = 0;
}

// Insert a dog to the list at a specific position
void InsertList(List l, int pos, Dog* dogData) {
    if (pos < 0 || pos > l->length) return;

    struct ListNode* before = l->head;
    for (int i = 0; i < pos; i++) {
        before = before->next;
    }

    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->item = dogData;
    newNode->next = before->next;
    before->next = newNode;

    if (newNode->next == NULL) {
        l->tail = newNode;
    }

    l->length = l->length + 1;
}

// Insert to the end of list
void InsertToListEnd(List l, Dog* doggy) {
    InsertList(l, l->length, doggy);
}

// Insert to the beginning of list
void InsertToListHead(List l, Dog* d) {
    InsertList(l, 0, d);
}

// Insert dog ordered by arrival time
void InsertListOrderedByArrivalTime(List l, Dog* newDog) {
    struct ListNode* prevNode = l->head;
    struct ListNode* curr = l->head->next;

    while (curr != NULL && curr->item->arrivalTime <= newDog->arrivalTime) {
        prevNode = curr;
        curr = curr->next;
    }

    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->item = newDog;
    node->next = curr;
    prevNode->next = node;

    if (node->next == NULL)
        l->tail = node;

    l->length++;
}

// Deletes first dog in the list
Dog* DeleteFirstNode(List l) {
    if (l->head->next == NULL)
        return NULL;

    struct ListNode* delNode = l->head->next;
    Dog* d = delNode->item;

    l->head->next = delNode->next;

    if (delNode == l->tail)
        l->tail = l->head;

    free(delNode);
    l->length--;

    return d;
}

// Delete a specific dog
void DeleteFromList(List l, Dog* dog) {
    struct ListNode* previous = l->head;
    struct ListNode* current = l->head->next;

    while (current != NULL) {
        if (current->item == dog) {
            previous->next = current->next;
            if (current == l->tail)
                l->tail = previous;
            free(current->item);
            free(current);
            l->length = l->length - 1;
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Return list size
int ListSize(List l) {
    return l->length;
}

// Return 1 if empty
int count=0;
int IsEmptyList(List l) {
    if (l->length == 0) {
        return 1; // list is empty
    } else {
        return 0; // list is not empty
    }
}

// Return first dog
Dog* HeadOfList(List l) {
    if (l->head->next == NULL)
        return NULL;
    return l->head->next->item;
}

// Return last dog
Dog* TailOfList(List l) {

    return l->tail->item;
}

// Display dogs in list
void DisplayList(List l) {
    struct ListNode* temp = l->head->next;

    while (temp != NULL) {
        Dog* d = temp->item;

        printf("Type: ");
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
        if (d->dogGender == 1) {
            printf("Male\n");
        } else {
            printf("Female\n");
        }

        printf("Neutered: ");
        if (d->isNeutered == 1) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }

        printf("-------------------\n");

        temp = temp->next;
    }
}


// Delete list and free memory
void deleteList(List l) {
    MakeEmptyList(l);
    free(l->head);
    free(l);
}
