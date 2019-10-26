#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expressionTreeADT.h"
#pragma warning (disable:4996)

NODE* createTree(NODE* left, const char* dataPtr, NODE* right) {
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	if (newNode == NULL)
		return;

	strcpy(newNode->dataPtr, dataPtr);
	newNode->left = left;
	newNode->right = right;
	return newNode;
}

void destroyTree(NODE* node) {
	if (node == NULL)
		return;

	if (node->left)
		destroyTree(node->left);
	if (node->right)
		destroyTree(node->right);

	free(node);
}

char* treeData(NODE* node) {
	return node->dataPtr;
}

bool hasChild(NODE* node) {
	if (node->right == NULL && node->left == NULL)
		return false;
	else
		return true;
}

double evaluateTree(NODE* node) {
	double retValue = 0;
	char* plus = { "+" };
	char* minus = { "-" };
	char* multip = { "*" };
	char* divide = { "/" };

	if (node == NULL)
		return;

	if (!hasChild(node)) { //number
		return atof(node->dataPtr);
	}
	else { //operator
		if (!strcmp(node->dataPtr, plus)) {
			retValue = evaluateTree(node->left) + evaluateTree(node->right);
		}
		else if (!strcmp(node->dataPtr, minus)) {
			retValue = evaluateTree(node->left) - evaluateTree(node->right);
		}
		else if (!strcmp(node->dataPtr, multip)) {
			retValue = evaluateTree(node->left) * evaluateTree(node->right);
		}
		else if (!strcmp(node->dataPtr, divide)) {

			if (evaluateTree(node->right) == 0) {
				printf("DIVIDE BY ZERO\n");
				exit(1);
			}

			retValue = evaluateTree(node->left) / evaluateTree(node->right);
		}
	}
	return retValue;
}
