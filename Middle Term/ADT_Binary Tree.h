#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ADT_Queue.h"

typedef int Element;

struct Tree_node {
	Element data;
	struct Tree_node* pLeft, * pRight;
};

typedef struct Tree_node TreeNode;

TreeNode* Binary_Tree_Create(TreeNode* pLeftNode, Element item, TreeNode* pRightNode);
TreeNode* Binary_Tree_LeftNode(TreeNode* node);
Element Binary_Tree_Data(TreeNode* node);
TreeNode* Binary_Tree_RightNode(TreeNode* node);
bool Binary_Tree_IsEmpty(TreeNode* node);
void Binary_Tree_DFS_PreOrder(TreeNode* node);
void Binary_Tree_DFS_InOrder(TreeNode* node);
void Binary_Tree_DFS_PostOrder(TreeNode* node);
void Binary_Tree_BFS(TreeNode* node);
TreeNode* Binary_Tree_Copy(TreeNode* node);

TreeNode* Binary_Tree_Create(TreeNode* pLeftNode, Element item, TreeNode* pRightNode) {
	TreeNode* pNewNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (pNewNode == NULL)
		return NULL;
	else {
		pNewNode->data = item; //Coulde be changed.

		pNewNode->pLeft = pLeftNode;
		pNewNode->pRight = pRightNode;

		return pNewNode;
	}
}

TreeNode* Binary_Tree_LeftNode(TreeNode* node) {
	if (Binary_Tree_IsEmpty(node->pLeft))
		return;
	return node->pLeft;
}

Element Binary_Tree_Data(TreeNode* node) {
	if (Binary_Tree_IsEmpty(node->pRight))
		return;
	return node->data;
}

TreeNode* Binary_Tree_RightNode(TreeNode* node) {
	return node->pRight;
}

bool Binary_Tree_IsEmpty(TreeNode* node) {
	if (node->pLeft == NULL && node->pRight == NULL)
		return false;
	else
		return true;
}

void Binary_Tree_DFS_PreOrder(TreeNode* node) {
	if (node == NULL)
		return;
	printf("%d\n", node->data);
	Binary_Tree_DFS_PreOrder(node->pLeft);
	Binary_Tree_DFS_PreOrder(node->pRight);
}

void Binary_Tree_DFS_InOrder(TreeNode* node) {
	if (node == NULL)
		return;
	Binary_Tree_DFS_PreOrder(node->pLeft);
	printf("%d\n", node->data);
	Binary_Tree_DFS_PreOrder(node->pRight);
}

void Binary_Tree_DFS_PostOrder(TreeNode* node) {
	if (node == NULL)
		return;
	Binary_Tree_DFS_PreOrder(node->pLeft);
	Binary_Tree_DFS_PreOrder(node->pRight);
	printf("%d\n", node->data);
}

void Binary_Tree_BFS(TreeNode* node) {
	if (node == NULL)
		return;

	QueueData* Queue = NULL;
	Queue_Create(Queue);

	while (node) {
		printf("%d\n", node->data);

		if (node->pLeft)
			Queue_Enqueue(Queue, node->pLeft->data);
		if (node->pRight)
			Queue_Enqueue(Queue, node->pRight->data);
		if (!Binary_Tree_IsEmpty(node))
			node = (TreeNode*)Queue_Dequeue(Queue);
		else
			node = NULL;
	}
	Queue_Destroy(Queue);
}

void Binary_Tree_Destroy(TreeNode* node) {
	if (node == NULL)
		return;

	if (node->pLeft)
		Binary_Tree_Destroy(node->pLeft);
	if (node->pRight)
		Binary_Tree_Destroy(node->pRight);

	free(node);
}

TreeNode* Binary_Tree_Copy(TreeNode* node) {
	if (node == NULL)
		return NULL;
	return Binary_Tree_Create(Binary_Tree_Copy(node->pLeft), node->data, Binary_Tree_Copy(node->pRight));
}
