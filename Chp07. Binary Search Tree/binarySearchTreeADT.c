#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binarySearchTreeADT.h"
#include "Stack_General_LinkedList.h"

int compareInt(void* argu1, void* argu2)
{
	return *(int*)argu1 - *(int*)argu2;
}

int compareStr(void* argu1, void* argu2)
{
	return strcmp((char*)argu1, (char*)argu2);
}

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


bool bstInsert(BST_TREE* tree, Element data)
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
	if (root == NULL) //Basic Case : current BST is an empty tree.
		return newNode;

	if (newNode->data < root->data) //General Case
		root->left = _bstAdd(root->left, newNode); //If the new node is smaller than root of BST.
	else
		root->right = _bstAdd(root->right, newNode); //If the new node is greater than root of BST.

	return root;
}

bool bstDelete(BST_TREE* tree, Element key)
{
	bool flag;
	_bstDel(tree->root, key, &flag);
	tree->count--;
	return flag;
}

TREE_NODE* _bstDel(TREE_NODE* root, Element data, bool* success)
{
	if (root == NULL) //ERROR : empty BST
	{
		*success = false;
		return root;
	}

	if (data < root->data) //If key data is smaller than root->data.
		root->left = _bstDel(root->left, data, success); //Recursive call.
	else if (data > root->data) //If key data is greater than root->data.
		root->right = _bstDel(root->right, data, success);
	else //data == root->data
	{	// root is the node to delete 
		TREE_NODE* delPtr = NULL;
		*success = true;

		if (!root->right)
		{ // CASE 1 : root has no child or CASE 2 : only left subtree 
			delPtr = root;
			root = root->left; // In CASE 1, root->letf is NULL.
			free(delPtr);
			return root;
		}
		else if (!root->left)
		{ // CASE 3 : root has only right subtree 
			delPtr = root;
			root = root->right;
			free(delPtr);
			return root;
		}
		else
		{ // CASE 4 : root has both left and right children 
			for (delPtr = root->left; delPtr->right != NULL; delPtr = delPtr->right); // find the largest among the left subtree 
			root->data = delPtr->data; // Change root->data to Largest in root->left subtree.
			root->left = _bstDel(root->left, delPtr->data, success); // Input left subtree, and return left subtree biggest one deleted.
		}
	}
	return root;
}

TREE_NODE* bstSearch(BST_TREE* tree, Element key)
{
	return _bstFind(tree->root, key);
}

TREE_NODE* _bstFind(TREE_NODE* root, Element key)
{
	/*
	//Recursive way
	if (!root)
		return NULL;

	if (key < root->data)
		return _bstFind(root->left, key);
	else if (key > root->data)
		return _bstFind(root->right, key);
	else
		return root;
	*/

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
	return root;
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
	//NOTE! Inorder traversal of a BST produces a sorted list.
	_bstTraverse(tree->root, process);
}

void _bstTraverse(TREE_NODE* root, void(*process)(TREE_NODE* root))
{
	/*
	//Recursive
	//Inorder
	if (root)
	{
		_bstTraverse(root->left, process);
		process(root);
		_bstTraverse(root->right, process);
	}
	*/

	//Iterative by STACK
	//Inorder
	StackData* stack = NULL;
	TREE_NODE* current = root;
	bool done = false;

	if (root == NULL) //ERROR : Empty BST
		return;
	Stack_Create(&stack); //Stack is created.

	while (!done) //Check flag.
	{
		if (current != NULL) //Current is NOT empty.
		{
			Stack_Push(stack, current); //Push it!
			current = current->left; //Change current to current->left.
		}
		else //Current is NULL.
		{
			if (!Stack_Empty(stack)) //If Stack is not Empty
			{
				current = Stack_Pop(stack);
				process(current); //Print something
				current = current->right; //Change current to 
			}
			else
				done = true;
		}
	}
	Stack_Destroy(stack);
}

void* _retrieve(BST_TREE* tree, void* dataPtr, TREE_NODE* root)
{
	if (root) {
		if (tree->compare(dataPtr, root->data) < 0)
			return _retrieve(tree, dataPtr, root->left);
		else if (tree->compare(dataPtr, root->data) > 0)
			return _retrieve(tree, dataPtr, root->right);
		else// Found equal key
			return root->data;
	} // if root
	else
		return NULL; // Data not in tree
}// _retrieve

void* BST_Retrieve(BST_TREE* tree, void* keyPtr)
{
	if (tree->root)
		return _retrieve(tree, keyPtr, tree->root);
	else
		return NULL;
}// BST_Retrieve

TREE_NODE* FindSmallestBST(TREE_NODE* root)
{
	if (root != NULL && root->left != NULL)
		return FindSmallestBST(root->left);
	else
		return root;
}

TREE_NODE* FindLargestBST(TREE_NODE* root)
{
	if (root != NULL && root->right != NULL)
		return FindLargestBST(root->right);
	else
		return root;
}
