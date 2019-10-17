#include "orderedListADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

LIST* createList(int(*compare)(void* pArg1, void* pArg2)) {
	LIST* list = (LIST*)malloc(sizeof(LIST));
	if (list) {
		list->size = 0;
		list->pos = NULL;
		list->head = NULL;
		list->rear = NULL;
		list->compare = compare;
	}
	return list;
}

void destroyList(LIST* pList) {
	NODE* pDel = NULL, * pNext = NULL;
	for (pDel = pList->head; pDel != NULL; pDel = pNext) {
		pNext = pDel->next;
		free(pDel);
	}

	free(pList);
}

bool insert(LIST* pList, void* pDataIn) {
	NODE* pPre = NULL, * pLoc = NULL;
	bool found = _search(pList, &pPre, &pLoc, pDataIn);
	if (!found) { //Not allow overlap.
		_insert(pList, pPre, pDataIn);
		return true;
	}
	return false;
}

bool Myremove(LIST* pList, void* pKey) {
	NODE* pPre, * pLoc = NULL;
	bool found = _search(pList, &pPre, &pLoc, pKey);

	if (found) {
		_delete(pList, pPre, pLoc);
		return true;
	}
	return false;
}

bool retrieve(LIST* pList, void* pKey, void** pDataOut) {
	NODE* pPre;
	NODE* pCur;

	if (_search(pList, &pPre, &pCur, pKey))
	{
		*pDataOut = pCur->pData;
		return true;
	}
	else
	{
		*pDataOut = NULL;
		return false;
	}
}

int size(LIST* pList) {
	return pList->size;
}

bool isEmpty(LIST* pList) {
	if (pList->size == 0)
		return TRUE;
	return FALSE;
}

bool iterate(LIST* pList, void** pDataOut) {
	if (pList->pos == NULL) { //In first excution
		pList->pos = pList->head;
	}
	else { //General
		pList->pos = pList->pos->next;
	}

	if (pList->pos != NULL) { //General
		*pDataOut = pList->pos->pData;
		return TRUE;
	}
	else { //In last excution
		*pDataOut = NULL;
		return FALSE;
	}
}

void initIterator(LIST* pList) {
	pList->pos = NULL;
}


void printList(LIST* pList, void(*print)(void* pArg)) {
	STUDENT* curStudent = NULL;
	while (iterate(pList, (void**)&curStudent))
	{
		if (pList->pos == NULL)
			break;

		(*print)(curStudent);
	}
	initIterator(pList);
	printf("===========================\n");
}


void printStudent(void* pArg) {
	STUDENT* pStudent;
	pStudent = (STUDENT*)pArg;

	printf("STUDENT ID: %d\n", pStudent->id);
	printf("NAME: %s\n", pStudent->name);
	printf("EMAIL: %s\n", pStudent->email);
	printf("-------------\n");
}

int cmpStudentId(void* pStudent1, void* pStudent2) {
	return *(int*)pStudent1 - *(int*)pStudent2;
}


static bool _insert(LIST* pList, NODE* pPre, void* pDataIn) {
	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	if (pNewNode != NULL)
		pNewNode->pData = pDataIn;
	else
		return false;

	if (pPre == NULL) { //insert before head node
		pNewNode->next = pList->head;
		pList->head = pNewNode;
	}
	else {
		pNewNode->next = pPre->next; //insert general case
		pPre->next = pNewNode;
	}

	pList->size++; //head complete

	NODE* pCur = pList->head;
	while (1) {
		if (pCur->next == NULL)
			break;
		pCur = pCur->next;
	}
	pList->rear = pCur;

	return true;
}

static void _delete(LIST* pList, NODE* pPre, NODE* pCur) {
	if (pPre == NULL)
		pList->head = pCur->next;
	else
		pPre->next = pCur->next;

	NODE* pLoc = pList->head;
	while (1) {
		if (pLoc == NULL || pLoc->next == NULL)
			break;
		pLoc = pLoc->next;
	}
	pList->rear = pLoc;

	free(pCur);
	pList->size--;
}

static bool _search(LIST* pList, NODE** pPre, NODE** pCur, void* pKey) {
#define COMPARE (((*pList->compare)(pKey, (*pCur)->pData)))
#define COMPARE_LAST ((*pList->compare) (pKey, pList->rear->pData))

	int result;
	*pPre = NULL;
	*pCur = pList->head;
	if (pList->size == 0)
		return false;

	if (COMPARE_LAST > 0)
	{
		*pPre = pList->rear;
		*pCur = NULL;
		return false;
	}

	while ((result = COMPARE) > 0)
	{
		*pPre = *pCur;
		*pCur = (*pCur)->next;
	}

	if (result == 0)
		return true;
	else
		return false;
}
