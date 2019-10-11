#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef int BOOL;

typedef struct _LinkedList_Node {
	void* dataPtr; //General void pointer
	ListNode* nextPtr;
}ListNode;

typedef struct _LinkedList {
	int count;
	ListNode* pPos;
	ListNode* pRear;
	ListNode* pHead;
	int (*compare) (void* argu1, void* argu2); //Function pointer
}ListData;

int List_Compare_Int(void* argu1, void* argu2) {
	return *(int*)argu1 - *(int*)argu2;
}

int List_Compare_String(void* argu1, void* argu2) {
	return strcmp((char*)argu1, (char*)argu2);
}

ListData* List_Create(int (*compare)(void* argu1, void* argu2)) {
	ListData* list = (ListData*)malloc(sizeof(ListData));
	if (list) {
		list->count = 0;
		list->pPos = NULL;
		list->pHead = NULL;
		list->pRear = NULL;
		list->compare = compare;
	}
	return list;
}

void _List_Insert(ListData* pList, ListNode* pPre, void* dataPtr) { //private function
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));
	pNewNode->dataPtr = dataPtr;

	if (pPre == NULL) { //insert before head node
		pNewNode->nextPtr = pList->pHead;
		pList->pHead = pNewNode;
	}
	else {
		pNewNode->nextPtr = pPre->nextPtr; //insert general case
		pPre->nextPtr = pNewNode;
	}

	pList->count++;
}

BOOL _List_Search(ListData* pList, ListNode** ppPre, ListNode** ppLoc, void* dataPtr) {
	for (*ppPre = NULL, *ppLoc = pList->pHead; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->nextPtr) {
		if ((*(pList->compare))((*ppLoc)->dataPtr, dataPtr) == 0)
			return TRUE;
		else if ((*(pList->compare))((*ppLoc)->dataPtr, dataPtr) > 0)
			break;
	}

	return FALSE;
}

void _List_Delete(ListData* pList, ListNode* pPre, ListNode* pLoc) {
	if (pPre == NULL)
		pList->pHead = pLoc->nextPtr;
	else
		pPre->nextPtr = pLoc->nextPtr;

	free(pLoc);
	pList->count--;
}

void List_Add(ListData* pList, void* dataPtr) {
	ListNode* pPre = NULL, * pLoc = NULL;
	BOOL found = _List_Search(pList, &pPre, &pLoc, dataPtr);
	if (!found) //Not allow overlap.
		_List_Insert(pList, pPre, dataPtr);
}

void List_Remove(ListData* pList, void* dataPtr) {
	ListNode* pPre, * pLoc = NULL;
	BOOL found = _List_Search(pList, &pPre, &pLoc, dataPtr);

	if (found)
		_List_Delete(pList, pPre, pLoc);
}

BOOL List_Retrieve(ListData* pList, void* pDataOut) {
	ListNode* pPre = NULL, * pLoc = NULL;
	return (_List_Search(pList, &pPre, &pLoc, pDataOut));
}

BOOL List_Traverse(ListData* pList, int fromWhere, void* pDataOut) {
	if (fromWhere == 0 || pList->pPos == NULL) { //In first excution
		pList->pPos = pList->pHead;
	}
	else { //General
		pList->pPos = pList->pPos->nextPtr;
	}

	if (pList->pPos != NULL) { //General
		pDataOut = pList->pPos->dataPtr;
		return TRUE;
	}
	else { //In last excution
		pDataOut = NULL;
		return FALSE;
	}
}

void List_Destroy(ListData* pList) {
	ListNode* pDel = NULL, * pNext = NULL;
	for (pDel = pList->pHead; pDel != NULL; pDel = pNext) {
		pNext = pDel->nextPtr;
		free(pDel);
	}

	free(pList);
}

int List_Count(ListData* pList) {
	return pList->count;
}
