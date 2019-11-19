#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Heap* heapCreate(int maximum) {
	Heap* newHeap = (Heap*)malloc(sizeof(Heap));
	if (newHeap != NULL)
	{
		newHeap->size = 0;
		newHeap->maxSize = maximum;
		newHeap->heapAry = (Element*)malloc(sizeof(Element) * maximum);
		return newHeap;
	}
	else
		return NULL;
}

void heapInsert(Heap* pHeap, Element data) {
	if (heapFull(pHeap))
	{
		printf("Heap is full!\n");
		return;
	}
	pHeap->heapAry[pHeap->size++] = data;
	ReheapUp(pHeap, pHeap->size - 1);
}

bool heapDelete(Heap* pHeap, Element* pDataOut) {
	if (heapEmpty(pHeap))
	{
		printf("Heap is empty!\n");
		return false;
	}

	*pDataOut = pHeap->heapAry[0];
	pHeap->heapAry[0] = pHeap->heapAry[--pHeap->size];
	ReheapDown(pHeap, 0);

	return true;
}

int heapCount(Heap* pHeap) {
	return pHeap->size;
}

bool heapFull(Heap* pHeap) {
	if (pHeap->size >= pHeap->maxSize)
		return true;
	else
		return false;
}

bool heapEmpty(Heap* pHeap) {
	if (pHeap->size <= 0)
		return true;
	else
		return false;
}

void heapDestroy(Heap* pHeap) {
	free(pHeap->heapAry);
	free(pHeap);
}

void ReheapUp(Heap* pHeap, int idx) {
	/*
	//Version Recursion

	int parentIdx = 0;

	if (idx <= 0 || idx >= pHeap->size) 
		return;

	parentIdx = (idx - 1) / 2;

	if (pHeap->heapAry[idx] > pHeap->heapAry[parentIdx])
	{
		Element temp = pHeap->heapAry[idx];
		pHeap->heapAry[idx] = pHeap->heapAry[parentIdx];
		pHeap->heapAry[parentIdx] = temp;
		ReheapUp(pHeap, parentIdx);
	}
	*/

	//Version Iterative

	int parentIdx = 0;
	Element curData = 0;

	if (idx <= 0 || idx >= pHeap->size)
		return;

	curData = pHeap->heapAry[idx];
	parentIdx = (idx - 1) / 2;
	while (idx > 0 && curData > pHeap->heapAry[parentIdx])
	{
		pHeap->heapAry[idx] = pHeap->heapAry[parentIdx];
		idx = parentIdx; parentIdx = (idx - 1) / 2;
	}
	pHeap->heapAry[idx] = curData;
}

void ReheapDown(Heap* pHeap, int idx) {
	/*
	//Recursion Version
	if (idx < 0 || idx >= pHeap->size)
		return;
	if (idx * 2 + 1 < pHeap->size)
	{
		int maxChild = idx * 2 + 1;
		if (maxChild + 1 < pHeap->size && pHeap->heapAry[maxChild + 1] > pHeap->heapAry[maxChild])
			maxChild++;
		if (pHeap->heapAry[maxChild] > pHeap->heapAry[idx])
		{
			Element temp = pHeap->heapAry[idx];
			pHeap->heapAry[idx] = pHeap->heapAry[maxChild];
			pHeap->heapAry[maxChild] = temp;
			ReheapDown(pHeap, maxChild);
		}
	}
	*/

	//Iterative Version
	Element curData = 0;
	if (idx < 0 || idx >= pHeap->size) 
		return;
	curData = pHeap->heapAry[idx]; 
	while (idx * 2 + 1 < pHeap->size)
	{
		int maxChild = idx * 2 + 1;
		if (maxChild + 1 < pHeap->size && pHeap->heapAry[maxChild + 1] > pHeap->heapAry[maxChild]) 
			maxChild++;
		if (pHeap->heapAry[maxChild] > curData) 
		{ 
			pHeap->heapAry[idx] = pHeap->heapAry[maxChild]; 
			idx = maxChild; 
		}
		else 
			break;
	} 
	pHeap->heapAry[idx] = curData;
}

void BuildHeap(Heap* pHeap) {
	int i = 0;
	for (i = 1; i < pHeap->size; i++) 
		ReheapUp(pHeap, i);
}

Element* heapSort(Heap* pHeap) {
	Heap* heapForSort = heapCreate(pHeap->maxSize);
	heapForSort->size = pHeap->size;
	for (int i = 0; i < heapForSort->size; i++)
		heapForSort->heapAry[i] = pHeap->heapAry[i];

	Element* arr = (Element*)malloc(sizeof(Element) * (heapForSort->size));
	
	int data = 0;
	for (int i = 0; heapForSort->size; i++)
	{
		if (heapForSort->heapAry[0] < heapForSort->heapAry[1])
		{
			int temp = heapForSort->heapAry[0];
			heapForSort->heapAry[0] = heapForSort->heapAry[1];
			heapForSort->heapAry[1] = temp;
		}
		heapDelete(heapForSort, &data);
		arr[i] = data;
	}
	heapDestroy(heapForSort);
	return arr;
}
