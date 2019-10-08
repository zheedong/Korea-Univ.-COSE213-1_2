#include "QueueADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	QueueNode* pHead = NULL;
	QueueNode* pTail = NULL;

	int iHowManySell = 0;
	int iNumberOfCustomer = 0;
	printf("number of customer : ");
	scanf_s("%d", &iNumberOfCustomer);

	for (int i = 0; i < iNumberOfCustomer; i++) { //Input Section
		int iPatience = 0;
		printf("Patience of customer : ");
		scanf_s("%d", &iPatience);

		if (i == 0) //First Trial
			createQueue(&pHead, &pTail, iPatience);
		else
			enqueue(&pTail, iPatience);
	}

	int time = 0;
	while (queueCount(pHead, pTail) != 0) {

		while ((queueFront(pHead) - time) < 0) { //0. Remove under 0 patience
			if (queueCount(pHead, pTail) == 0)
				break;
			dequeue(&pHead, &pTail);
		}
		if (queueCount(pHead, pTail) == 0)
			break;

		dequeue(&pHead, &pTail); //1. dequeue and increase sell.
		iHowManySell++;

		time++; //3. Time increase
	}
	
	printf("I sell %d hotdogs\n", iHowManySell);
	destroyQueue(&pHead, &pTail);
	return 0;
}