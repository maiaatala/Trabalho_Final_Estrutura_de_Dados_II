#include "list.h"
#include "essentials.h"

/*
todo: Printf virar fprintf
*/

struct ListNode *newListNode(
    unsigned int *newNumberArr, struct ListNode *nextNode) {
  struct ListNode *newListNode =
      (struct ListNode *)malloc(sizeof(struct ListNode));
  if (newListNode == NULL) {
    printf("%s", error_descriptions[INSERT_ERROR]);
    return NULL;
  }

  newListNode->listArr = newNumberArr;
  newListNode->nxt = nextNode;
  return newListNode;
}

compareResults compareListArr(unsigned int *currNumberArr,
    unsigned int *newNumberArr, unsigned int currArrPos, unsigned int arrSize) {
  if (currArrPos >= arrSize) {
    return EQUAL;
  }

  // printf("is %u == %u\n", newNumberArr[currArrPos],
  // currNumberArr[currArrPos]);
  if (newNumberArr[currArrPos] > currNumberArr[currArrPos]) {
    return NEW_IS_BIGGER;
  }

  if (newNumberArr[currArrPos] == currNumberArr[currArrPos]) {
    return (
        compareListArr(currNumberArr, newNumberArr, currArrPos + 1, arrSize));
  }

  return NEW_IS_SMALLER;
}

/*
Inserts a new value in an ordered dynamic list.
compares new arr to every smaller array in the dynamic list to guarantee no
duplicates inserts new node as soon as it finds null node or smaller value
*/
struct ListNode *push(struct ListNode *listNode, unsigned int *newNumberArr,
    unsigned int arrSize, char *outFile) {
  if (listNode == NULL) {
    // printf("null on push manual flag\n");
    return newListNode(newNumberArr, listNode);
  }

  switch (compareListArr(listNode->listArr, newNumberArr, 0, arrSize)) {
  case EQUAL:
    statusToFile(outFile, INSERT_ERROR);
    break;

  case NEW_IS_BIGGER:
    // continue to iterate throught the list
    listNode->nxt = push(listNode->nxt, newNumberArr, arrSize, outFile);
    break;

  case NEW_IS_SMALLER:
    // new list array is smaller than the current array, insert new array
    // pointing to current one
    listNode = newListNode(newNumberArr, listNode);
    break;

  default:
    statusToFile(outFile, INSERT_ERROR);
    break;
  }
  return listNode;
}

struct ListNode *pop(struct ListNode *listNode, unsigned int *arrToDelete,
    unsigned int arrSize, char *outFile) {
  if (listNode == NULL) {
    // list is empty or value wasn't found
    statusToFile(outFile, INSERT_ERROR);
    return listNode;
  }

  switch (compareListArr(listNode->listArr, arrToDelete, 0, arrSize)) {
  case EQUAL:;
    // delete node
    struct ListNode *tempToFree = NULL;
    tempToFree = listNode;
    listNode = listNode->nxt;
    free(tempToFree);
    break;

  case NEW_IS_BIGGER:
    // continue to iterate throught the list
    listNode->nxt = pop(listNode->nxt, arrToDelete, arrSize, outFile);
    break;

  case NEW_IS_SMALLER:
    // wont find an equal value since all the next ones will be bigger than the
    // current value
    statusToFile(outFile, INSERT_ERROR);
    break;

  default:
    statusToFile(outFile, INSERT_ERROR);
    break;
  }
  return listNode;
}

void printArr(
    unsigned int *numberArr, unsigned int clusterSize, char *outFile) {
  unsigned int i;
  for (i = 0; i < clusterSize; i++) {
    numberToFile(outFile, numberArr[i]);
    // printf("  %u", numberArr[i]);
  }
  statusToFile(outFile, LIST_END);
}

void printAllList(
    struct ListNode *listRoot, unsigned int clusterSize, char *outFile) {
  if (listRoot != NULL) {
    printArr(listRoot->listArr, clusterSize, outFile);
    // printf(",");
    printAllList(listRoot->nxt, clusterSize, outFile);
  }
}