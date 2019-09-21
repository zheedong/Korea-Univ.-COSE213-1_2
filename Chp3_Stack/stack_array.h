#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef int Element; //Changeable.

typedef struct {
	Element *stack;
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
