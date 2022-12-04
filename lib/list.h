#ifndef CUSTOMLIST_H
#define CUSTOMLIST_H

#include "essentials.h"

/* compare results for the list arrays */
typedef enum {
  NEW_IS_SMALLER,
  EQUAL,
  NEW_IS_BIGGER,
  COMPARATOR_ERROR
} compareResults;

/* export functions */
struct ListNode *push(struct ListNode *listNode, unsigned int *newNumberArr,
    unsigned int arrSize, char *outFile);

struct ListNode *pop(struct ListNode *listNode, unsigned int *arrToDelete,
    unsigned int arrSize, char *outFile);

void printAllList(
    struct ListNode *listRoot, unsigned int clusterSize, char *outFile);

compareResults compareListArr(unsigned int *currNumberArr,
    unsigned int *newNumberArr, unsigned int currArrPos, unsigned int arrSize);

#endif