#ifndef DICTIONARYTEST_H
#define DICTIONARYTEST_H

#include "Dictionary.h"
#include "TestsSummary.h"

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
    TestsSummaryPrintHeader("Dictionary");

    testDictionaryInsert();
    testDictionaryRemove();
    testDictionaryGet();
    testDictionaryKeys();
    testDictionaryValues();
    testDictionaryToString();

    TestsSummaryPrintFooter("Dictionary");
}

void testDictionaryInsert() {
    Dictionary* dict = SetUp();
    int successes = 0, failures = 0;

    // Insert single key-value pair, retrieve the value associated with the key
    dictionaryInsert(dict, "testKey1", "testValue1");
    char* value1 = dictionaryGet(dict, "testKey1");
    if (value1 == NULL || strcmp(value1, "testValue1") != 0) {
        printf("FAILED: testDictionaryInsert: expected 'testValue1' but got '%s'\n", value1);
        failures++;
    }
    else successes++;

    // Insert the same key as we already did, but with a different value
    dictionaryInsert(dict, "testKey1", "testValue2");
    char* value2 = dictionaryGet(dict, "testKey1");
    if (value2 == NULL || strcmp(value2, "testValue2") != 0) {
        printf("FAILED: testDictionaryInsert: expected 'testValue2' but got '%s'\n", value2);
        failures++;
    }
    else successes++;

    // Insert multiple key-value pairs
    dictionaryInsert(dict, "testKey2", "testValue3");
    dictionaryInsert(dict, "testKey3", "testValue4");
    char* value3 = dictionaryGet(dict, "testKey2");
    char* value4 = dictionaryGet(dict, "testKey3");

    if (value3 == NULL || strcmp(value3, "testValue3") != 0) {
        printf("FAILED: testDictionaryInsert: expected 'testValue3' but got '%s'\n", value3);
        failures++;
    }
    else successes++;

    if (value4 == NULL || strcmp(value4, "testValue4") != 0) {
        printf("FAILED: testDictionaryInsert: expected 'testValue4' but got '%s'\n", value4);
        failures++;
    }
    else successes++;

    TestsSummaryPrintResults("DictionaryInsert", successes, failures);
    TearDown(dict);
}

void testDictionaryRemove() {
    Dictionary* dict = SetUp();
    int successes = 0, failures = 0;

    // Remove a key that is in the dict
    dictionaryInsert(dict, "testKey1", "testValue1");
    dictionaryRemove(dict, "testKey1");
    char* value1 = dictionaryGet(dict, "testKey1");
    if (value1 != NULL) {
        printf("FAILED: testDictionaryRemove: expected NULL but got '%s'\n", value1);
        failures++;
    }
    else successes++;

    // Remove a key that isn't in the dict
    dictionaryRemove(dict, "nonExistentKey"); 
    successes++;

    // Remove a key in the middle of a chain
    dictionaryInsert(dict, "testKey1", "testValue1");
    dictionaryInsert(dict, "testKey2", "testValue2");
    dictionaryInsert(dict, "testKey3", "testValue3");

    dictionaryRemove(dict, "testKey2");
    char* value2 = dictionaryGet(dict, "testKey2");
    if (value2 != NULL) {
        printf("FAILED: testDictionaryRemove: expected NULL but got '%s'\n", value2);
        failures++;
    }
    else successes++;

    TestsSummaryPrintResults("DictionaryRemove", successes, failures);
    TearDown(dict);
}

void testDictionaryGet() {
    Dictionary* dict = SetUp();
    int successes = 0, failures = 0;

    // get value - key exists
    dictionaryInsert(dict, "testKey1", "testValue1");
    char* value1 = dictionaryGet(dict, "testKey1");
    if (value1 == NULL || strcmp(value1, "testValue1") != 0) {
        printf("FAILED: testDictionaryGet: expected 'testValue1' but got '%s'\n", value1);
        failures++;
    }
    else successes++;

    // get value - key doesn't exist
    char* value2 = dictionaryGet(dict, "nonExistentKey");
    if (value2 != NULL) {
        printf("FAILED: testDictionaryGet: expected NULL but got '%s'\n", value2);
        failures++;
    }
    else successes++;

    TestsSummaryPrintResults("DictionaryGet", successes, failures);
    TearDown(dict);
}

void testDictionaryKeys() {
    Dictionary* dict = SetUp();
    int successes = 0, failures = 0;

    dictionaryInsert(dict, "testKey1", "testValue1");
    dictionaryInsert(dict, "testKey2", "testValue2");
    dictionaryInsert(dict, "testKey3", "testValue3");

    // try getting all keys
    char** keys = dictionaryKeys(dict);

    if (dict->size != 3) {
        printf("FAILED: testDictionaryKeys: expected 3 keys but got %lu\n", dict->size);
        failures++;
    }
    else successes++;

    // check that all the keys are present
    bool found[3] = {false, false, false};

    for (unsigned long i = 0; i < dict->size; ++i) {
        if (strcmp(keys[i], "testKey1") == 0) {
            found[0] = true;
        }
        else if (strcmp(keys[i], "testKey2") == 0) {
            found[1] = true;
        }
        else if (strcmp(keys[i], "testKey3") == 0) {
            found[2] = true;
        }
        else {
            printf("FAILED: testDictionaryKeys: unexpected key '%s'\n", keys[i]);
        }
        free(keys[i]);
    }
    free(keys);

    if (!found[0] || !found[1] || !found[2]) {
        printf("FAILED: testDictionaryKeys: not all expected keys were found\n");
        failures++;
    }
    else successes++;

    TestsSummaryPrintResults("DictionaryKeys", successes, failures);
    TearDown(dict);
}

void testDictionaryValues() {
    Dictionary* dict = SetUp();
    int successes = 0, failures = 0;

    dictionaryInsert(dict, "testKey1", "testValue1");
    dictionaryInsert(dict, "testKey2", "testValue2");
    dictionaryInsert(dict, "testKey3", "testValue3");

    char** values = dictionaryValues(dict);

    if (dict->size != 3) {
        printf("FAILED: testDictionaryValues: expected 3 values but got %lu\n", dict->size);
        failures++;
    }
    else successes++;

    // check that all the values are present
    bool found[3] = {false, false, false};

    for (unsigned long i = 0; i < dict->size; ++i) {
        if (strcmp(values[i], "testValue1") == 0) {
            found[0] = true;
        }
        else if (strcmp(values[i], "testValue2") == 0) {
            found[1] = true;
        }
        else if (strcmp(values[i], "testValue3") == 0) {
            found[2] = true;
        }
        else {
            printf("FAILED: testDictionaryValues: unexpected value '%s'\n", values[i]);
        }
        free(values[i]);
    }
    free(values);

    if (!found[0] || !found[1] || !found[2]) {
        printf("FAILED: testDictionaryValues: not all expected values were found\n");
        failures++;
    }
    else successes++;

    TearDown(dict);
}

void testDictionaryToString() {
    Dictionary* dict = SetUp();
    int successes = 0, failures = 0;
    
    dictionaryInsert(dict, "testKey1", "testValue1");
    dictionaryInsert(dict, "testKey2", "testValue2");
    dictionaryInsert(dict, "testKey3", "testValue3");

    FILE* tempFile = tmpfile();
    if (tempFile == NULL) {
        fprintf(stderr, "ERROR: Failed to create temp file for test\n");
        TearDown(dict);
        return;
    }

    FILE* stdOut = stdout;
    stdout = tempFile;

    dictionaryToString(dict);

    // Reset stdout
    fflush(stdout);
    stdout = stdOut;

    // Move to beginning of file, count lines
    rewind(tempFile);
    int numLines = 0;
    char buffer[4096];

    // Count the number of lines in the output
    while (fgets(buffer, sizeof(buffer), tempFile) != NULL) numLines++;

    fclose(tempFile);

    if (numLines != 3) {
        printf("FAILED: testDictionaryToString: expected 3 lines but got %d\n", numLines);
        failures++;
    }
    else successes++;

    TestsSummaryPrintResults("DictionaryToString", successes, failures);
    TearDown(dict);
}


#endif /* DICTIONARYTEST_H */