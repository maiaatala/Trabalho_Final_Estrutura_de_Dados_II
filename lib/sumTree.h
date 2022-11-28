#ifndef SUMTREE_H
#define SUMTREE_H

#include "essentials.h"
#include "list.h"

struct SumNode {
  int sum;
  struct SumNode *lft;
  struct SumNode *rgt;
  short int sumNodeHeight;
  struct ListNode *list;
};

#endif