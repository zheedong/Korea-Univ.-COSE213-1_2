#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

struct node {
	double data;
	struct node* nextPtr;
};

typedef struct node StackNode;

void push_double(StackNode** topPtr, Element value) {
	StackNode* newPtr;
	newPtr = malloc(sizeof(StackNode));

	if (newPtr != NULL) {
		newPtr->data = value;
		newPtr->nextPtr = *topPtr;
		*topPtr = newPtr;
	}
	else {
		printf("ERROR\n");
		exit(1);
	}
}

double pop_double(StackNode** topPtr) {
	StackNode* tempPtr;
	double popValue;

	if (*topPtr == NULL) {
		return -1;
	}

	tempPtr = *topPtr;
	popValue = (*topPtr)->data;
	*topPtr = (*topPtr)->nextPtr;
	free(tempPtr);

	return popValue;
}

int size_double(StackNode** topPtr) {
	int count = 0;
	if (topPtr == NULL) {
		printf("ERROR\n");
		exit(1);
	}
	StackNode* tempPtr = *topPtr;
	while (tempPtr != NULL) {
		count++;
		tempPtr = tempPtr->nextPtr;
	}

	return count;
}

int empty_double(StackNode** topPtr) {
	if (*topPtr == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

double top_double(StackNode** topPtr) {
	double popValue = -1;
	if (*topPtr == NULL) {
		return popValue;
	}
	popValue = (*topPtr)->data;

	return popValue;
}

double second_double(StackNode** topPtr) {
	double popValue = -1;
	if (*topPtr == NULL) {
		return popValue;
	}
	else if ((*topPtr)->nextPtr == NULL) {
		return popValue;
	}
	popValue = ((*topPtr)->nextPtr)->data;
	
	return popValue;
}
