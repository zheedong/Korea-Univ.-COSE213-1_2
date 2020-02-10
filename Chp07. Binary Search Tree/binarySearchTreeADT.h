#pragma once
#include <stdio.h>
#include <stdbool.h>
#define Element int

typedef struct treeNode
{
	Element data;
	struct treeNode* left;
	struct treeNode* right;
} TREE_NODE;

typedef struct
{
	int count;
	TREE_NODE* root;
	int (*compare)(void* argu1, void* argu2);
} BST_TREE;

int compareInt(void* argu1, void* argu2);
int compareStr(void* argu1, void* argu2);

BST_TREE* bstCreate();
BST_TREE* bstCreate_General(int (*compare)(void* argu1, void* argu2));
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

void bstTraverse(BST_TREE* tree, void(*process)(TREE_NODE* root));
void _bstTraverse(TREE_NODE* root, void(*process)(TREE_NODE* root));

void* _retrieve(BST_TREE* tree, void* dataPtr, TREE_NODE* root);
void* BST_Retrieve(BST_TREE* tree, void* keyPtr);

TREE_NODE* FindSmallestBST(TREE_NODE* root);
TREE_NODE* FindLargestBST(TREE_NODE* root);
