#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "vector.h"
#include "node.h"

struct node;

typedef struct node Node;

struct node
{
	MY_STRING key;
	VECTOR family;
	Node *left, *right;
	int height;
};

int max (int a, int b)
{
  if (a > b)
    return a;
  return b;
}

int height(Node* pNode)
{
	if (pNode == NULL)
		return 0;
	return pNode->height;
}

Node* rightRotate(Node* pNode)
{
	Node* temp = pNode->left;
	Node* tempA = temp->right;
	temp->right = pNode;
	pNode->left = tempA;
	pNode->height = max(height(pNode->left), height(pNode->right)) + 1;
	temp->height = max(height(temp->left), height(temp->right)) + 1;
	return temp;
}

Node* leftRotate(Node* pNode)
{
	Node* temp = pNode->right;
	Node* tempA = temp->left;
	temp->left = pNode;
	pNode->right = tempA;
	pNode->height = max(height(pNode->left), height(pNode->right)) + 1;
	temp->height = max(height(temp->left), height(temp->right)) + 1;
	return temp;
}

Node* node_init_default(MY_STRING phStr, MY_STRING oKey)
{
        Node* pNode = NULL;
	pNode = (Node*)malloc(sizeof(Node));
	if (pNode == NULL)
	  exit(1);
	pNode->family = vector_init_default(); vector_push_back(pNode->family, phStr);
	pNode->key = oKey;
	pNode->left = NULL; pNode->right = NULL;
	pNode->height = 1;
	return (NODE)pNode;
}

int getBalance(Node* N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

NODE node_insert(NODE phNode, MY_STRING phStr, MY_STRING oKey)
{
  Node* pNode = (Node*)phNode;

  if (pNode == NULL)
    return (NODE)node_init_default(phStr, oKey);
  else if (my_string_compare(oKey, pNode->key) < 0)
    pNode->left = (Node*)node_insert((NODE)pNode->left, phStr, oKey);
  else if (my_string_compare(oKey, pNode->key) > 0)
    pNode->right = (Node*)node_insert((NODE)pNode->right, phStr, oKey);
  else
  {
    my_string_destroy(&oKey);
    vector_push_back(pNode->family, phStr);
  }

  pNode->height = 1 + max(height(pNode->left),
			  height(pNode->right));

  int balance = getBalance(pNode);
  if (balance > 1 && my_string_compare(oKey, pNode->left->key) < 0)
    return (NODE)rightRotate(pNode);
  if (balance < -1 && my_string_compare(oKey, pNode->right->key) > 0)
    return (NODE)leftRotate(pNode);
  if (balance > 1 && my_string_compare(oKey, pNode->left->key) > 0)
  {
    pNode->left = leftRotate(pNode->left);
    return (NODE)rightRotate(pNode);
  }

  if (balance < -1 && my_string_compare(oKey, pNode->right->key) < 0)
  {
    pNode->right = rightRotate(pNode->right);
    return (NODE)leftRotate(pNode);
  }

  return (NODE)pNode;
}

NODE biggest_node(NODE phNode)
{
  Node* pNode = (Node*)phNode;
  Node* biggestNode = pNode;
  if (pNode->left != NULL)
    {
      Node* left = (Node*)biggest_node((NODE)pNode->left);
      if (vector_get_size(left->family) > vector_get_size(biggestNode->family))
	biggestNode = left;
    }
  if (pNode->right != NULL)
    {
      Node* right = (Node*)biggest_node((NODE)pNode->right);
      if (vector_get_size(right->family) > vector_get_size(biggestNode->family))
	biggestNode = right;
    }
  return (NODE)biggestNode;
}

MY_STRING node_get_key(NODE phNode)
{
  Node* pNode = (Node*)phNode;
  return pNode->key;
}

VECTOR node_get_family(NODE phNode)
{
  Node* pNode = (Node*)phNode;
  return pNode->family;
}

void node_destroyAll(NODE* phNode)
{
  Node* pNode = (Node*)*phNode;
  if (pNode->left != NULL)
    node_destroyAll((NODE*)&pNode->left);
  if (pNode->right != NULL)
    node_destroyAll((NODE*)&pNode->right);
  vector_destroy(&pNode->family);
  my_string_destroy((Item*)&pNode->key);
  free(*phNode); *phNode = NULL;
}
