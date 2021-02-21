#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_get_capacity_on_init_default_returns_7(char* buffer, int length);
Status test_my_string_compare(char* buffer, int length);
Status test_my_string_push_back_a(char* buffer, int length);
Status test_my_string_pop_back(char* buffer, int length);
Status test_my_string_concat(char* buffer, int length);
Status test_my_string_init_c_string(char* buffer, int length);
Status test_my_string_destroy(char* buffer, int length);
Status test_my_string_extraction(char* buffer, int length);
Status test_my_string_insertion(char* buffer, int length);
Status test_my_string_c_str(char* buffer, int length);
Status test_my_string_at(char* buffer, int length);
Status test_my_string_empty(char* buffer, int length);
void my_string_assignment(Item* pLeft, Item Right);

#endif
