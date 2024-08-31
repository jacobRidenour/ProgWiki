#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    unsigned long size;
    unsigned long capacity;
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

    dict->size = 0;
    dict->capacity = DICT_CAPACITY;

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
    if (dict == NULL) {
        fprintf(stderr, "Error in dictionaryDestroy(): dictionary is NULL.\n");
        return;
    }

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
    if (dict == NULL) {
        fprintf(stderr, "Error in dictionaryInsert(): dictionary is NULL.\n");
        return;
    }

    if(key == NULL || strlen(key) == 0) {
        fprintf(stderr, "Error: attempted to add empty key. Dictionary not modified.\n");
        return;
    }
    
    bool updateSize = true;
    unsigned long index = dictionaryHash(key);
    DictNode* currentNode = dict->table[index];

    while (currentNode != NULL) {
        // key already in dict, update value
        if (strcmp(currentNode->key, key) == 0) {
            free(currentNode->value);
            currentNode->value = strdup(value);
            updateSize = false;
        }
        currentNode = currentNode->next;
    }

    // key doesn't exist, create node and
    // insert at the beginning of the list
    DictNode* newNode = dictNodeInit(key, value);
    newNode->next = dict->table[index];
    dict->table[index] = newNode;
    if(updateSize) dict->size++;  
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
    if (dict == NULL) {
        fprintf(stderr, "Error in dictionaryGet(): dictionary is NULL.\n");
        return NULL;
    }

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
    if(key == NULL || strlen(key) == 0) {
        fprintf(stderr, "Error: attempted to remove empty key. Dictionary not modified.\n");
        return;
    }

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
    dict->size--;
}

/******************************************************************************
* dictionarySize
*
* parameters: 
*  - dict : Dictionary*
*
* returns: unsigned long
* 
* description: returns the number of keys that have been added to the dict.
* 
******************************************************************************/
unsigned long dictionarySize(Dictionary* dict) {
    if (dict == NULL) {
        fprintf(stderr, "Error in dictionarySize(): dictionary is NULL.\n");
        return 0;
    }

    return dict->size;
}


/******************************************************************************
* dictionaryCapacity
*
* parameters: 
*  - dict : Dictionary*
*
* returns: unsigned long
* 
* description: returns the maximum capacity of the dict.
* 
******************************************************************************/
unsigned long dictionaryCapacity(Dictionary* dict) {
    if (dict == NULL) {
        fprintf(stderr, "Error in dictionaryCapacity(): dictionary is NULL.\n");
        return 0;
    }

    return dict->capacity;
}

/******************************************************************************
* dictionaryKeys
*
* parameters: 
*  - dict : Dictionary*
*   
* returns: char** ; array containing dict's keys
* 
* description: returns an array containing all keys in the Dictionary* dict;
*              updates count param to reflect the array size
* 
******************************************************************************/
char** dictionaryKeys(Dictionary* dict) {
    if (dict == NULL) {
        fprintf(stderr, "Error in dictionaryKeys(): dictionary is NULL.\n");
        return NULL;
    }

    // make keys array
    char** keys = malloc(dict->size * sizeof(char*));
    if (keys == NULL) {
        fprintf(stderr, "Failed to allocate memory for keys array\n");
        return NULL;
    }

    // populate it 
    unsigned long keyIndex = 0;
    for (unsigned long i = 0; i < DICT_CAPACITY; ++i) {
        DictNode* currentNode = dict->table[i];
        while (currentNode != NULL) {
            keys[keyIndex++] = strdup(currentNode->key);
            currentNode = currentNode->next;
        }
    }

    return keys;
}

/******************************************************************************
* dictionaryValues
*
* parameters: 
*  - dict : Dictionary*
*   
* returns: none
* 
* description: returns an array containing all values in the Dictionary* dict;
*              updates count param to reflect the array size
* 
******************************************************************************/
char** dictionaryValues(Dictionary* dict) {
    if (dict == NULL) {
        fprintf(stderr, "Error in dictionaryKeys(): dictionary is NULL.\n");
        return NULL;
    }

    char** values = malloc(dict->size * sizeof(char*));
    if (values == NULL) {
        fprintf(stderr, "Failed to allocate memory for values array\n");
        return NULL;
    }

    unsigned long valueIndex = 0;
    for (unsigned long i = 0; i < DICT_CAPACITY; ++i) {
        DictNode* currentNode = dict->table[i];
        while (currentNode != NULL) {
            values[valueIndex++] = strdup(currentNode->value);
            currentNode = currentNode->next;
        }
    }

    return values;
}


// todo, update to only include indices with values
void dictionaryToString(Dictionary* dict) {
    for (unsigned long i = 0; i < DICT_CAPACITY; ++i) {
        DictNode* currentNode = dict->table[i];
        while (currentNode != NULL) {
            printf("\"%s\" : \"%s\"\n", currentNode->key, currentNode->value);
            currentNode = currentNode->next;
        }
    }
}


// TODO new functions:
// copy() -> create a copy of this dict

#endif /* DICTIONARY_H */