#ifndef ARRAYTEST_H
#define ARRAYTEST_H

#include "Array.h"
#include "TestsSummary.h"

/* Testing functions **********************************************************/
void testArrayPushBack();
void testArrayPopBack();
void testArrayClear();
void testArrayFrontBack();
void testArraySizeCapacity();
/* End testing functions ******************************************************/

/* Test setup/teardown functions **********************************************/
Array* SetUp(unsigned long capacity) {
    return arrayInit(capacity);
}

void TearDown(Array* array) {
    arrayDestroy(array);
}
/* End test setup/teardown functions ******************************************/

// These tests assume ARRAY_TYPE is int
void runArrayTests() {
    TestsSummaryPrintHeader("Array");

    testArrayPushBack();
    testArrayPopBack();
    testArrayClear();
    testArrayFrontBack();
    testArraySizeCapacity();

    TestsSummaryPrintFooter("Array");
}

void testArrayPushBack() {
    Array* array = SetUp(3);
    int successes = 0, failures = 0;

    arrayPushBack(array, 10);
    arrayPushBack(array, 20);
    arrayPushBack(array, 30);

    if (*arrayAt(array, 0) != 10) {
        printf("FAILED: testArrayPushBack: expected 10 but got %d\n", *arrayAt(array, 0));
        failures++;
    }
    else successes++;

    if (*arrayAt(array, 1) != 20) {
        printf("FAILED: testArrayPushBack: expected 20 but got %d\n", *arrayAt(array, 1));
        failures++;
    }
    else successes++;

    if (*arrayAt(array, 2) != 30) {
        printf("FAILED: testArrayPushBack: expected 30 but got %d\n", *arrayAt(array, 2));
        failures++;
    }
    else successes++;

    // Test pushing back more than capacity
    bool pushResult = arrayPushBack(array, 40);
    if (pushResult) {
        printf("Array's size: %lu", array->size);
        printf("Array's capacity: %lu", array->capacity);
        printf("FAILED: testArrayPushBack: incorrectly allowed push back beyond capacity\n");
        failures++;
    }
    else successes++;

    TestsSummaryPrintResults("ArrayPushBack", successes, failures);
    TearDown(array);
}

void testArrayPopBack() {
    Array* array = SetUp(5);
    int successes = 0, failures = 0;

    arrayPushBack(array, 10);
    arrayPushBack(array, 20);

    // usual case
    arrayPopBack(array);
    if (arraySize(array) != 1 || *arrayBack(array) != 10) {
        printf("FAILED: testArrayPopBack: expected size 1 and back element 10, but got \
                size %lu and back element %d\n", arraySize(array), *arrayBack(array));
        failures++;
    }
    else successes++;

    // array should be empty after this
    arrayPopBack(array);
    if (arraySize(array) != 0) {
        printf("FAILED: testArrayPopBack: expected size 0 after popping all elements, but got size %lu\n",
               arraySize(array));
        failures++;
    }
    else successes++;

    // popping from an empty array
    bool popResult = arrayPopBack(array);
    if (popResult) {
        printf("FAILED: testArrayPopBack: incorrectly allowed pop from empty array\n");
        failures++;
    }
    else successes++;

    TestsSummaryPrintResults("ArrayPopBack", successes, failures);
    TearDown(array);
}

void testArrayClear() {
    Array* array = SetUp(5);
    int successes = 0, failures = 0;

    arrayPushBack(array, 10);
    arrayPushBack(array, 20);

    arrayClear(array);

    if (arraySize(array) != 0) {
        printf("FAILED: testArrayClear: expected size 0 after clear, but got size %lu\n", arraySize(array));
        failures++;
    }
    else successes++;

    if (!arrayEmpty(array)) {
        printf("FAILED: testArrayClear: expected array to be empty after clear\n");
        failures++;
    }
    else successes++;

    TestsSummaryPrintResults("ArrayClear", successes, failures);
    TearDown(array);
}

void testArrayFrontBack() {
    Array* array = SetUp(5);
    int successes = 0, failures = 0;

    arrayPushBack(array, 10);
    arrayPushBack(array, 20);
    arrayPushBack(array, 30);

    if (*arrayFront(array) != 10) {
        printf("FAILED: testArrayFrontBack: expected front 10 but got %d\n", *arrayFront(array));
        failures++;
    }
    else successes++;

    if (*arrayBack(array) != 30) {
        printf("FAILED: testArrayFrontBack: expected back 30 but got %d\n", *arrayBack(array));
        failures++;
    }
    else successes++;

    TestsSummaryPrintResults("ArrayFrontBack", successes, failures);
    TearDown(array);
}

void testArraySizeCapacity() {
    Array* array = SetUp(5);
    int successes = 0, failures = 0;

    if (arraySize(array) != 0) {
        printf("FAILED: testArraySizeCapacity: expected initial size 0 but got %lu\n", arraySize(array));
        failures++;
    }
    else successes++;

    if (arrayCapacity(array) != 5) {
        printf("FAILED: testArraySizeCapacity: expected capacity 5 but got %lu\n", arrayCapacity(array));
        failures++;
    }
    else successes++;

    arrayPushBack(array, 10);
    arrayPushBack(array, 20);

    if (arraySize(array) != 2) {
        printf("FAILED: testArraySizeCapacity: expected size 2 after adding elements but got %lu\n", arraySize(array));
        failures++;
    }
    else successes++;

    TestsSummaryPrintResults("ArraySizeCapacity", successes, failures);
    TearDown(array);
}


#endif /* ARRAYTEST_H */