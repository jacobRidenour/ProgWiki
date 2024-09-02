#include <stdio.h> 

#include "LinkedList.h"
// #include "LinkedListTest.h" // TODO

int main() {
    LinkedList* list = linkedListInit();
    if (list == NULL) return 1;

    linkedListPushBack(list, 10); // 1
    linkedListPushBack(list, 20); // 2
    linkedListPushBack(list, 30); // 3
    linkedListPushFront(list, 5); // 0

    linkedListToString(list);

    // Non-random access.. not ideal
    int* dataAtIndex = linkedListAt(list, 2);
    if (dataAtIndex != NULL) {
        printf("Element at index 2: %d\n", *dataAtIndex);
    }

    linkedListPopBack(list);
    linkedListPopFront(list);

    linkedListToString(list);

    linkedListClear(list);
    linkedListToString(list);

    linkedListDestroy(list);
}