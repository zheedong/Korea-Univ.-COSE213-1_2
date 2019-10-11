#pragma once
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int BOOL;

struct node { //Queue node.
	void* dataPtr; //General void pointer. In main function, call as pointer and malloc.
	struct node* nextPtr;
};

struct Queue { //Struct that save Queue data.
	struct node* headPtr;
	struct node* tailPtr;
	int size;
};

typedef struct Queue QueueData;
typedef struct node QueueNode;

void Queue_Create(QueueData* pQueueData) { //Create New Queue.
	pQueueData = (QueueData*)malloc(sizeof(QueueData));
	pQueueData->size = 0;
	pQueueData->headPtr = NULL; //Queue is empty.
	pQueueData->tailPtr = NULL;
}

void Queue_Enqueue(QueueData* pQueueData, void* pValue) {
	QueueNode* newPtr;
	newPtr = (QueueNode*)malloc(sizeof(QueueNode));
	if (newPtr != NULL) { //Memory Allocation success.
		newPtr->dataPtr = pValue; //New node will be head.
		(pQueueData->tailPtr)->nextPtr = newPtr; //New node linked.
		newPtr->nextPtr = NULL; //Set new node's nextPtr NULL.
		pQueueData->tailPtr = newPtr; //headPtr change.
		pQueueData->size++;
	}
	else {
		printf("ERROR. Memory allocation Fail.\n");
		exit(1);
	}
}

void* Queue_Dequeue(QueueData* pQueueData) {
	QueueNode* tempPtr;
	void* pDequeue_Value;
	if (pQueueData->size == 0) //Queue is empty.
		return;
	tempPtr = pQueueData->headPtr; //Save temp to free.
	pDequeue_Value = (pQueueData->headPtr)->dataPtr; //Save pointer of data to Dequeue_Value
	pQueueData->headPtr = (pQueueData->headPtr)->nextPtr; //Change the headPtr.
	if (pQueueData->headPtr == NULL) { //If Queue is empty.
		pQueueData->tailPtr = NULL;
	}
	free(tempPtr);
	pQueueData->size--; //Size decrease
	return pDequeue_Value;
}

int Queue_Size(QueueData* pQueueData) {
	return pQueueData->size;
}

BOOL Queue_Empty(QueueData* pQueueData) { //return 1 when Queue is empty.
	if (pQueueData->size == 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void* Queue_Front(QueueData* pQueueData) {
	void* pFront_Value;
	if (Queue_Empty(pQueueData) == 1) //Empty check.
		return;
	pFront_Value = (pQueueData->headPtr)->dataPtr;
	return pFront_Value;
}

void* Queue_Rear(QueueData* pQueueData) {
	void* pRear_Value;
	if (Queue_Empty(pQueueData) == 1) //Empty check.
		return;
	pRear_Value = (pQueueData->tailPtr)->dataPtr;
	return pRear_Value;
}

void Queue_Destroy(QueueData* pQueueData) {
	while (Queue_Empty(pQueueData) == 0)
		Queue_Dequeue(pQueueData);
	free(pQueueData);
}
