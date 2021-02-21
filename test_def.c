#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
  MY_STRING hString = NULL;
  hString = my_string_init_default();
  if(hString == NULL)
  {
    strncpy(buffer, "test_init_default_returns_nonNULL\n"
	    "my_string_init_default returns NULL", length);
    return FAILURE;
  }
  else
  {
    my_string_destroy((Item*)&hString);
    strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
    return SUCCESS;
  }
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_default();
  if(my_string_get_size(hString) != 0)
  {
    status = FAILURE;
    printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	    "Did not receive 0 from get_size after init_default\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	    , length);
  }

  my_string_destroy(&hString);
  return status;
}

Status test_get_capacity_on_init_default_returns_7(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_default();
  if(my_string_get_capacity(hString) != 7)
  {
    status = FAILURE;
    printf("Expected a capacity of 7 but got %d\n", my_string_get_capacity(hString));
    strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n"
	    "Did not receive 7 from get_capacity after init_default\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n"
	    , length);
  }

  my_string_destroy(&hString);
  return status;
}

Status test_my_string_compare(char* buffer, int length)
{
  MY_STRING lStr = NULL, rStr = NULL;
  Status status;

  lStr = my_string_init_default();
  rStr = my_string_init_default();

  my_string_push_back(lStr, 'a');
  my_string_push_back(rStr, 'b');
  
  if(my_string_compare(lStr, rStr) != -1)
  {
    status = FAILURE;
    printf("wrong value\n");
    strncpy(buffer, "test_my_string_compare\n"
      "My_string_compare did not return the right value\n", length);
  }
  else
  {
    my_string_pop_back(lStr);
    my_string_push_back(lStr, 'b');
    my_string_push_back(lStr, 'd');
    my_string_push_back(rStr, 'a');
  
    if (my_string_compare(lStr, rStr) != 1)
    {
      status = FAILURE;
      printf("wrong value\n");
      strncpy(buffer, "test_my_string_compare\n"
	      "My_string_compare did not return the right value\n", length);
    }
    else
    {
      status = SUCCESS;
      strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	    , length);
    }
  }

  my_string_destroy(&lStr);
  my_string_destroy(&rStr);
  
  return status;
}

Status test_my_string_push_back_a(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_default();

  my_string_push_back(hString, 'a');
  if(my_string_get_size(hString) != 1 || *my_string_at(hString, 0) != 'a')
  {
    status = FAILURE;
    printf("Size didn't change or wrong char inserted\n");
    strncpy(buffer, "test_my_string_push_back_a\n"
	    "Size didn't change or wrong char inserted\n", length);
  }
    else
  {
    status = SUCCESS;
    strncpy(buffer, "test_my_string_push_back_a\n"
	    , length);
  }

  my_string_destroy(&hString);
  return status;
}

Status test_my_string_pop_back(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_default();
  
  my_string_push_back(hString, 'a');
  my_string_pop_back(hString);
  if (my_string_get_size(hString) != 0)
  {
    status = FAILURE;
    printf("Pop back failed; size did not decrease by 1\n");
    strncpy(buffer, "test_my_string_pop_back\n""Pop back failed; size did not decrease by 1", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_my_string_pop_back\n", length);
  }

  my_string_destroy(&hString);
  return status;
}

Status test_my_string_concat(char* buffer, int length)
{
  MY_STRING lStr = NULL, rStr = NULL;
  Status status, a;

  lStr = my_string_init_default();
  rStr = my_string_init_default();

  my_string_push_back(lStr, 'a');
  my_string_push_back(rStr, 'b');

  a = my_string_concat(lStr, rStr);
  if (a == FAILURE || my_string_get_size(lStr) != 2 || *my_string_at(lStr, 0) != 'a' || *my_string_at(lStr, 1) != 'b')
  {
    status = FAILURE;
    printf("concat failed\n");
    strncpy(buffer, "test_my_string_concat\n""concat failed", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_my_string_pop_back\n", length);
  }

  my_string_destroy(&lStr);
  my_string_destroy(&rStr);
  return status;
}

Status test_my_string_init_c_string(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_c_string("ab");

  if (hString == NULL || my_string_get_size(hString) != 2 || my_string_get_capacity(hString) != 3 || *my_string_at(hString, 0) != 'a' || *my_string_at(hString, 1) != 'b')
  {
    status = FAILURE;
    printf("init c string failed\n");
    strncpy(buffer, "test_my_string_init_c_string\n""init c string failed", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_my_string_init_c_string\n", length);
  }

  my_string_destroy(&hString);
  return status;
}

Status test_my_string_destroy(char* buffer, int length)
{
  MY_STRING hStr = NULL; Status status; char* check;
  hStr = my_string_init_default(); check = my_string_at(hStr, 0);
  my_string_push_back(hStr, 'a');
  my_string_destroy((Item*)&hStr);
  if (hStr != NULL || check != NULL)
  {
    status = FAILURE;
    printf("destroy failed\n");
    strncpy(buffer, "test_my_string_destroy\n" "destroy failed", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_my_string_destroy\n", length);
  }
  return status;
}

Status test_my_string_extraction(char* buffer, int length)
{
  MY_STRING hStr = NULL; FILE* fp = NULL; int works = 1; Status status;
  hStr = my_string_init_default();
  fp = fopen("dictionary.txt", "r"); if (fp == NULL) works = 0;
  else
    if (my_string_extraction(hStr, fp) == FAILURE) works = 0;
  if (!works)
  {
    status = FAILURE;
    printf("extraction failed\n");
    strncpy(buffer, "test_my_string_extraction\n" "extraction failed", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_my_string_extraction\n", length);
  }
  fclose(fp);
  my_string_destroy(&hStr);
  return status;
}

Status test_my_string_insertion(char* buffer, int length)
{
  MY_STRING hStr = NULL; Status status; FILE* fp;
  hStr = my_string_init_default();
  fp = fopen("placeholder.txt", "w");

  my_string_push_back(hStr, 'c');
  my_string_push_back(hStr, 'b');
  if (my_string_insertion(hStr, fp) == FAILURE)
  {
    status = FAILURE;
    printf("insertion failed\n");
    strncpy(buffer, "test_my_string_insertion\n" "insertion failed", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_my_string_insertion\n", length);
  }
  fclose(fp);
  my_string_destroy(&hStr);
  return status;
}

Status test_my_string_c_str(char* buffer, int length)
{
  MY_STRING hStr = NULL; Status status; char* thing;

  hStr = my_string_init_default();
  
  my_string_push_back(hStr, '1');
  thing = my_string_c_str(hStr);
  if (thing[0] != '1' || thing[1] != '\0' || my_string_get_size(hStr) != 1)
  {
    status = FAILURE;
    printf("cstr failed\n");
    strncpy(buffer, "test_my_string_c_str\n" "cstr failed", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_my_string_c_str\n", length);
  }
  my_string_destroy(&hStr);
  return status;
}

Status test_my_string_at(char* buffer, int length)
{
  MY_STRING hStr = NULL; Status status;
  hStr = my_string_init_default();
  my_string_push_back(hStr, 'a');
  my_string_push_back(hStr, 'b');
  if (*my_string_at(hStr, 1) != 'b' || *my_string_at(hStr, 0) != 'a')
  {
    status = FAILURE;
    printf("string at failed\n");
    strncpy(buffer, "test_my_string_at\n" "string at failed", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_my_string_at\n", length);
  }
  my_string_destroy(&hStr);
  return status;
}
Status test_my_string_empty(char* buffer, int length)
{
  MY_STRING hStr = NULL; Status status;
  hStr = my_string_init_default();
  my_string_push_back(hStr, 'a');
  my_string_pop_back(hStr);

  if (my_string_empty(hStr) != TRUE)
  {
    status = FAILURE;
    printf("string empty failed\n");
    strncpy(buffer, "test_my_string_empty\n" "string empty failed", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_my_string_empty\n", length);
  }
  my_string_destroy(&hStr);
  return status;
}
