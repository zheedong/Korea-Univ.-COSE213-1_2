#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "binarySearchTreeADT.h"

int main()
{
	int data[] = { 14, 23, 7, 10, 33, 56, 80, 66, 70 };
	BST_TREE* bstTree = bstCreate();

	for (int i = 0; i < sizeof(data) / sizeof(int); i++)
	{
		bstInsert(bstTree, data[i]);
	}

	printf("%d\n", bstCount(bstTree));

	int delKey[] = { 33, 7, 14 };
	for (int i = 0; i < sizeof(delKey) / sizeof(int); i++)
	{
		bstDelete(bstTree, delKey[i]);
	}

	printf("%d\n", bstCount(bstTree));

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

	printf("%d\n", bstCount(bstTree));

	bstDestroy(bstTree);

	return 0;
}
