#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include "my_string.h"

typedef void* NODE;

//NODE node_init_default(MY_STRING phStr, MY_STRING oKey);

NODE node_insert(NODE phNode, MY_STRING phStr, MY_STRING oKey);

VECTOR key_lookup(NODE phNode, MY_STRING oKey);

VECTOR getLargest(NODE phNode);

void node_checkDown(NODE phNode);

void node_destroyAll(NODE* phNode);

NODE biggest_node(NODE phNode);

MY_STRING node_get_key(NODE phNode);

VECTOR node_get_family(NODE phNode);

#endif