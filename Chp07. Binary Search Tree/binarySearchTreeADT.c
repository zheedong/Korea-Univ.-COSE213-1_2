#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binarySearchTreeADT.h"
#include "Stack_General_LinkedList.h"

BST_TREE* bstCreate()
{
	BST_TREE* tree = (BST_TREE*)malloc(sizeof(BST_TREE));
	if (tree)
	{
		tree->root = NULL;
		tree->count = 0;
	}

	return tree;
}

BST_TREE* bstCreate_General(int (*compare)(void* argu1, void* argu2))
{
	BST_TREE* tree = (BST_TREE*)malloc(sizeof(BST_TREE));
	if (tree)
	{
		tree->root = NULL;
		tree->count = 0;
		tree->compare = compare;
	}

	return tree;
}

void bstDestroy(BST_TREE* tree)
{
	if (tree)
	{
		_bstDestroy(tree->root);
		tree->count = 0;

		free(tree);
	}
}

void _bstDestroy(TREE_NODE* root)
{
	if (root)
	{
		_bstDestroy(root->left);
		_bstDestroy(root->right);
		free(root);
	}
}


bool bstInsert(BST_TREE* tree, int data)
{
	TREE_NODE* newNode;
	newNode = (TREE_NODE*)malloc(sizeof(TREE_NODE));

	if (newNode != NULL) {
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;

		tree->root = _bstAdd(tree->root, newNode);
		tree->count++;
		return true;
	}
	return false;
}

TREE_NODE* _bstAdd(TREE_NODE* root, TREE_NODE* newNode)
{
	if (root == NULL)
		return newNode;

	if (newNode->data < root->data)
		root->left = _bstAdd(root->left, newNode);
	else
		root->right = _bstAdd(root->right, newNode);

	return root;
}

bool bstDelete(BST_TREE* tree, int key)
{
	bool flag;
	_bstDel(tree->root, key, &flag);
	tree->count--;
	return flag;
}

TREE_NODE* _bstDel(TREE_NODE* root, int data, bool* success)
{
	if (root == NULL)
	{
		*success = false;
		return root;
	}

	if (data < root->data)
		root->left = _bstDel(root->left, data, success);
	else if (data > root->data)
		root->right = _bstDel(root->right, data, success);
	else
	{	// root is the node to delete 
		TREE_NODE* delPtr = NULL;
		*success = true;

		if (!root->right)
		{ // root has no child or only left subtree 
			delPtr = root; root = root->left;
			free(delPtr); return root;
		}
		else if (!root->left)
		{ // root has only right subtree 
			delPtr = root;
			root = root->right;
			free(delPtr);
			return root;
		}
		else
		{ // root has both left and right children 
		  // find the largest among the left subtree 
			for (delPtr = root->left; delPtr->right != NULL; delPtr = delPtr->right);
			root->data = delPtr->data;
			root->left = _bstDel(root->left, delPtr->data, success);
		}
	}
	return root;
}

TREE_NODE* bstSearch(BST_TREE* tree, int key)
{
	return _bstFind(tree->root, key);
}

TREE_NODE* _bstFind(TREE_NODE* root, int key)
{
	//Recursive way
	if (!root)
		return NULL;

	if (key < root->data)
		return _bstFind(root->left, key);
	else if (key > root->data)
		return _bstFind(root->right, key);
	else
		return root;

	/*
	//Iterative way
	while (root != NULL)
	{
		if (key == root->data)
			break;
		else if (key < root->data)
			root = root->left;
		else if (key > root->data)
			root = root->right;
	}
	*/
}

bool bstEmpty(BST_TREE* tree)
{
	if (tree->count == 0)
		return true;
	else
		return false;
}

int bstCount(BST_TREE* tree)
{
	return tree->count;
}

void bstTraverse(BST_TREE* tree, void(*process)(TREE_NODE* root))
{
	_bstTraverse(tree->root, process);
}

void _bstTraverse(TREE_NODE* root, void(*process)(TREE_NODE* root))
{
	/*
	//Recursive
	if (root)
	{
		_bstTraverse(root->left, process);
		process(root);
		_bstTraverse(root->right, process);
	}
	*/

	//Iterative by STACK
	StackData* stack = NULL;
	TREE_NODE* current = root;
	bool done = false;

	if (root == NULL)
		return;
	Stack_Create(&stack);

	while (!done)
	{
		if (current != NULL)
		{
			Stack_Push(stack, current);
			current = current->left;
		}
		else
		{
			if (!Stack_Empty(stack))
			{
				current = Stack_Pop(stack);
				process(current);
				current = current->right;
			}
			else
				done = true;
		}
	}
	Stack_Destroy(stack);
}
