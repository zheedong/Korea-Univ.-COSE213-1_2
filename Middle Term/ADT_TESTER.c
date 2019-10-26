#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ADT_Circular Queue.h"
#include "ADT_Linked_List.h"
#include "ADT_Queue.h"
#include "ADT_Stack.h"
#include "ADT_Binary Tree.h"
#pragma warning (disable:4996)

void Circular_Queue_Menu(Queue* pCircular) {
	while (1) {
		printf("------------------------------\n");
		printf("0. Enqueue\n");
		printf("1. Dequeue\n");
		printf("2. Front\n");
		printf("3. Rear\n");
		printf("4. Count\n");
		printf("5. Back To Main\n");

		int flow = 0;
		int buffer = 0;
		scanf("%d", &flow);
		switch (flow) {
		case 0:
			printf("Input Data : ");
			scanf("%d", &buffer);
			Circular_Queue_Enque(pCircular, buffer);
			break;
		case 1:
			buffer = Circular_Queue_Deque(pCircular);
			printf("%d is dequeued\n", buffer);
			break;
		case 2:
			printf("%d is front\n");
			break;
		case 3:
			break;
		case 4:

			break;
		case 5:
			return;
		}
	}
}

void Queue_Menu(QueueData* pQueue) {
	while (1) {
		printf("------------------------------\n");
		printf("0. Enqueue\n");
		printf("1. Dequeue\n");
		printf("2. Front\n");
		printf("3. Rear\n");
		printf("4. Count\n");
		printf("5. Back To Main\n");

		int flow = 0;
		int buffer = 0;
		switch (flow) {
		case 0:
			printf("Input Data : ");
			scanf("%d", &buffer);
			Queue_Enqueue(pQueue, buffer);
			printf("Enqueue success\n");
			break;
		case 1:
			buffer = Queue_Dequeue(pQueue);
			printf("%d is dequeued\n", buffer);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			return;
		}
	}
}

void Stack_Menu(StackData* pStack) {
	printf("------------------------------\n");
	printf("0. Push\n");
	printf("1. Pop\n");
	printf("2. Top\n");
	printf("3. Back To Main\n");

	while (1) {
		int flow = 0;
		int buffer = 0;
		scanf("%d", &flow);
		switch (flow) {
		case 0:
			printf("Input Data : ");
			scanf("%d", &buffer);
			Stack_Push(pStack, buffer);
			printf("Push success\n");
			break;
		case 1:
			buffer = Stack_Pop(pStack);
			printf("%d is popped\n", buffer);
			break;
		case 2:
			buffer = Stack_Top(pStack);
			printf("%d is on top\n", buffer);
			break;
		case 3:
			return;
		}
	}
}

void Linked_List_Menu(ListData* pList) {
	while (1) {
		printf("------------------------------\n");
		printf("0. Add\n");
		printf("1. Remove\n");
		printf("2. Retrieve\n");
		printf("3. Traverse\n");
		printf("4. Count\n");
		printf("5. Back To Main\n");

		int flow = 0;
		int buffer = 0;
		Element* dataOut = (Element*)malloc(sizeof(Element));
		int index = 0;
		scanf("%d", &flow);
		switch (flow) {
		case 0:
			printf("Input data : ");
			scanf("%d", &buffer);
			List_Add(pList, buffer);
			printf("Add success\n");
			break;
		case 1:
			printf("Remove data : ");
			scanf("%d", &buffer);
			List_Remove(pList, buffer);
			break;
		case 2:
			printf("Retrieve data : ");
			scanf("%d", &buffer);
			List_Retrieve(pList, buffer);
			break;
		case 3:
			index = 0;
			while (List_Traverse(pList, index++, dataOut)) {
				printf("%d\t", *dataOut);
				if (index % 5 == 0)
					printf("\n");
			}
			break;
		case 4:
			printf("%d is in the list.\n", List_Count(pList));
			break;
		case 5:
			return;
		}
	}
}

void Tree_Menu(TreeNode* pRoot) {
	while (1) {
		printf("------------------------------\n");
		printf("0. DFS_PreOrder\n");
		printf("1. DFS_InOrder\n");
		printf("2. DFS_PostOrder\n");
		printf("3. BFS\n");
		printf("4. Back To Main\n");

		int flow = 0;
		scanf("%d", &flow);
		switch (flow) {
		case 0:
			Binary_Tree_DFS_PreOrder(pRoot);
			break;
		case 1:
			Binary_Tree_DFS_InOrder(pRoot);
			break;
		case 2:
			Binary_Tree_DFS_PostOrder(pRoot);
			break;
		case 3:
			Binary_Tree_BFS(pRoot);
			break;
		case 4:
			return;
		}
	}
}

int main() {
	Queue* pCircular;
	QueueData* pQueue = NULL;
	StackData* pStack = NULL;
	ListData* pList = NULL;
	TreeNode* pRoot = NULL;
	TreeNode* pLeft = NULL;
	TreeNode* pRight = NULL;
	TreeNode* pLeft2 = NULL;
	TreeNode* pRight2 = NULL;

	int data[15];
	pCircular = Circular_Queue_Create(20);
	pList = List_Create();
	Queue_Create(&pQueue);
	Stack_Create(&pStack);

	printf("Input 15 data\n");
	for (int i = 0; i < 15; i++) {
		scanf("%d", &data[i]);
		Circular_Queue_Enque(pCircular, data[i]);
		Stack_Push(pStack, data[i]);
		Queue_Enqueue(pQueue, data[i]);
		List_Add(pList, data[i]);
	}
	pLeft = Binary_Tree_Create(NULL, data[0], NULL);
	pRight = Binary_Tree_Create(NULL, data[1], NULL);
	pLeft = Binary_Tree_Create(pLeft, data[2],pRight);
	pLeft = Binary_Tree_Create(NULL, data[3], NULL);
	pRight = Binary_Tree_Create(NULL, data[4], NULL);
	pRight = Binary_Tree_Create(pLeft, data[5], pRight);
	pLeft2 = Binary_Tree_Create(pLeft, data[6], pRight);
	pLeft = Binary_Tree_Create(NULL, data[7], NULL);
	pRight = Binary_Tree_Create(NULL, data[8], NULL);
	pLeft = Binary_Tree_Create(pLeft, data[9], pRight);
	pLeft = Binary_Tree_Create(NULL, data[10], NULL);
	pRight = Binary_Tree_Create(NULL, data[11], NULL);
	pRight = Binary_Tree_Create(pLeft, data[12], pRight);
	pRight2 = Binary_Tree_Create(pLeft, data[13], pRight);
	pRoot = Binary_Tree_Create(pLeft2, data[14], pRight2);

	int flow = 0;
	while (1) {
		printf("------------------------------\n");
		printf("0. Circular Queue\n");
		printf("1. Queue\n");
		printf("2. Stack\n");
		printf("3. Linkded List\n");
		printf("4. Tree\n");
		printf("5. EXIT\n");
		printf("Input : ");

		scanf("%d", &flow);
		switch (flow) {

		case 0:
			Circular_Queue_Menu(pCircular);
			break;
		case 1:
			Queue_Menu(pQueue);
			break;
		case 2:
			Stack_Menu(pStack);
			break;
		case 3:
			Linked_List_Menu(pList);
			break;
		case 4:
			Tree_Menu(pRoot);
			break;
		case 5:
			Circular_Queue_Destroy(pCircular);
			Queue_Destroy(pQueue);
			Stack_Destroy(pStack);
			List_Destroy(pList);
			Binary_Tree_Destroy(pRoot);
			return 0;
		default:
			printf("Try again.\n");
			break;
		}
	}
}