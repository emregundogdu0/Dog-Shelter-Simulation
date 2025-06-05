#ifndef list
#define list

#include "Dog.h"
#include <stdio.h>
#include <stdlib.h>

// Linked list implementation will be responsible from Dog* allocations and deallocation

// A structure to represent a list node with item type Dog*
struct ListNode
{
	Dog* item;
	struct ListNode *next;
};

// A structure to keep a linked lists record.
struct ListRecord
{
	struct ListNode *head;
	struct ListNode *tail;
	int length;
};

// Typedef for list record pointer
typedef struct ListRecord *List;

/* A function to create a list, its allocates an address in
 * memory for ListRecord and creates an empty linked list with dummy
 * node by using MakeEmptyList function.*/
List CreateList(void);

// Makes a list empty with dummy node.
void MakeEmptyList(List);

// Insert a node to a specific position of the linked list
void InsertList(List, int, Dog*);

// Insert to the end of linked list.
void InsertToListEnd(List, Dog*);

//Insert to the beginning of the linked list.
void InsertToListHead(List, Dog*);

//Insert to linked list by arrival time order (Ascending, smallest arrival time at Head)
void InsertListOrderedByArrivalTime(List l, Dog* newDog);

//To delete first node from the linked list and return the address of deleted nodes item Dog
Dog* DeleteFirstNode(List);

//To Delete a dog from the list.
void DeleteFromList(List, Dog*);

//To get the length of the linked list
int ListSize(List);

//To get the Dogs address at the head of the linked list, without removing the node!
Dog* HeadOfList(List);

//To get the Dogs address at the tail of the linked list, without removing the node!
Dog* TailOfList(List);

//To check of list is empty, 1 for empty, 0 for not.
int IsEmptyList(List);

//To print the content of the linked list.
void DisplayList(List);

//To free all the nodes and delete the linked list.
void deleteList(List);

#endif