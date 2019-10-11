#pragma once
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int BOOL;
typedef int Element;

struct _node {
	Element data;
	struct _node* nextPtr;
};

typedef struct _node ListNode;

typedef struct _data {
	int count;
	ListNode* pHead;
	ListNode* pPos;
	ListNode* pRear;
}ListData;

ListData* List_Create() {
	ListData* pNew_List = (ListData*)malloc(sizeof(ListData));
	if (pNew_List == NULL)
		return NULL;

	pNew_List->count = 0;
	pNew_List->pHead = NULL;
	pNew_List->pPos = NULL;
	pNew_List->pRear = NULL;

	return pNew_List;
}

void _List_Insert(ListData* pList, ListNode* pPre, Element data) { //private function
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));
	if(pNewNode!=NULL)
		pNewNode->data = data;

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

BOOL _List_Search(ListData* pList, ListNode** ppPre, ListNode** ppLoc, Element data) {
	for (*ppPre = NULL, *ppLoc = pList->pHead; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->nextPtr) {
		if ((*ppLoc)->data == data)
			return TRUE;
		else if ((*ppLoc)->data > data)
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

void List_Add(ListData* pList, Element data) {
	ListNode* pPre = NULL, * pLoc = NULL;
	BOOL found = _List_Search(pList, &pPre, &pLoc, data); //Set location.
	if (!found) //Not allow overlap.
		_List_Insert(pList, pPre, data);
}

void List_Remove(ListData* pList, Element data) {
	ListNode* pPre, * pLoc = NULL;
	BOOL found = _List_Search(pList, &pPre, &pLoc, data);

	if (found)
		_List_Delete(pList, pPre, pLoc);
}

BOOL List_Retrieve(ListData* pList, Element data) {
	ListNode* pPre = NULL, * pLoc = NULL;
	return (_List_Search(pList, &pPre, &pLoc, data));
}

BOOL List_Traverse(ListData* pList, int fromWhere, Element* pDataOut) {
	/*
	Should use like
		int fromWhre = 0;
		Element* pDataOut;
		while(List_Traverse(pListData, fromwhere++, pDataOut)
			printf("%d", *pDataOuta);
	*/
	if (fromWhere == 0 || pList->pPos == NULL) { //In first excution
		pList->pPos = pList->pHead;
	}
	else { //General
		pList->pPos = pList->pPos->nextPtr;
	}

	if (pList->pPos != NULL) { //General
		*pDataOut = pList->pPos->data;
		return TRUE;
	}
	else { //In last excution
		*pDataOut = (Element)NULL;
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