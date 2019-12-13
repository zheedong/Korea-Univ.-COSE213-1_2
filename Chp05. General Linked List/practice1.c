#include "General_LinkedList_Ordered.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define EOI -1
#pragma warning (disable : 4996)

int main() {
	ListData* pListData;
	pListData = List_Create();

	int buffer = 0;
	printf("Input number you would add (EOI -1) : ");
	do {
		scanf("%d", &buffer);
		if (buffer == EOF)
			break;
		List_Add(pListData, buffer);
	} while (1);

	while (1) {
		printf("\n--------------------\n");
		printf("\tMenu\t\n");
		printf("1. List Add\n");
		printf("2. List Remove\n");
		printf("3. List Retrieve\n");
		printf("4. List Traverse\n");
		printf("5. Exit\n");

		int flow = 0;
		do {
			scanf("%d", &flow);
		} while (flow < 1 && flow > 5);
		printf("\n");

		Element buffer = 0;
		int fromWhere = 0;
		Element out = 0;

		switch (flow) {
			case 1:
				printf("\nWhich number? :");
				scanf("%d", &buffer);
				List_Add(pListData, buffer);
				break;
			case 2:
				printf("\nWhich number? :");
				scanf("%d", &buffer);
				List_Remove(pListData, buffer);
				break;
			case 3:
				printf("\nWhich number? :");
				scanf("%d", &buffer);
				if (List_Retrieve(pListData, buffer))
					printf("Yes\n");
				else
					printf("No\n");
				break;
			case 4:
				printf("Index\tNumber\n");
				while (List_Traverse(pListData, fromWhere, &out)) {
					printf("%d.\t%d\n", fromWhere++, out);
				}
				break;
			case 5:
				List_Destroy(pListData);
				return 0;
			default:
				printf("Try again.\n");
				break;
		}
	}
}