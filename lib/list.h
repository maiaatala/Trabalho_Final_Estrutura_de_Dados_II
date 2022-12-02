#ifndef CUSTOMLIST_H
#define CUSTOMLIST_H

#include "essentials.h"
/* export functions */
struct ListNode *push(struct ListNode *listNode, unsigned int *newNumberArr,
    unsigned int arrSize);

struct ListNode *pop(
    struct ListNode *listNode, unsigned int *arrToDelete, unsigned int arrSize);

void printAllList(struct ListNode *listRoot, unsigned int clusterSize);

#endif