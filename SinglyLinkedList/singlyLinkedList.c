#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "singlyLinkedList.h"

SinglyLinkedListNode *singlyLinkedListGetNode(SinglyLinkedList *pList, int index);
void freeNode(SinglyLinkedListNode *pNode);

typedef struct SinglyLinkedList
{
    SinglyLinkedListNode *head;
    int length;
    int size;
} SinglyLinkedList;

typedef struct SinglyLinkedListNode
{
    SinglyLinkedListNode *next;
    void *value;
} SinglyLinkedListNode;

SinglyLinkedList *singlyLinkedListCreate(int size)
{
    SinglyLinkedList *pList = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));

    if (pList == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }

    pList->head = NULL;
    pList->length = 0;
    pList->size = size;

    return pList;
}

void *singlyLinkedListGet(SinglyLinkedList *pList, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return NULL;
    }

    SinglyLinkedListNode *pNode = singlyLinkedListGetNode(pList, index);

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }

    memcpy_s(cp, pList->size, pNode->value, pList->size);

    return cp;
}

int singlyLinkedListSet(SinglyLinkedList *pList, void *value, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return -1;
    }

    SinglyLinkedListNode *pNode = singlyLinkedListGetNode(pList, index);

    if (pNode == NULL)
    {
        return -1;
    }

    free(pNode->value);
    pNode->value = NULL;

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return -1;
    }
    memcpy_s(cp, pList->size, value, pList->size);

    pNode->value = cp;

    return 0;
}

int singlyLinkedListAdd(SinglyLinkedList *pList, void *value)
{
    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return -1;
    }

    memcpy_s(cp, pList->size, value, pList->size);

    SinglyLinkedListNode *pNodeNew = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
    if (pNodeNew == NULL)
    {
        free(cp);
        printf("Memory allocation failed!");
        return -1;
    }

    pNodeNew->value = cp;
    pNodeNew->next = NULL;

    if (pList->length == 0)
    {
        pList->head = pNodeNew;
    }
    else
    {
        SinglyLinkedListNode *node = singlyLinkedListGetNode(pList, pList->length - 1);

        if (node == NULL)
        {
            free(pNodeNew);
            return -1;
        }

        node->next = pNodeNew;
    }

    pList->length++;

    return 0;
}

int singlyLinkedListAddIndex(SinglyLinkedList *pList, void *value, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return -1;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("Memory allocation failed!");
        return -1;
    }

    memcpy_s(cp, pList->size, value, pList->size);

    SinglyLinkedListNode *pNodeNew = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
    if (pNodeNew == NULL)
    {
        free(cp);
        printf("Memory allocation failed!");
        return -1;
    }

    pNodeNew->value = cp;
    pNodeNew->next = NULL;

    SinglyLinkedListNode *pNodeP;
    SinglyLinkedListNode *pNodeC;

    if (index == 0)
    {
        pNodeP = NULL;
        pNodeC = pList->head,

        pList->head = pNodeNew;
        pNodeNew->next = pNodeC;
    }
    else
    {
        pNodeP = singlyLinkedListGetNode(pList, index - 1);

        if (pNodeP == NULL)
        {
            free(pNodeNew);
            return -1;
        }

        pNodeC = pNodeP->next;

        pNodeP->next = pNodeNew;
        pNodeNew->next = pNodeC;
    }

    pList->length++;

    return 0;
}

int singlyLinkedListRemove(SinglyLinkedList *pList, int index)
{
    if (pList->length == 0)
    {
        printf("List is empty!");
        return -1;
    }

    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return -1;
    }

    SinglyLinkedListNode *pNodeP;
    SinglyLinkedListNode *pNodeC;

    if (index == 0)
    {
        pNodeP = NULL;
        pNodeC = pList->head->next;

        freeNode(pList->head);
        pList->head = pNodeC;
    }
    else
    {
        pNodeP = singlyLinkedListGetNode(pList, index - 1);

        if (pNodeP == NULL)
        {
            return -1;
        }

        pNodeC = pNodeP->next->next;

        freeNode(pNodeP->next);
        pNodeP->next = NULL;
        pNodeP->next = pNodeC;
    }

    pList->length--;

    return 0;
}

int singlyLinkedListLength(SinglyLinkedList *pList)
{
    return pList->length;
}

int singlyLinkedListSize(SinglyLinkedList *pList)
{
    return pList->size;
}

SinglyLinkedListNode *singlyLinkedListGetHead(SinglyLinkedList *pList)
{
    return pList->head;
}

void singlyLinkedListFree(SinglyLinkedList *pList)
{
    SinglyLinkedListNode *pNode = pList->head;

    for (int i = 0; i < pList->length; i++)
    {
        SinglyLinkedListNode *pNodeTemp = pNode->next;

        freeNode(pNode);
        pNode = pNodeTemp;
    }

    free(pList);
}

SinglyLinkedListNode *singlyLinkedListGetNode(SinglyLinkedList *pList, int index)
{
    if (index >= pList->length || index < 0)
    {
        printf("Index out of bounds!");
        return NULL;
    }

    if (pList->length == 0)
    {
        printf("Can not get a node from an empty list!");
        return NULL;
    }

    SinglyLinkedListNode *node = pList->head;

    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }

    return node;
}

void freeNode(SinglyLinkedListNode *pNode)
{
    free(pNode->value);
    pNode->value = NULL;
    pNode->next = NULL;
    free(pNode);

    pNode = NULL;
}
