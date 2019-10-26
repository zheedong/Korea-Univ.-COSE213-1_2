#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Element; //Changeable.

struct Stack_Node { //Stack node.
	Element data;
	struct Stack_Node* nextPtr;
};

struct Stack { //Struct that save Stack data.
	struct Stack_Node* topPtr;
	int size;
};

typedef struct Stack StackData;
typedef struct Stack_Node StackNode;

void Stack_Create(StackData* pStackData);
void Stack_Push(StackData* pStack, Element item);
Element Stack_Pop(StackData* pStack);
Element Stack_Top(StackData* pStack);
void Stack_Destroy(StackData* pStack);
bool isEmpty(StackData* pStack);

void Stack_Create(StackData** ppStackData) {
	*ppStackData = (StackData*)malloc(sizeof(StackData));
	(*ppStackData)->topPtr = NULL;
	(*ppStackData)->size = 0;
}

void Stack_Push(StackData* pStack, Element item) {
	StackNode* newPtr;
	newPtr = (StackNode*)malloc(sizeof(StackNode));
	if (newPtr != NULL) {
		newPtr->data = item;
		newPtr->nextPtr = pStack->topPtr;

		pStack->topPtr = newPtr; //Change top
		pStack->size++;
	}
	else {
		printf("MEMORY_ALLOCATION_FAIL\n");
		return;
	}
}

Element Stack_Pop(StackData* pStack) {
	Element popValue = 0;
	if (pStack->size == 0) {
		printf("STACK_EMPTY\n");
		return;
	}

	StackNode* tempPtr = pStack->topPtr;
	popValue = pStack->topPtr->data;
	pStack->topPtr = pStack->topPtr->nextPtr;

	free(tempPtr);
	pStack->size--;
	return popValue;
}

Element Stack_Top(StackData* pStack) {
	if (pStack->size == 0)
		return NULL;

	return pStack->topPtr->data;
}

void Stack_Destroy (StackData* pStack) {
	StackNode* pCur = NULL, * pNext = NULL;

	for (pCur = pStack->topPtr; pCur != NULL; pCur = pNext) {
		pNext = pCur->nextPtr;
		free(pCur);
	}

	pStack->size = 0;
	pStack->topPtr = NULL;

	free(pStack);
}

bool isEmpty(StackData* pStack) {
	if (pStack->size == 0)
		return true;
	else
		return false;
}

