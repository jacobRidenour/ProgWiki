#ifndef DICTIONARYTEST_H
#define DICTIONARYTEST_H

#include "Dictionary.h"
#include "__tests/PrintTestResults.h"

/* Testing functions **********************************************************/
void testDictionaryInsert();
void testDictionaryRemove();
void testDictionaryGet();
void testDictionaryKeys();
void testDictionaryValues();
void testDictionaryToString();
/* End testing functions ******************************************************/

/* Test setup/teardown functions **********************************************/
Dictionary* SetUp() {
    return dictionaryInit();
}

void TearDown(Dictionary* dict) {
    dictionaryDestroy(dict);
}
/* End test setup/teardown functions ******************************************/


void runDictionaryTests() {
    Dictionary* dict = SetUp();
    testDictionaryInsert();
    testDictionaryRemove();
    testDictionaryGet();
    testDictionaryKeys();
    testDictionaryValues();
    testDictionaryToString();
    TearDown(dict);
}

void testDictionaryInsert() {
    Dictionary* dict = SetUp();

    // Insert single key-value pair, retrieve the value associated with the key
    dictionaryInsert(dict, "testKey1", "testValue1");
    char* value1 = dictionaryGet(dict, "testKey1");
    if (value1 == NULL || strcmp(value1, "testValue1") != 0) {
        printf("FAILED: testDictionaryInsert: expected 'testValue1' but got '%s'\n", value1);
    }

    // Test inserting a duplicate key
    dictionaryInsert(dict, "testKey1", "testValue2");
    char* value2 = dictionaryGet(dict, "testKey1");
    if (value2 == NULL || strcmp(value2, "testValue2") != 0) {
        printf("FAILED: testDictionaryInsert: expected 'testValue2' but got '%s'\n", value2);
    }

    // Test inserting multiple key-value pairs
    dictionaryInsert(dict, "testKey2", "testValue3");
    dictionaryInsert(dict, "testKey3", "testValue4");
    char* value3 = dictionaryGet(dict, "testKey2");
    char* value4 = dictionaryGet(dict, "testKey3");

    if (value3 == NULL || strcmp(value3, "testValue3") != 0) {
        printf("testDictionaryInsert failed: expected 'testValue3' but got '%s'\n", value3);
    }

    if (value4 == NULL || strcmp(value4, "testValue4") != 0) {
        printf("testDictionaryInsert failed: expected 'testValue4' but got '%s'\n", value4);
    }



    TearDown(dict);
}


#endif /* DICTIONARYTEST_H */