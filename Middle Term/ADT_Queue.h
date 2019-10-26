#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Element;

struct node { //Queue node.
	Element data;
	struct node* nextPtr;
};

struct Queue { //Struct that save Queue data.
	struct node* headPtr;
	struct node* tailPtr;
	int size;
};

typedef struct Queue QueueData;
typedef struct node QueueNode;
void Queue_Create(QueueData** pQueueData);
void Queue_Enqueue(QueueData* pQueueData, Element item);
Element Queue_Dequeue(QueueData* pQueueData);
int Queue_Count(QueueData* pQueueData);
int Queue_Size(QueueData* pQueueData);
bool Queue_Empty(QueueData* pQueueData);
Element Queue_Front(QueueData* pQueueData);
Element Queue_Rear(QueueData* pQueueData);
void Queue_Destroy(QueueData* pQueueData);

void Queue_Create(QueueData** ppQueueData) { //Create New Queue.
	*ppQueueData = (QueueData*)malloc(sizeof(QueueData));

	if (*ppQueueData == NULL) {
		printf("ERROR. Memory allocation Fail.\n");
		return;
	}

	(*ppQueueData)->size = 0;
	(*ppQueueData)->headPtr = (*ppQueueData)->tailPtr = NULL; //Empty Queue
}

void Queue_Enqueue(QueueData* pQueueData, Element item) {
	QueueNode* newPtr;
	newPtr = (QueueNode*)malloc(sizeof(QueueNode));
	if (newPtr == NULL) { //Memory Allocation success.
		printf("ERROR. Memory allocation Fail.\n");
		return;
	}

	newPtr->data = item;
	newPtr->nextPtr = NULL;

	if (pQueueData->size <= 0) {
		pQueueData->headPtr = pQueueData->tailPtr = newPtr; //Head, tail, new is equals.
	}
	else {
		pQueueData->tailPtr->nextPtr = newPtr;
		pQueueData->tailPtr = newPtr;
	}
	pQueueData->size++;
}

Element Queue_Dequeue(QueueData* pQueueData) {
	QueueNode* tempPtr;
	Element pDequeue_Value;

	if (pQueueData->size == 0) //Queue is empty.
		return;

	tempPtr = pQueueData->headPtr; //Save temp to free.
	pDequeue_Value = (pQueueData->headPtr)->data; //Save data to Dequeue_Value
	pQueueData->headPtr = (pQueueData->headPtr)->nextPtr; //Change the headPtr.

	if (pQueueData->headPtr == NULL) { //If Queue is empty.
		pQueueData->tailPtr = NULL;
	}

	free(tempPtr);
	pQueueData->size--; //Size decrease
	return pDequeue_Value;
}

int Queue_Count(QueueData* pQueueData) {
	return pQueueData->size;
}

int Queue_Size(QueueData* pQueueData) {
	return pQueueData->size;
}

bool Queue_Empty(QueueData* pQueueData) { //return 1 when Queue is empty.
	if (pQueueData->size == 0) {
		return true;
	}
	else {
		return false;
	}
}

Element Queue_Front(QueueData* pQueueData) {
	Element pFront_Value;
	if (Queue_Empty(pQueueData) == 1) //Empty check.
		return;
	pFront_Value = (pQueueData->headPtr)->data;
	return pFront_Value;
}

Element Queue_Rear(QueueData* pQueueData) {
	Element pRear_Value;
	if (Queue_Empty(pQueueData) == 1) //Empty check.
		return;
	pRear_Value = (pQueueData->tailPtr)->data;
	return pRear_Value;
}

void Queue_Destroy(QueueData* pQueueData) {
	QueueNode* pCur = NULL, * pNext = NULL;
	
	for (pCur = pQueueData->headPtr; pCur != NULL; pCur = pNext) {
		pNext = pCur->nextPtr;
		free(pCur);
	}

	pQueueData->size = 0;
	pQueueData->headPtr = pQueueData->tailPtr = NULL;

	free(pQueueData);
}
