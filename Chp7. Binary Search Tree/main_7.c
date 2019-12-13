#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "binarySearchTreeADT.h"

int compare(void* argu1, void* argu2)
{
	if (*(int*)argu1 > * (int*)argu2)
		return 1;
	else if (*(int*)argu1 < *(int*)argu2)
		return -1;
	else
		return 0;
}

void printInt(void* stuPtr)
{
	int* intPtr = (int*)stuPtr;
	printf("%d\n", *intPtr);
}

void printString(void* stuPtr)
{
	char* str = (char*)stuPtr;
	printf("%s\n", str);
}

void printNode(void* stuPtr)
{
	TREE_NODE* nodePtr = (TREE_NODE*)stuPtr;
	printf("%d\n", nodePtr->data);
}

int main()
{
	int data[] = { 14, 23, 7, 10, 33, 56, 80, 66, 70 };
	BST_TREE* bstTree = bstCreate_General(compare);

	for (int i = 0; i < sizeof(data) / sizeof(int); i++)
	{
		printf("Insert : %d\n", data[i]);
		bstInsert(bstTree, data[i]);
	}

	printf("Count : %d\n", bstCount(bstTree));

	int delKey[] = { 33, 7, 14 };
	for (int i = 0; i < sizeof(delKey) / sizeof(int); i++)
	{
		printf("Deleted : %d\n", delKey[i]);
		bstDelete(bstTree, delKey[i]);
	}

	printf("Count : %d\n", bstCount(bstTree));

	printf("Traverse :\n");
	bstTraverse(bstTree, printNode);

	int retreiveKey[] = { 14, 23, 7 };
	for (int i = 0; i < sizeof(retreiveKey) / sizeof(int); i++)
	{
		TREE_NODE* node = bstSearch(bstTree, retreiveKey[i]);
		if (node)
		{
			printf("Key: %d, Founded: %d\n", retreiveKey[i], node->data);
		}
		else
		{
			printf("No data for key: %d\n", retreiveKey[i]);
		}
	}

	printf("Count : %d\n", bstCount(bstTree));
	printf("%d\n", bstCount(bstTree));

	bstDestroy(bstTree);

	return 0;
}
