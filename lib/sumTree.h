#ifndef SUMTREE_H
#define SUMTREE_H

#include "essentials.h"

struct SumNode *sumInsert(struct SumNode *SumNode, long unsigned int sum);

struct SumNode *deleteSumNode(struct SumNode *root, long unsigned int sum);

struct SumNode *sumSearch(struct SumNode *SumNode, long unsigned int wantedsum);

void sumTreePrintInOrder(struct SumNode *root);

int validateSumTree(struct SumNode *root);

#endif