#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "my_string.h"
#include "vector.h"

struct vector  //Known type
{
	int size; // number of items the vector holds
	int capacity; //number of items the vector CAN hold
	MY_STRING* data;
};

typedef struct vector Vector;

VECTOR vector_init_default(void)
{
	Vector* pVector;
	pVector = (Vector*)malloc(sizeof(Vector));
	if (pVector != NULL)
	{
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (MY_STRING*)malloc(sizeof(MY_STRING) * pVector->capacity);
		if (pVector->data == NULL)
		{
			free(pVector);
			return NULL;
		}
	}
	return (VECTOR)pVector;
}

int vector_get_size(VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->size;
}

int vector_get_capacity(VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->capacity;
}

Status vector_push_back(VECTOR hVector, MY_STRING item)
{
  Vector* pVector = (Vector*)hVector;
  MY_STRING* pTemp;
  int i;

  if (pVector->size >= pVector->capacity)
  {
    pTemp = (MY_STRING*)malloc(2 * pVector->capacity * sizeof(MY_STRING));
    for (i = 0; i < pVector->size; i++)
      pTemp[i] = pVector->data[i];
    free(pVector->data);
    pVector->data = pTemp;
    pVector->capacity *= 2;
  }

  pVector->data[pVector->size] = item;
  pVector->size++;
  return SUCCESS;
}

MY_STRING* vector_at(VECTOR hVector, int index)
{
	Vector* pVector = (Vector*)hVector;
	if (index < 0 || index >= pVector->size)
	{
		return NULL;
	}
	return &(pVector->data[index]);
}

Status vector_pop_back(VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	if (pVector->size <= 0)
	{
		return FAILURE;
	}
	pVector->size--;
	return SUCCESS;
}

void vector_destroy(VECTOR* phVector)
{
	Vector* pVector = (Vector*)*phVector;
	int j;
	for (j = 0; j < pVector->size; j++)
		my_string_destroy((Item*)&pVector->data[j]);
	free(pVector->data);
	free(pVector); //clean up the memory footprint of the object
	*phVector = NULL;
	return;
}

MY_STRING vector_rString(VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	int strIndex;
	srand(time(0));
	strIndex = rand() % pVector->size;
	return *vector_at(hVector, strIndex);
}

VECTOR vector_copy(VECTOR oV)
{
	Vector* vOld = (Vector*)oV, *vNew = NULL;
	int i;

	vNew = (Vector*)malloc(sizeof(Vector));
	if (vNew == NULL)
		exit(1);

	vNew->size = vOld->size;
	vNew->capacity = vOld->capacity;
	vNew->data = (MY_STRING*)malloc(vNew->capacity * sizeof(MY_STRING));
	for (i = 0; i < vNew->size; i++)
	{
		vNew->data[i] = NULL;
		my_string_assignment((Item*)&vNew->data[i], (Item)vOld->data[i]);
	}
	return (VECTOR)vNew;
}
