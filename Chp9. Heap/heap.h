#pragma once
#include <stdbool.h>

typedef int Element;

typedef struct tHeap {
	Element* heapAry; // array to store items 
	int maxSize; // maximum size (size of heapAry) 
	int size; // # of items in heap 
} Heap;

Heap* heapCreate(int maximum);
void heapInsert(Heap* pHeap, Element data);
bool heapDelete(Heap* pHeap, Element* pDataOut);
int heapCount(Heap* pHeap);
bool heapFull(Heap* pHeap);
bool heapEmpty(Heap* pHeap);
void heapDestroy(Heap* pHeap);
void ReheapUp(Heap* pHeap, int idx);
void ReheapDown(Heap* pHeap, int idx);
void BuildHeap(Heap* pHeap);
Element* heapSort(Heap* pHeap);
