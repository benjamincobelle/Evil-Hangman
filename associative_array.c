#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "status.h"
#include "my_string.h"
#include "vector.h"
#include "node.h"
#include "associative_array.h"

struct associative_array
{
	NODE key;
	MY_STRING currentKey;
	int size;
};

typedef struct associative_array associativeArray;

ASSOCIATIVE_ARRAY assoc_init_default(int size)
{
	associativeArray* pArray = NULL;
	char* currKeyInit = (char*)malloc((size + 1) * sizeof(char));
	int i;

	pArray = (associativeArray*)malloc(sizeof(associativeArray));

	for (i = 0; i < size; i++)
		currKeyInit[i] = '-';
	currKeyInit[size] = '\0';

	if (pArray == NULL)
		exit(1);

	pArray->key = NULL;
	pArray->currentKey = my_string_init_c_string(currKeyInit);
	pArray->size = size;

	free(currKeyInit);

	return (ASSOCIATIVE_ARRAY)pArray;
}

void addWord(ASSOCIATIVE_ARRAY phArr, MY_STRING pStr, char guess)
{
	associativeArray* pArr = (associativeArray*)phArr;
	MY_STRING nKey = my_string_init_default();
	MY_STRING cpStr = NULL;
	my_string_assignment(&cpStr, pStr);
	get_word_key_value(pArr->currentKey, nKey, pStr, guess);
	pArr->key = node_insert(pArr->key, cpStr, nKey);
}

VECTOR key_update(ASSOCIATIVE_ARRAY phArr, int* changed, VECTOR* oldList)
{
	associativeArray* pArr = (associativeArray*)phArr;
	NODE temp = biggest_node(pArr->key);
	VECTOR newList = vector_copy(node_get_family(temp));
	MY_STRING tempKey = NULL;
	*changed = 1;

	my_string_assignment(&tempKey, node_get_key(temp));
	
	if (!my_string_compare(tempKey, pArr->currentKey))
		*changed = 0;

	my_string_destroy((Item*)&pArr->currentKey);

	pArr->currentKey = tempKey;

	node_destroyAll(&pArr->key);
	vector_destroy(oldList);
	return newList;
}

VECTOR keyLookup(MY_STRING key)
{
	VECTOR* rightVect = NULL;

	//find key

	return *rightVect;
}

MY_STRING getCurrentKey(ASSOCIATIVE_ARRAY phArray)
{
	associativeArray* pArray = (associativeArray*)phArray;
	return pArray->currentKey;
}

void assoc_destroy(ASSOCIATIVE_ARRAY* phArr)
{
	associativeArray* pArr = (associativeArray*)*phArr;
	if (pArr->key != NULL)
		node_destroyAll(&pArr->key);
	my_string_destroy((Item*)&pArr->currentKey);
	free(pArr);
	*phArr = NULL;
}
