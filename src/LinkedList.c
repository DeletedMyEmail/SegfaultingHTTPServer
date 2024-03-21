#include "../includes/LinkedList.h"
#include <stdio.h>

LinkedList* llCreate() {
    LinkedList* list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return list;
}

ListNode* createNode(void* pVal) {
    ListNode* node = malloc(sizeof(ListNode));
    node->val = pVal;
    node->next = NULL;

    return node;
}

void llPush(LinkedList* pList, void* pVal) {
    ListNode* head = pList->head;

    ListNode* node = malloc(sizeof(ListNode));
    node->val = pVal;
    node->next = NULL;

    if (head == NULL) {
        pList->head = node;
        pList->tail = node;
        pList->length = 1;
    }
    else {
        pList->tail->next = (struct ListNode *) node;
        pList->tail = node;
        ++pList->length;
    }
}

void llPushAt(LinkedList* pList, int pPosition, void* pVal) {
    if (pPosition == 0) {
        ListNode* temp = pList->head;
        pList->head = createNode(pVal);
        pList->head->next = (struct ListNode *) temp;
        ++pList->length;

        if (pList->length == 1) {
            pList->tail = pList->head;
        }
    }
    else {
        ListNode* predecessorNode = llGet(pList, pPosition - 1);
        printf("->%p\n",predecessorNode->val);
        ListNode* nextNode = (ListNode *) predecessorNode->next;
        predecessorNode->next = (struct ListNode *) createNode(pVal);
        predecessorNode->next->next = (struct ListNode *) nextNode;
        ++pList->length;
    }
}

ListNode* llPopAt(LinkedList* pList, unsigned int pPosition) {
    if (pPosition == 0 && pList->length == 1) {
        ListNode* temp = pList->head;
        pList->head = NULL;
        pList->tail = NULL;
        --pList->length;
        return temp;
    }
    else if (pPosition == 0 && pList->length > 0) {
        ListNode* temp = pList->head;
        pList->head = (ListNode *) temp->next;
        --pList->length;
        return temp;
    }
    else {
        ListNode* predecessorNode = llGet(pList, pPosition - 1);
        ListNode* nodeToPop = predecessorNode->next;
        predecessorNode->next = nodeToPop->next;
        --pList->length;
        return nodeToPop;
    }
}

ListNode* llPop(LinkedList* pList) {
    ListNode* head = pList->head;

    if (head == NULL) {
        return NULL;
    }
    else if (head->next == NULL) {
        ListNode* temp = pList->head;
        pList->head = NULL;
        pList->tail =  NULL;
        pList->length = 0;
        return temp;
    }

    ListNode* fLast = llGet(pList, pList->length-2);
    ListNode* temp = pList->tail;
    pList->tail = fLast;
    fLast->next = NULL;
    --pList->length;

    return temp;
}

ListNode* llGet(LinkedList* pList, unsigned int pPosition) {
    if (pPosition > pList->length) {
        return NULL;
    }

    ListNode* current = pList->head;
    for (size_t i = 0; i < pPosition; ++i) {
        current = current->next;
    }

    return current;
}

void llForeach(LinkedList* pList, void (*pCallback)(ListNode* pNode)) {
    ListNode* current = pList->head;

    while (current != NULL) {
        pCallback(current);
        current = (ListNode *) current->next;
    }
}

void llFree(LinkedList* pList) {
    if (pList->head == NULL) {
        free(pList);
        return;
    }

    ListNode* current = pList->head;
    do {
        ListNode* next = current->next;
        free(current->val);
        free(current);

        current = next;
    } while (current != NULL);
    free(pList);
}