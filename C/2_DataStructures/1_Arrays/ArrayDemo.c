#include <stdio.h> 

#include "Array.h"
// #include "ArrayTest.h"

int main(int argc, char* argv[]) {
    Array* array = arrayInit(5);
    if (array == NULL) return 1;

    arrayPushBack(array, 100);
    arrayPushBack(array, 430);
    arrayPushBack(array, 540);

    printf("Front: %d\n", *arrayFront(array));
    printf("Back: %d\n", *arrayBack(array));
    printf("At index 1: %d\n", *arrayAt(array, 1));

    printf("Size: %lu\n", arraySize(array));
    printf("Capacity: %lu\n", arrayCapacity(array));
    printf("Is empty: %s\n", arrayEmpty(array) ? "true" : "false");

    arrayPopBack(array);
    printf("After pop back, size: %lu\n", arraySize(array));

    arrayClear(array);
    printf("After clear, size: %lu\n", arraySize(array));

    arrayDestroy(array);
    return 0;
    //runArrayTests();
}