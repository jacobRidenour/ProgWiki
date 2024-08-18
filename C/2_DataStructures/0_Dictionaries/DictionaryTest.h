#ifndef DICTIONARYTEST_H
#define DICTIONARYTEST_H

#include "Dictionary.h"

void testDictionaryInsert();
void testDictionaryGet();
void testdictionaryRemove();

void runDictionaryTests() {} // add test functions

void testDictionaryInsert() {
    Dictionary* dict = dictionaryInit();

    // empty key, empty value, empty key/value
    dictionaryInsert(dict, "", "");

    dictionaryDestroy(dict);
}


#endif /* DICTIONARYTEST_H */