#ifndef INC_13LAB_TREE_FUNCTIONS_H
#define INC_13LAB_TREE_FUNCTIONS_H
#include "validators.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
} Node;

void in_order_show(Node* root);
Node* insert(Node* root, int value);
Node* createNode(int value);
void reversed_in_order_show(Node* root);
void as_tree_print(Node* root, int space, int isRight);
Node* search_node(Node* root, int value);
Node* delete(Node* root, int value);
void clean_tree(Node* root);
void get_tree_size(Node* root, int* size);
void tree_to_vine(Node* pseudo_root);
void compress(Node* pseudo_root, int count);
Node* balance_tree(Node* root);

#endif