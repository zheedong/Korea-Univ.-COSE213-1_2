#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct treeNode
{
	int data;
	struct treeNode* left;
	struct treeNode* right;
} TREE_NODE;

typedef struct
{
	int count;
	TREE_NODE* root;
} BST_TREE;

BST_TREE* bstCreate();
void bstDestroy(BST_TREE* tree);
static void _bstDestroy(TREE_NODE* root);

bool bstInsert(BST_TREE* tree, int data);
TREE_NODE* _bstAdd(TREE_NODE* root, TREE_NODE* newNode);
bool bstDelete(BST_TREE* tree, int key);
TREE_NODE* _bstDel(TREE_NODE* root, int data, bool* success);
TREE_NODE* bstSearch(BST_TREE* tree, int key);
TREE_NODE* _bstFind(TREE_NODE* root, int key);

bool bstEmpty(BST_TREE* tree);
int bstCount(BST_TREE* tree);
