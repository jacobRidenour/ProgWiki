#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/******************************************************************************
* Array
*
* implementation: wrapper around built-in arrays; compile-time "generic"
*                 with ARRAY_TYPE
*
* structures
*  - Array: holds the data, along with size and capacity
* 
******************************************************************************/

#define ARRAY_TYPE int

typedef struct Array {
    ARRAY_TYPE* data;
    unsigned long size;
    unsigned long capacity;
} Array;


/******************************************************************************
* arrayInit
*
* parameters:
*  - capacity : unsigned long
*
* returns: Array*
* 
* description: initializes the Array's memory; array data is NOT initialized
* 
******************************************************************************/
Array* arrayInit(unsigned long capacity) {
    Array* array = malloc(sizeof(Array));
    if (array == NULL) {
        fprintf(stderr, "ERROR: failed to allocate memory for struct Array.\n");
        return NULL;
    }

    array->data = malloc(capacity * sizeof(ARRAY_TYPE));
    if (array->data == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory for Array's data\n");
        free(array);
        return NULL;
    }

    array->size = 0;
    array->capacity = capacity;

    return array;
}

/******************************************************************************
* arrayDestroy
*
* parameters: 
*  - array : Array*
*   
* returns: none
* 
* description: frees the memory used by the Array array.
* 
******************************************************************************/
void arrayDestroy(Array* array) {
    if (array == NULL) {
        fprintf(stderr, "ERROR: attempted to destroy NULL Array*.\n");
        return;
    }

    free(array->data);
    free(array);
}

/******************************************************************************
* arrayAt
*
* parameters: 
*  - array : Array*
*   
* returns: int*
* 
* description: returns the ARRAY_TYPE* at the given index, with bounds checking
*              performed.
* 
******************************************************************************/
ARRAY_TYPE* arrayAt(Array* array, unsigned long index) {
    if (index >= array->size) {
        fprintf(stderr, "ERROR: array index out of bounds.\n");
        return NULL;
    }
    return &(array->data[index]);
}

/******************************************************************************
* arrayFront
*
* parameters: 
*  - array : Array*
*   
* returns: ARRAY_TYPE* 
* 
* description: returns the element at the front of Array's data
* 
******************************************************************************/
ARRAY_TYPE* arrayFront(Array* array) {
    return arrayAt(array, 0);
}

/******************************************************************************
* arrayBack
*
* parameters: 
*  - array : Array*
*   
* returns: ARRAY_TYPE*
* 
* description: returns the element at the back of Array's data
* 
******************************************************************************/
ARRAY_TYPE* arrayBack(Array* array) {
    return arrayAt(array, array->size-1);
}

/******************************************************************************
* arrayData
*
* parameters: 
*  - array : Array*
*   
* returns: ARRAY_TYPE*
* 
* description: returns the built-in array held by this Array
* 
******************************************************************************/
ARRAY_TYPE* arrayData(Array* array) {
    if (array == NULL) {
        fprintf(stderr, "ERROR: attempted to access data in NULL Array*.\n");
        return NULL;
    }

    return array->data;
}

/******************************************************************************
* arrayEmpty
*
* parameters: 
*  - array : Array*
*   
* returns: bool
* 
* description: returns whether this Array is empty based on its size
* 
******************************************************************************/
bool arrayEmpty(Array* array) {
    if (array == NULL) {
        fprintf(stderr, "ERROR: attempted to access size of NULL Array*.\n");
        return false;
    }

    return array->size == 0;
}

/******************************************************************************
* arraySize
*
* parameters: 
*  - array : Array*
*   
* returns: unsigned long
* 
* description: returns the size of the Array*
* 
******************************************************************************/
unsigned long arraySize(Array* array) {
    if (array == NULL) {
        fprintf(stderr, "ERROR: attempted to access size of NULL Array*.\n");
        return 0;
    }
    return array->size;
}

/******************************************************************************
* arrayCapacity
*
* parameters: 
*  - array : Array*
*   
* returns: unsigned long
* 
* description: returns the maximum number of elements that can be held by the
*              array.
* 
******************************************************************************/
unsigned long arrayCapacity(Array* array) {
    if (array == NULL) {
        fprintf(stderr, "ERROR: attempted to access capacity of NULL Array*.\n");
        return 0;
    }
    return array->capacity;
}

/******************************************************************************
* arrayPushBack
*
* parameters: 
*  - array : Array*
*  - value : ARRAY_TYPE
*   
* returns: bool
* 
* description: pushes element to the back of the array, returns success status
* 
******************************************************************************/
bool arrayPushBack(Array* array, ARRAY_TYPE value) {
    if (array == NULL) {
        fprintf(stderr, "ERROR: attempted to access capacity of NULL Array*.\n");
        return false;
    }
    
    if (array->size >= array->capacity) {
        fprintf(stderr, "ERROR: array is full.\n");
        return false;
    }
    array->data[array->size++] = value;
    return true;
}

/******************************************************************************
* arrayPopBack
*
* parameters: 
*  - array : Array*
*   
* returns: bool
* 
* description: pops element from the back of the array, returns success status
* 
******************************************************************************/
bool arrayPopBack(Array* array) {
    if (array->size == 0) {
        fprintf(stderr, "ERROR: array is empty.\n");
        return false;
    }
    array->size--;
    return true;
}

/******************************************************************************
* array
*
* parameters: 
*  - array : Array*
*   
* returns: none
* 
* description: 
* 
******************************************************************************/
void arrayClear(Array* array) {
    if (array == NULL) {
        fprintf(stderr, "Error in arrayClear(): array is NULL.\n");
        return;
    }
    array->size = 0;
}

#endif /* ARRAY_H */