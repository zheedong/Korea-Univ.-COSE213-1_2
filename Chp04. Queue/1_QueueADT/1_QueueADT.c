#pragma once
#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* nextPtr;
};

typedef struct node QueueNode;

void createQueue(QueueNode** ppHead, QueueNode** ppTail, int data) {
	*ppHead = (QueueNode*)malloc(sizeof(QueueNode));
	(*ppHead)->data = data;
	(*ppHead)->nextPtr = NULL;
	*ppTail = *ppHead;
}

void enqueue(QueueNode** ppTail, int data) {
	QueueNode* pNewNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (pNewNode == NULL) {
		printf("Memory allocation Fail\n");
		return;
	}
	else {
		(*ppTail)->nextPtr = pNewNode;
		pNewNode->data = data;
		pNewNode->nextPtr = NULL;
		*ppTail = pNewNode;
	}
}

int dequeue(QueueNode** ppHead, QueueNode** ppTail) {
	int retValue;
	if (*ppHead == NULL) { //Empty check
		return -1;
	}
	else {
		retValue = (*ppHead)->data;
		QueueNode* pTemp = *ppHead;
		if (*ppHead == *ppTail) { //Left one node
			*ppHead = NULL;
			*ppTail = NULL;
		}
		else { //General Case
			*ppHead = pTemp->nextPtr;
		}
		free(pTemp); //Free memory
	}
	return retValue;
}

int queueFront(QueueNode* pHead) {
	if (pHead == NULL) { //Empty Queue
		return -1;
	}
	else {
		return pHead->data;
	}
}

int queueCount(QueueNode* pHead, QueueNode* pTail) { //Call by value
	int counter = 0;
	QueueNode* pTemp = pHead;
	if (pHead == NULL || pTail == NULL) {
		return counter;
	}
	else {
		while (pTemp != pTail) {
			counter++;
			pTemp = pTemp->nextPtr;
		}
		counter++;
	}
	return counter;
}

void destroyQueue(QueueNode** ppHead, QueueNode** ppTail) {
	while (queueCount(*ppHead, *ppTail) != 0)
		dequeue(ppHead, ppTail);
}
