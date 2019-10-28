#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#pragma warning (disable:4996)

typedef char* Element;

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
	int (*compare)(Element argu1, Element argu2);
}ListData;

ListData* List_Create(int (*compare)(Element argu1, Element argu2));
void _List_Insert(ListData* pList, ListNode* pPre, Element data);
bool _List_Search(ListData* pList, ListNode** ppPre, ListNode** ppLoc, Element data);
void _List_Delete(ListData* pList, ListNode* pPre, ListNode* pLoc);
void List_Add(ListData* pList, Element data);
void List_Remove(ListData* pList, Element data);
bool List_Retrieve(ListData* pList, Element data);
bool List_Traverse(ListData* pList, int fromWhere, Element* pDataOut);
void List_Destroy(ListData* pList);
int List_Count(ListData* pList);


int compare_string(char* argu1, char* argu2) {
	return (-1) * strcmp(argu1, argu2);
}

ListData* List_Create(int (*compare)(Element argu1, Element argu2)) {
	ListData* pNew_List = (ListData*)malloc(sizeof(ListData));
	if (pNew_List == NULL)
		return NULL;
	pNew_List->count = 0;
	pNew_List->pHead = NULL;
	pNew_List->pPos = NULL;
	pNew_List->pRear = NULL;
	pNew_List->compare = compare;
	return pNew_List;
}

void _List_Insert(ListData* pList, ListNode* pPre, Element data) { //private function
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));
	if (pNewNode != NULL)
		pNewNode->data = data;

	if (pPre == NULL) { //insert before head node
		pNewNode->nextPtr = pList->pHead;
		pList->pHead = pNewNode;
		if (pList->count == 0) //Insert to empty node.
			pList->pRear = pNewNode;
	}
	else {
		pNewNode->nextPtr = pPre->nextPtr; //insert general case
		pPre->nextPtr = pNewNode;
		if (pNewNode->nextPtr == NULL) //Insert to last node
			pList->pRear = pNewNode;
	}
	pList->count++;
}

bool _List_Search(ListData* pList, ListNode** ppPre, ListNode** ppLoc, Element data) {
#define COMPARE \
((* pList->compare) (data, (*ppLoc)->data))
#define COMPARE_LAST \
 ( (* pList->compare) (data, pList->pRear->data))
	int result;

	*ppPre = NULL;
	*ppLoc = pList->pHead;
	if (pList->count == 0)
		return false;

	if (COMPARE_LAST > 0) {
		*ppPre = pList->pRear;
		*ppLoc = NULL;
		return false;
	}

	while ((result = COMPARE) > 0) {
		*ppPre = *ppLoc;
		*ppLoc = (*ppLoc)->nextPtr;
	}

	if (result == 0)
		return true;
	else
		return false;
}

void _List_Delete(ListData* pList, ListNode* pPre, ListNode* pLoc) {
	if (pPre == NULL)
		pList->pHead = pLoc->nextPtr;
	else
		pPre->nextPtr = pLoc->nextPtr;

	if (pLoc->nextPtr == NULL) //Check pLoc whether it is last node
		pList->pRear = pPre;

	free(pLoc);
	pList->count--;
}

void List_Add(ListData* pList, Element data) {
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _List_Search(pList, &pPre, &pLoc, data); //Set location.
	if (!found) //Not allow overlap.
		_List_Insert(pList, pPre, data);
}

void List_Remove(ListData* pList, Element data) {
	ListNode* pPre, * pLoc = NULL;
	bool found = _List_Search(pList, &pPre, &pLoc, data);
	if (found)
		_List_Delete(pList, pPre, pLoc);
}

bool List_Retrieve(ListData* pList, Element data) {
	ListNode* pPre = NULL, * pLoc = NULL;
	return (_List_Search(pList, &pPre, &pLoc, data));
}

bool List_Traverse(ListData* pList, int fromWhere, Element* pDataOut) {
	/*
	Should use like
	int fromWhre = 0;
	Element* pDataOut = (Element*)malloc(sizeof(Element));
	while(List_Traverse(pListData, fromWhere++, pDataOut)
		printf("%d", *pDataOut);
	*/
	if (fromWhere == 0 || pList->pPos == NULL) { //In first excution
		pList->pPos = pList->pHead;
	}
	else { //General
		pList->pPos = pList->pPos->nextPtr;
	}
	if (pList->pPos != NULL) { //General
		*pDataOut = pList->pPos->data;
		return true;
	}
	else { //In last excution
		*pDataOut = (Element)NULL;
		return false;
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

int main() {
	int fromWhere = 0;
	Element* pDataOut = (Element*)malloc(sizeof(Element));
	char** NAME_Arr;
	char NAME_buffer[7] = { '\0', };
	char IO_buffer[6] = { '\0', };
	int how_many = 0;
	scanf("%d", &how_many);

	ListData* pList = NULL;
	pList = List_Create(compare_string);
	NAME_Arr = (char**)malloc(sizeof(char*) * how_many);
	
	for (int i = 0; i < how_many; i++) {
		scanf("%s %s", NAME_buffer, IO_buffer);
		if (!strcmp(IO_buffer, "enter")) {
			NAME_Arr[i] = (char*)malloc(sizeof(NAME_buffer));
			strcpy(NAME_Arr[i], NAME_buffer);
			List_Add(pList, NAME_Arr[i]);
		}
		else if (!strcmp(IO_buffer, "leave"))
			List_Remove(pList, NAME_buffer);
	}

	int counter = 0;
	while (List_Traverse(pList, fromWhere++, pDataOut)) {
		printf("%s\n", *pDataOut);
		counter++;
	}

	for (int i = 0; i < counter; i++)
		free(NAME_Arr[i]);

	List_Destroy(pList);
	return 0;
}

