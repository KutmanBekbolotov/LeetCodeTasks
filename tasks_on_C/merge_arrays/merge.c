#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

ListNode* createNode(int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

ListNode* mergeKLists(ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    if (listsSize == 1) return lists[0];

    int mid = listsSize / 2;
    ListNode* left = mergeKLists(lists, mid);
    ListNode* right = mergeKLists(lists + mid, listsSize - mid);

    return mergeTwoLists(left, right);
}

void printList(ListNode* head) {
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

void freeList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    ListNode* list1 = createNode(1);
    list1->next = createNode(4);
    list1->next->next = createNode(5);

    ListNode* list2 = createNode(1);
    list2->next = createNode(3);
    list2->next->next = createNode(4);

    ListNode* list3 = createNode(2);
    list3->next = createNode(6);

    ListNode* lists[] = {list1, list2, list3};

    ListNode* result = mergeKLists(lists, 3);

    printf("Merged list: ");
    printList(result);

    freeList(result);

    return 0;
}
