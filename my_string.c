#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

struct my_string
{
  int size;
  int capacity;
  char* data;
};

typedef struct my_string My_string;

MY_STRING my_string_init_default(void)
{
  My_string* pString;
  pString = (My_string*)malloc(sizeof(My_string));
  if (pString != NULL)
  {
    pString->size = 0;
    pString->capacity = 7;
    pString->data = (char*)malloc(pString->capacity * sizeof(char));
    if (pString->data == NULL)
    {
      free(pString);
      return NULL;
    }
  }
  return (MY_STRING)pString;
}

void my_string_destroy(Item* pItem)
{
  My_string* pString = (My_string*)*pItem;
  free(pString->data); pString->data = NULL;
  free(*pItem); *pItem = NULL;
  return;
}

MY_STRING my_string_init_c_string(const char* c_string)
{
  My_string* pString = NULL; pString  = (My_string*)malloc(sizeof(My_string));
  int c = 1;
  int i = 0;
  while (c_string[(c - 1)] != '\0')
      c++;
  if (pString != NULL)
  {
    pString->size = c - 1;
    pString->capacity = c;
    pString->data = (char*)malloc(c * sizeof(char));
    if (pString->data == NULL)
    {
			free(pString->data);
			free(pString);
			return NULL;
    }
    while (i < (c - 1))
    {
			pString->data[i] = c_string[i];
			i++;
    }
    return (MY_STRING)pString;
  }
  return NULL;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
  My_string* pString = (My_string*)hMy_string;
  return pString->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
  My_string* pString = (My_string*)hMy_string;
  return pString->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
  My_string* lString = (My_string*)hLeft_string;
  My_string* rString = (My_string*)hRight_string;
  int i;
  
  for (i = 0; i < rString->capacity && i < lString->capacity; i++)
  {
    if (lString->data[i] < rString->data[i])
    {
			return -1;
    }
		else if (rString->data[i] < lString->data[i])
    {
			return 1;
    }
  }
  if (i == lString->capacity && i < rString->capacity)
  {
    return -1;
  }
  if (i == rString->capacity && i < lString->capacity)
  {
    return 1;
  }
  return 0;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
  My_string* pStr = (My_string*)hMy_string;
	char cHolder = fgetc(fp);
	int i, j;
  for (j = 0; j < pStr->size; j++) pStr->data[j] = 0;
  if (fp == NULL || cHolder == EOF) return FAILURE;
  while (cHolder == ' ' || cHolder == '\n')
    cHolder = fgetc(fp);

  pStr->size = 0;

  for (i = 0; cHolder != ' ' && cHolder != '\n' && cHolder != EOF; i++)
  {
    pStr->size++;
    if (pStr->size > pStr->capacity)
    {
      int z;
      char* dataHolder = pStr->data;

      pStr->data = (char*)malloc(pStr->capacity * 2  * sizeof(char));
      if (pStr->data == NULL)
      {
				free(pStr->data);
				free(dataHolder);
				pStr->size--;
				return FAILURE;
      }
      
      pStr->capacity *= 2;

      for (z = 0; z < pStr->size - 1; z++)
				pStr->data[z] = dataHolder[z];

      free(dataHolder);
    }
    pStr->data[i] = cHolder;
    cHolder = fgetc(fp);
  }
  if (cHolder != EOF && cHolder != '\0')
    fseek(fp, -1, SEEK_CUR);
  return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
  My_string* pStr = (My_string*)hMy_string;
  int i = 0;
  if (fp == NULL || pStr->size <= 0) return FAILURE;
  while (i < pStr->size)
  {
    fprintf(fp, "%c", pStr->data[i]);
    i++;
  } 
  return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
  My_string* pStr = (My_string*)hMy_string;
  pStr->size++;
  if (pStr->size > pStr->capacity)
  {
    int z;
    char* dataHolder; dataHolder = (char*)malloc(pStr->size * sizeof(char));
    if (dataHolder == NULL) { free(dataHolder); pStr->size--; return FAILURE; }

    for (z = 0; z < pStr->size - 1; z++)
      dataHolder[z] = pStr->data[z];

    pStr->data = (char*)malloc(pStr->capacity * 2  * sizeof(char));
    if (pStr->data == NULL)
    {
      free(pStr->data);
      free(dataHolder);
      pStr->size--;
      return FAILURE;
    }
      
    pStr->capacity *= 2;

    for (z = 0; z < pStr->size - 1; z++)
      pStr->data[z] = dataHolder[z];
    free(dataHolder);
  }
  pStr->data[pStr->size - 1] = item;
  return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
  My_string* pStr = (My_string*)hMy_string;
  pStr->data[pStr->size - 1] = 0;
  pStr->size--;
  return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
  My_string* pStr = (My_string*)hMy_string;
  if (index >= 0 && index < pStr->size)
    return &(pStr->data[index]);
  return NULL;
}

char* my_string_c_str(MY_STRING hMy_string)
{
  My_string* pStr = (My_string*)hMy_string;
  if (pStr->size == pStr->capacity)
  {
    char* copy = (char*)malloc((pStr->size) * sizeof(char)); int i;
    if (copy == NULL) { free(copy); return NULL; }
    for (i = 0; i < pStr->size; i++)
      copy[i] = pStr->data[i];
    pStr->capacity++;
    pStr->data = (char*)malloc((pStr->capacity) * sizeof(char));
    if (pStr->data == NULL) { free(pStr->data); return NULL; }
    for (i = 0; i < pStr->size; i++)
      pStr->data[i] = copy[i];
    free(copy);
  }
  pStr->data[pStr->size] = 0;
  return pStr->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
  My_string* a = (My_string*)hResult; My_string* b = (My_string*)hAppend; int i;
  if (a->size + b->size >= a->capacity)
  {
    char* copy = (char*)malloc((a->size) * sizeof(char));
    if (copy == NULL) { free(copy); return FAILURE; }
    for (i = 0; i < a->size; i++)
      copy[i] = a->data[i];
    a->capacity += b->size;
    a->data = (char*)malloc((a->capacity) * sizeof(char));
    if (a->data == NULL) { free(a->data); return FAILURE; }
    for (i = 0; i < a->size; i++)
      a->data[i] = copy[i];
    free(copy);
  }
  for (i = a->size; i < a->size + b->size; i++)
    a->data[i] = b->data[i - a->size];
  a->size += b->size;
  return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
  if (my_string_get_size(hMy_string) == 0)
    return TRUE;
  return FALSE;
}

void my_string_assignment(Item* pLeft, Item Right)
{
  My_string *sL = (My_string*)pLeft, *sR = (My_string*)Right;

  if ((My_string*)*pLeft == NULL)
  {
    int i;
    sL = (My_string*)malloc(sizeof(My_string));
    sL->size = sR->size;
    sL->capacity = sR->capacity;
    sL->data = (char*)malloc(sL->capacity * sizeof(char));
    for (i = 0; i < sL->capacity; i++)
      sL->data[i] = sR->data[i];
    *pLeft = (Item*)sL;
  }
  else
  {
    int i;
    sL = (My_string*)*pLeft;
    if (sL->capacity < sR->size + sL->size)
    {
      char* holder = (char*)malloc(sL->size * sizeof(char));
      for (i = 0; i < sL->size; i++)
        holder[i] = sL->data[i];

      sL->capacity = sL->size + sR->size;
      sL->data = (char*)malloc(sL->capacity * sizeof(char));

      for (i = 0; i < sL->size; i++)
	sL->data[i] = holder[i];

      free(holder);
    }
    
    for (i = sL->size; i < sL->size + sR->size; i++)
      sL->data[i] = sR->data[i - sL->size];

    sL->size += sR->size;
  }
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	My_string* pNew = (My_string*)new_key, *pCurr = (My_string*)current_word_family, *pWord = (My_string*)word;
	int i; char cHolder;

	if (65 <= guess && guess <= 90)
		guess += 32;

	if (my_string_get_capacity(new_key) != my_string_get_capacity(current_word_family))
	{
	  free(pNew->data);
	  pNew->data = NULL;
	  int a = my_string_get_capacity(current_word_family);
	  pNew->capacity = a;
	  pNew->size = pCurr->size;
	  pNew->data = (char*)malloc(a * sizeof(char));
	  if (pNew->data == NULL)
			return FAILURE;
	}

	pNew->size = pCurr->size;

	for (i = 0; i < pNew->size; i++)
	{
		cHolder = pWord->data[i];
		if (65 <= cHolder && cHolder <= 90)
			cHolder += 32;

		if (cHolder == guess)
			pNew->data[i] = cHolder;
		else pNew->data[i] = pCurr->data[i];
	}

	pNew->data[i] = '\0';
	return SUCCESS;
}
