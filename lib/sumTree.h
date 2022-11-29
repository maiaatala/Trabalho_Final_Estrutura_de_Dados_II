#ifndef SUMTREE_H
#define SUMTREE_H

#include "essentials.h"
#include "list.h"

struct SumNode {
  long unsigned int sum;
  struct SumNode *lft;
  struct SumNode *rgt;
  short int sumNodeHeight;
  struct ListNode *list;
};

// copy the tree frum the cluster. change the sumNode to ListNode. should be about the same tree

#endif