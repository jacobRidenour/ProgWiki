#include <stdio.h> 

#include "Dictionary.h"
#include "DictionaryTest.h"

int main(int argc, char* argv[]) {
    Dictionary* countryCodes = dictionaryInit();
    
    dictionaryInsert(countryCodes, "Bermuda", "BM");
    dictionaryInsert(countryCodes, "Chile", "CL");
    dictionaryInsert(countryCodes, "Ghana", "GH");
    dictionaryInsert(countryCodes, "Greece", "GR");
    dictionaryInsert(countryCodes, "Tuvalu", "TV");
    dictionaryInsert(countryCodes, "United States", "US");
    dictionaryInsert(countryCodes, "Vietnam", "VN");

    printf("Country code for Tuvalu: %s\n", dictionaryGet(countryCodes, "Tuvalu"));
    printf("Removing country code for Tuvalu...\n");
    dictionaryRemove(countryCodes, "Tuvalu");
    printf("Country code for Tuvalu: %s\n", dictionaryGet(countryCodes, "Tuvalu"));

    dictionaryDestroy(countryCodes);

    runDictionaryTests();
}