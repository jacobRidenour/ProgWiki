#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// listNodeInit -> listNodeInit

/******************************************************************************
* LinkedList
*
* implementation: doubly-linked list. pointers all the way down. compile-time
*                 "generic" with LISTNODE_TYPE.
*
* structures
*  - Array: holds the data, along with size and capacity
* 
******************************************************************************/

#define LISTNODE_TYPE int

typedef struct ListNode {
    LISTNODE_TYPE data;
    struct ListNode* prev;
    struct ListNode* next;
} ListNode;

/******************************************************************************
* listNodeInit
*
* parameters:
*  - data : LISTNODE_TYPE
*
* returns: ListNode*
* 
* description: initializes a ListNode with data
* 
******************************************************************************/
ListNode* listNodeInit(LISTNODE_TYPE data) {
    ListNode* node = malloc(sizeof(ListNode));
    if (node == NULL) {
        fprintf(stderr, "ERROR: failed to allocate memory for ListNode.\n");
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

typedef struct LinkedList {
    ListNode* head;
    ListNode* tail;
    unsigned long size;
} LinkedList;

/******************************************************************************
* linkedListInit
*
* parameters: none
*
* returns: LinkedList*
* 
* description: initializes memory for the LinkedList
* 
******************************************************************************/
LinkedList* linkedListInit() {
    LinkedList* list = malloc(sizeof(LinkedList));
    if (list == NULL) {
        fprintf(stderr, "ERROR: failed to allocate memory for LinkedList.\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

/******************************************************************************
* linkedListDestroy
*
* parameters:
*  - list : LinkedList*
*
* returns: none
* 
* description: frees the heap memory associated with the LinkedList*
* 
******************************************************************************/
void linkedListDestroy(LinkedList* list) {
    if (list == NULL) {
        fprintf(stderr, "ERROR: attempted to destroy NULL LinkedList.\n");
        return;
    }

    ListNode* currentNode = list->head;
    while (currentNode != NULL) {
        ListNode* nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }

    free(list);
}

/******************************************************************************
* linkedListFront
*
* parameters:
*  - list : LinkedList*
*
* returns: LISTNODE_TYPE
* 
* description: returns the data held at the front of the LinkedList
* 
******************************************************************************/
LISTNODE_TYPE* linkedListFront(LinkedList* list) {
    if (list->head == NULL) {
        fprintf(stderr, "Error: list is empty\n");
        return NULL;
    }

    return &(list->head->data);
}

/******************************************************************************
* linkedListBack
*
* parameters:
*  - list : LinkedList*
*
* returns: LISTNODE_TYPE
* 
* description: returns the data held at the back of the LinkedList
* 
******************************************************************************/
LISTNODE_TYPE* linkedListBack(LinkedList* list) {
    if (list->tail == NULL) {
        fprintf(stderr, "Error: list is empty\n");
        return NULL;
    }

    return &(list->tail->data);
}

/******************************************************************************
* linkedListAt
*
* parameters:
*  - list : LinkedList*
*
* returns: LISTNODE_TYPE
* 
* description: returns the data held at the given index of the LinkedList
* 
******************************************************************************/
LISTNODE_TYPE* linkedListAt(LinkedList* list, unsigned long index) {
    if (index >= list->size) {
        fprintf(stderr, "Error: index out of bounds\n");
        return NULL;
    }

    ListNode* currentNode = list->head;
    for (unsigned long i = 0; i < index; ++i) {
        currentNode = currentNode->next;
    }

    return &(currentNode->data);
}

/******************************************************************************
* linkedListEmpty
*
* parameters:
*  - list : LinkedList*
*
* returns: bool
* 
* description: returns whether the list's size is 0
* 
******************************************************************************/
bool linkedListEmpty(LinkedList* list) {
    if (list == NULL) {
        fprintf(stderr, "ERROR: attempted to access size of NULL LinkedList*.\n");
        return false;
    }

    return list->size == 0;
}

/******************************************************************************
* linkedListSize
*
* parameters:
*  - list : LinkedList*
*
* returns: unsigned long
* 
* description: returns the size of the list
* 
******************************************************************************/
unsigned long linkedListSize(LinkedList* list) {
    if (list == NULL) {
        fprintf(stderr, "ERROR: attempted to access size of NULL LinkedList*.\n");
        return false;
    }

    return list->size;
}


/******************************************************************************
* linkedListPushBack
*
* parameters:
*  - list : LinkedList*
*
* returns: bool ; success status
* 
* description: adds a node containing data to the back of the list
* 
******************************************************************************/
bool linkedListPushBack(LinkedList* list, LISTNODE_TYPE data) {
    if (list == NULL) {
        fprintf(stderr, "ERROR: attempted to add element to NULL LinkedList*.\n");
        return false;
    }
    
    ListNode* newNode = listNodeInit(data);
    if (newNode == NULL) {
        return false;
    }

    if (list->tail == NULL) {
        list->head = list->tail = newNode;
    }
    else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->size++;
    return true;
}

/******************************************************************************
* linkedListPushFront
*
* parameters:
*  - list : LinkedList*
*
* returns: bool ; success status
* 
* description: adds a node containing data to the front of the list
* 
******************************************************************************/
bool linkedListPushFront(LinkedList* list, LISTNODE_TYPE data) {
    if (list == NULL) {
        fprintf(stderr, "ERROR: attempted to add element to NULL LinkedList*.\n");
        return false;
    }

    ListNode* newNode = listNodeInit(data);
    if (newNode == NULL) {
        return false;
    }

    if (list->head == NULL) {
        list->head = list->tail = newNode;
    }
    else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }

    list->size++;
    return true;
}

/******************************************************************************
* linkedListPopBack
*
* parameters:
*  - list : LinkedList*
*
* returns: bool ; success status
* 
* description: removes the node at the back of the list
* 
******************************************************************************/
bool linkedListPopBack(LinkedList* list) {
    if (list->tail == NULL) {
        fprintf(stderr, "ERROR: list is empty.\n");
        return false;
    }

    ListNode* nodeToRemove = list->tail;
    list->tail = nodeToRemove->prev;

    if (list->tail != NULL) {
        list->tail->next = NULL;
    }
    else {
        list->head = NULL;
    }

    free(nodeToRemove);
    list->size--;
    return true;
}

/******************************************************************************
* linkedListPopFront
*
* parameters:
*  - list : LinkedList*
*
* returns: bool ; success status
* 
* description: removes the node at the front of the list
* 
******************************************************************************/
bool linkedListPopFront(LinkedList* list) {
    if (list->head == NULL) {
        fprintf(stderr, "ERROR: list is empty.\n");
        return false;
    }

    ListNode* nodeToRemove = list->head;
    list->head = nodeToRemove->next;

    if (list->head != NULL) {
        list->head->prev = NULL;
    }
    else {
        list->tail = NULL;
    }

    free(nodeToRemove);
    list->size--;
    return true;
}

/******************************************************************************
* linkedListClear
*
* parameters:
*  - list : LinkedList*
*
* returns: none 
* 
* description: removes all nodes from the list
* 
******************************************************************************/
void linkedListClear(LinkedList* list) {
    while (!linkedListEmpty(list)) {
        linkedListPopFront(list);
    }
}

/******************************************************************************
* linkedListToString
*
* parameters:
*  - list : LinkedList*
*
* returns: none
* 
* description: prints data held by each node in list, one per line
* 
******************************************************************************/
void linkedListToString(LinkedList* list) {
    ListNode* currentNode = list->head;
    printf("[ ");
    while (currentNode != NULL) {
        printf("%d", currentNode->data);
        if (currentNode->next != NULL) {
            printf(", ");
        }
        currentNode = currentNode->next;
    }
    printf(" ]\n");
}


// method stub

/******************************************************************************
* linkedList
*
* parameters:
*  - list : LinkedList*
*
* returns: type
* 
* description: 
* 
******************************************************************************/

#endif /* LINKEDLIST_H */