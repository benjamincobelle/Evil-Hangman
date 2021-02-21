#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H

#include <stdio.h>
#include "my_string.h"
#include "vector.h"
#include "status.h"


typedef void* ASSOCIATIVE_ARRAY;

ASSOCIATIVE_ARRAY assoc_init_default(int size);

void addWord(ASSOCIATIVE_ARRAY phArr, MY_STRING pStr, char guess);

VECTOR keyLookup(MY_STRING key);

void assoc_destroy(ASSOCIATIVE_ARRAY* phArr);

VECTOR key_update(ASSOCIATIVE_ARRAY phArr, int* changed, VECTOR* oldList);

MY_STRING getCurrentKey(ASSOCIATIVE_ARRAY phArray);

#endif
