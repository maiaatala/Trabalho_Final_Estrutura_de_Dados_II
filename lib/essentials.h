#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include "clusterTree.h"
#include "list.h"
#include "sumTree.h"
#include <stdio.h>
#include <stdlib.h>

/* All Structs */
struct ListNode {
  struct ListNode *nxt;
  unsigned int *listArr;
};

struct SumNode {
  struct SumNode *lft;
  struct SumNode *rgt;
  short unsigned int sumNodeHeight;
  long unsigned int sum;
  struct ListNode *listRoot;
};

struct ClusterNode {
  struct ClusterNode *lft;
  struct ClusterNode *rgt;
  short unsigned int clustherHeight;
  unsigned int clusterSize;
  struct SumNode *sumNodeRoot;
};

/* All Enums */

/* discounted booleans */
typedef enum { False = 0, True = 1 } boolean;

/* statusCode for Function return organazing */
typedef enum {
  SUCCESSFUL_REMOVAL = 0,
  SUCCESSFUL_INSERT,
  INSERT_ERROR,
  SUCCESSFUL_OPERATION,
  SUCCESSFUL_TREE_SORT,
  VALUE_ALREADY_EXISTS,
  NOT_FOUND,
  TREE_IS_EMPTY,
  UNKNOWN_ERROR,
} statusCode;

/*
printf tied to the statusCode return
ex: printf("%s", error_descriptions[functionCall(params)]);
*/
static const char *error_descriptions[] = {
    [SUCCESSFUL_REMOVAL] = "0\n",
    [SUCCESSFUL_INSERT] = "0\n",
    [SUCCESSFUL_OPERATION] = "0\n",
    [NOT_FOUND] = "E\n",
    [INSERT_ERROR] = "E\n",
    [VALUE_ALREADY_EXISTS] = "E\n",
    [TREE_IS_EMPTY] = "Tree is empty and all is void.",
    [UNKNOWN_ERROR] = "E\n",
};

/* All export functions */

/* Insert all the required things */
struct ClusterNode *dbInsert(struct ClusterNode *clusterNode,
    unsigned int newClustersize, long unsigned int newSum,
    unsigned int *newNumberArr);

/* Print all */
// todo: Print the lists, not the sum nodes. one list per line.
void printInOrder(struct ClusterNode *clusterRoot);

// print do main menu

// switch case do main menu, +, -, =, *, <, >

// functions to work with all the required cases

/* All internal functions */
int max(int a, int b);

#endif