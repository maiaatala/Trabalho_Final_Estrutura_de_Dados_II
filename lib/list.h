#ifndef CUSTOMLIST_H
#define CUSTOMLIST_H

#include "essentials.h"

/* export functions */
struct ListNode *push(struct ListNode *listNode, unsigned int *newNumberArr,
    unsigned int arrSize);

void printAllList(struct ListNode *listRoot, unsigned int clusterSize);
// remember to pass the size of the listArr from the cluster tree.

// print all arrays in the list.

// find one arr in the list.

// find a subset in the list node. print them.

// find a superset in the list node. print them.

#endif