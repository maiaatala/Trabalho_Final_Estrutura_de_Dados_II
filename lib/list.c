#include "essentials.h"

struct ListNode *newListNode(unsigned int *newNumberArr) {
  struct ListNode *newListNode =
      (struct ListNode *)malloc(sizeof(struct ListNode));
  if (newListNode == NULL) {
    return NULL;
  }

  newListNode->listArr = newNumberArr;
  newListNode->nxt = NULL;
  return newListNode;
}

boolean compareListArr(unsigned int *currNumberArr, unsigned int *newNumberArr,
    unsigned int currArrPos, unsigned int arrSize) {
  if (currArrPos >= arrSize) {
    return True;
  }
  if (currNumberArr[currArrPos] == newNumberArr[currArrPos]) {
    currArrPos += 1;
    return (True &&
            compareListArr(currNumberArr, newNumberArr, currArrPos, arrSize));
  }
  return False;
}

/*
Inserts a new value in the end of the dynamic list.
compares new arr to every array in the dynamic list to guarantee no duplicates
? could be an ordered list to save processing power.
! an ordered list would require way more programming logic.
is it worth it to refactor?
*/
struct ListNode *push(struct ListNode *listNode, unsigned int *newNumberArr,
    unsigned int arrSize) {
  if (listNode == NULL) {
    return newListNode(newNumberArr);
  }

  if (compareListArr(listNode->listArr, newNumberArr, 0, arrSize)) {
    printf("%s", error_descriptions[INSERT_ERROR]);
    return listNode;
  }
  listNode->nxt = push(listNode->nxt, newNumberArr, arrSize);
  return listNode;
}

void printArr(unsigned int *numberArr, unsigned int clusterSize) {
  unsigned int i;
  for (i = 0; i < clusterSize; i++) {
    printf("  %u", numberArr[i]);
  }
  // printf("\n");
}

void printAllList(struct ListNode *listRoot, unsigned int clusterSize) {
  if (listRoot != NULL) {
    printArr(listRoot->listArr, clusterSize);
    printf(",");
    printAllList(listRoot->nxt, clusterSize);
  }
}