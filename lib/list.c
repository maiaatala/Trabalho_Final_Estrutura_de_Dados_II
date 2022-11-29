#include "essentials.h"

struct ListNode *newListNode(unsigned int *newNumberArr) {
  struct ListNode *newListNode =
      (struct ListNode *)malloc(sizeof(struct ListNode));
  if (newListNode == NULL) {
    printf("\nbuy more memory or stop stress testing this program");
    exit(1);
  }

  newListNode->listArr = newNumberArr;
  newListNode->nxt = NULL;
  return newListNode;
}

struct ListNode *push(struct ListNode *listNode, unsigned int *newNumberArr) {
  if (listNode == NULL) {
    return newListNode(newNumberArr);
  }
  struct ListNode *newListStart = newListNode(newNumberArr);
  newListStart->nxt = listNode;
  return newListStart;
}

void printArr(unsigned int *numberArr, unsigned int clusterSize) {
  unsigned int i;
  for (i = 0; i < clusterSize; i++) {
    printf("%u  ", numberArr[i]);
  }
  // printf("\n");
}

void printAllList(struct ListNode *listRoot, unsigned int clusterSize) {
  if (listRoot != NULL) {
    printArr(listRoot->listArr, clusterSize);
    printf("|  ");
    printAllList(listRoot->nxt, clusterSize);
  }
}