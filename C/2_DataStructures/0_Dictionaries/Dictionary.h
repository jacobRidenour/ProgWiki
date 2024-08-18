#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
* Dictionary/Map
*
* implementation: hash table on a linked list
*
* structures
*  - DictNode: holds each dictionary entry (key and value)
*  - Dictionary: array of DictNodes
* 
******************************************************************************/

#define DICT_CAPACITY 16381
// constexpr int DICT_CAPACITY = 16381; // C23 onward

typedef struct DictNode {
    char* key;
    char* value;
    struct DictNode* next;
} DictNode;

typedef struct Dictionary {
    DictNode* table[DICT_CAPACITY];
} Dictionary;

unsigned long dictionaryHash(const char* key) {
    unsigned long value = 0;
    unsigned int keyLength = strlen(key);

    for(unsigned long i = 0; i < keyLength; ++i) {
        value = value * 37 + key[i];
    }

    return value % DICT_CAPACITY;
}

/******************************************************************************
* dictionaryInit
*
* parameters: none
* returns: Dictionary*
* 
* description: initializes the dictionary, setting all table indices to NULL
* 
******************************************************************************/
Dictionary* dictionaryInit() {
    Dictionary* dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        fprintf(stderr, "Failed to allocate memory for Dictionary\n");
        return NULL;
    }

    for (unsigned long i = 0; i < DICT_CAPACITY; ++i) {
        dict->table[i] = NULL;
    }

    return dict;
}

/******************************************************************************
* dictNodeInit
*
* parameters: 
*  - key : const char*
*  - value : const char*
*
* returns: DictNode*
* 
* description: initializes the dictionary, setting all table indices to NULL
* 
******************************************************************************/
DictNode* dictNodeInit(const char* key, const char* value) {
    DictNode* node = malloc(sizeof(DictNode));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate memory for DictNode\n");
        return NULL;
    }

    node->key = strdup(key); // Note: strdup calls malloc()
    node->value = strdup(value);
    node->next = NULL;
    return node;
}

/******************************************************************************
* dictionaryDestroy
*
* parameters: 
*  - dict : Dictionary*
*   
* returns: none
* 
* description: frees the memory used by the Dictionary dict.
* 
******************************************************************************/
void dictionaryDestroy(Dictionary* dict) {
    for(unsigned long i = 0; i < DICT_CAPACITY; ++i) {
        DictNode* currentNode = dict->table[i];
        while (currentNode != NULL) {
            DictNode* nextNode = currentNode->next;
            free(currentNode->key);
            free(currentNode->value);
            free(currentNode);
            currentNode = nextNode;
        }
    }
    free(dict);
}


/******************************************************************************
* dictionaryInsert
*
* parameters:
*  - dict : Dictionary*
*  - key : const char*
*  - value : const char*
*   
* returns: none
* 
* description: add a key-value pair to the Dictionary
* 
******************************************************************************/
void dictionaryInsert(Dictionary* dict, const char* key, const char* value) {
    unsigned long index = dictionaryHash(key);
    DictNode* node = dictNodeInit(key, value);

    // Insert at beginning of list
    node->next = dict->table[index];
    dict->table[index] = node;
}

/******************************************************************************
* dictionaryGet
*
* parameters: 
*  - dict : Dictionary*
*  - key : const char*
*   
* returns: char*
* 
* description: retrieves the value associated with the given key, or NULL if
*              not found.
* 
******************************************************************************/
char* dictionaryGet(Dictionary* dict, const char* key) {
    unsigned long index = dictionaryHash(key);
    DictNode* currentNode = dict->table[index];

    while (currentNode != NULL) {
        if (strcmp(currentNode->key, key) == 0) {
            return currentNode->value;
        }
        currentNode = currentNode->next;
    }
    // key not found
    return NULL;
}

/******************************************************************************
* dictionaryRemove
*
* parameters: 
*  - dict : Dictionary*
*  - key : const char*
*   
* returns: none
* 
* description: retrieves the value associated with the given key, or NULL if
*              not found.
* 
******************************************************************************/
void dictionaryRemove(Dictionary* dict, const char* key) {
    unsigned long index = dictionaryHash(key);
    DictNode* currentNode = dict->table[index];
    DictNode* previousNode = NULL;

    // find the node to remove
    while (currentNode != NULL && strcmp(currentNode->key, key) != 0) {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    // key not found
    if (currentNode == NULL) return;

    // key found, remove the node
    if (previousNode == NULL) {
        // remove first node
        dict->table[index] = currentNode->next;
    }
    else {
        // bypass the current node
        previousNode->next = currentNode->next;
    }

    free(currentNode->key);
    free(currentNode->value);
    free(currentNode);
}

// TODO new functions:
// clear() -> destroy this dict return a fresh one
// keys() -> return an array of the keys
// values() -> return an array of the values
// copy() -> create a copy of this dict
// toString() -> for each non-empty kv pair, print "key" : "value" (optional: the index)

#endif /* DICTIONARY_H */