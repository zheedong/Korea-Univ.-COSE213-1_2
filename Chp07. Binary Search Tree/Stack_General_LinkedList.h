#pragma once
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int BOOL;

struct node { //Stack node.
	void* dataPtr; //General void pointer. In main function, call as pointer and malloc.
	struct node* nextPtr;
};

struct Stack { //Struct that save stack data.
	struct node* topPtr;
	int size;
};

typedef struct Stack StackData;
typedef struct node StackNode;

void Stack_Create(StackData** ppStackData) { //Create New Stack.
	*ppStackData = (StackData*)malloc(sizeof(StackData));
	if (*ppStackData != NULL) {
		(*ppStackData)->size = 0;
		(*ppStackData)->topPtr = NULL; //Stack is empty.
	}
	else {
		printf("Memory allocation fail\n");
	}
}

void Stack_Push(StackData* pStackData, void* pValue) {
	StackNode* newPtr;
	newPtr = (StackNode*)malloc(sizeof(StackNode));
	if (newPtr != NULL) { //Memory Allocation success.
		newPtr->dataPtr = pValue; //New node will be top.
		newPtr->nextPtr = pStackData->topPtr; //New node linked.
		pStackData->topPtr = newPtr; //TopPtr change.
		pStackData->size++; //Size increase
	}
	else {
		printf("ERROR. Memory allocation Fail.\n");
		exit(1);
	}
}

void* Stack_Pop(StackData* pStackData) {
	StackNode* tempPtr;
	void* pPop_Value;
	if (pStackData->size == 0) //Stack is empty.
		return;
	tempPtr = pStackData->topPtr; //Save temp to free.
	pPop_Value = (pStackData->topPtr)->dataPtr; //Save pointer of data to Pop_Value
	pStackData->topPtr = (pStackData->topPtr)->nextPtr; //Change the topPtr.
	free(tempPtr);
	pStackData->size--; //Size decrease
	return pPop_Value;
}

int Stack_Size(StackData* pStackData) {
	return pStackData->size;
}

BOOL Stack_Empty(StackData* pStackData) { //return 1 when stack is empty.
	if (pStackData->size == 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void* Stack_Top(StackData* pStackData) {
	void* pTop_Value;
	if (Stack_Empty(pStackData) == 1) //Empty check.
		return NULL;
	pTop_Value = (pStackData->topPtr)->dataPtr;
	return pTop_Value;
}

void Stack_Destroy(StackData* pStackData) {
	while (Stack_Empty(pStackData) == 0)
		Stack_Pop(pStackData);
	free(pStackData);
}
