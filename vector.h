#ifndef VECTOR_H
#define VECTOR_H
#include "status.h"
#include "my_string.h"

typedef void* VECTOR;

VECTOR vector_init_default(void);

int vector_get_size(VECTOR hVector);
int vector_get_capacity(VECTOR hVector);

Status vector_push_back(VECTOR hVector, MY_STRING item);

Status vector_pop_back(VECTOR hVector);

//shrink to fit

MY_STRING* vector_at(VECTOR hVector, int index);

//set the capacity??

void vector_destroy(VECTOR* phVector);

MY_STRING vector_rString(VECTOR hVector);

VECTOR vector_copy(VECTOR oV);

#endif