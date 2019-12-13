#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Element; //Changeable.

typedef struct {
	Element* stack;
	int size;
	int top;
}Stack;

Stack* createStack(int size) {
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL) {
		printf("ERROR : Memory allocation FAIL.\n");
		exit(1);
	}
	pStack->stack = (Element*)malloc(size * sizeof(Element));
	if (pStack->stack == NULL) {
		printf("ERROR : Memory allocation FAIL.\n");
		free(pStack);
		exit(1);
	}
	 memset(pStack->stack, NULL, size);
	pStack->size = size;
	pStack->top = -1;

	return pStack;
}

void Push(Stack* pStack, Element item) {
	if (pStack->top == pStack->size - 1) //Check Overflow
		return;

	pStack->stack[++pStack->top] = item;
}

Element Pop(Stack* pStack) {
	if (pStack->top < 0) //Check Underflow
		return NULL;

	return pStack->stack[pStack->top--];
}

Element Top(Stack* pStack) {
	if (pStack->top < 0)
		return NULL;

	return pStack->stack[pStack->top];
}

void DestroyStack(Stack* pStack) {
	if (pStack->top > 0)
		free(pStack->stack);
	free(pStack);
}

int isEmpty(Stack* pStack) {
	if (pStack->top == -1)
		return 0;
	else
		return 1;
}

Stack* reverse_Stack(Stack* pStack) {
	Stack* pStack_reverse = createStack(pStack->size);
	for (int i = 0; i < pStack->size; i++)
		Push(pStack_reverse, Pop(pStack));
	return pStack_reverse;
}

Stack* CatStack(Stack* pStack1, Stack* pStack2) {
	Stack* pStack_new = createStack(pStack1->size + pStack2->size);
	Stack* pStack2_reverse = reverse_Stack(pStack2);

	for (int i = 0; i < pStack1->size; i++) {
		Element value = Pop(pStack1);
		Push(pStack_new, value);
	}

	for (int i = 0; i < pStack2->size; i++) {
		Element value = Pop(pStack2_reverse);
		Push(pStack_new, value);
	}

	DestroyStack(pStack1);
	DestroyStack(pStack2);

	return pStack_new;
}