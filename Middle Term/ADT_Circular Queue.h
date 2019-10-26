#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Element;

typedef struct {
	Element* queue;
	int size;
	int front, rear;
}Queue;

Queue* Circular_Queue_Create(int size);
void Circular_Queue_Enque(Queue* pQueue, Element item);
Element Circular_Queue_Deque(Queue* pQueue);
Element Circular_Queue_Front(Queue* pQueue);
Element Circular_Queue_Rear(Queue* pQueue);
int Circular_Queue_Count(Queue* pQueue);
bool Circular_Queue_isFull(Queue* pQueue);
bool Circular_Queue_isEmpty(Queue* pQueue);
void Circular_Queue_Destroy(Queue* pQueue);

Queue* Circular_Queue_Create(int size) {
	Queue* pQueue = (Queue*)malloc(sizeof(Queue));
	if (pQueue == NULL)
		return;
	pQueue->queue = (Element*)malloc(size * sizeof(Element));
	if (pQueue->queue == NULL) {
		free(pQueue);
		return;
	}
	
	pQueue->size = size;
	pQueue->front = pQueue->rear = 0;

	return pQueue;
}

void Circular_Queue_Enque(Queue* pQueue, Element item) {
	if (Circular_Queue_isFull(pQueue)) {
		printf("FULL_QUEUE\n");
		return;
	}
	else {
		pQueue->rear = (pQueue->rear + 1) % pQueue->size;
		pQueue->queue[pQueue->rear] = item;
	}
}

Element Circular_Queue_Deque(Queue* pQueue) {
	if (Circular_Queue_isEmpty(pQueue)) {
		printf("EMPTY_QUEUE\n");
		return;
	}
	else {
		pQueue->front = (pQueue->front + 1) % pQueue->size;
		return pQueue->queue[pQueue->front];
	}
}

Element Circular_Queue_Front(Queue* pQueue) {
	return pQueue->queue[pQueue->front];
}

Element Circular_Queue_Rear(Queue* pQueue) {
	return pQueue->queue[pQueue->rear];
}

int Circular_Queue_Count(Queue* pQueue) {
	return pQueue->size;
}

bool Circular_Queue_isFull(Queue* pQueue) {
	if ((pQueue->rear + 1) % pQueue->size == pQueue->front)
		return true;
	else
		return false;
}

bool Circular_Queue_isEmpty(Queue* pQueue) {
	if (pQueue->front == pQueue->rear)
		return true;
	else
		return false;
}

void Circular_Queue_Destroy(Queue* pQueue) {
	free(pQueue->queue);
	free(pQueue);
}
