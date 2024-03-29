#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include "clusterTree.h"
#include "list.h"
#include "sumTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* All Structs */

/*
Dynamic List of the sets
- contains: pointer to the set array.
*/
struct ListNode {
  struct ListNode *nxt;
  unsigned int *listArr;
};

/*
Secondary Tree Struct
- key: Sum of the array
- contains: Dynamic list of the arrays of same sum
*/
struct SumNode {
  struct SumNode *lft;
  struct SumNode *rgt;
  short unsigned int sumNodeHeight;
  long unsigned int sum;
  struct ListNode *listRoot;
};

/*
Main Tree Struct
- key: size of the arr
- contains: Tree of sum
*/
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
  OPERATION_END,
  SUCCESSFUL_TREE_SORT,
  VALUE_ALREADY_EXISTS,
  NOT_FOUND,
  TREE_IS_EMPTY,
  UNKNOWN_ERROR,
  LIST_END,
} statusCode;

/*
printf tied to the statusCode return
- printf("%s", error_descriptions[functionCall(params)]);
*/
static const char *error_descriptions[] = {
    [SUCCESSFUL_REMOVAL] = "0\n",
    [SUCCESSFUL_INSERT] = "0\n",
    [SUCCESSFUL_OPERATION] = "0\n",
    [OPERATION_END] = "0\n",
    [LIST_END] = "\n",
    [NOT_FOUND] = "E\n",
    [INSERT_ERROR] = "E\n",
    [VALUE_ALREADY_EXISTS] = "E\n",
    [TREE_IS_EMPTY] = "Tree is empty and all is void.",
    [UNKNOWN_ERROR] = "E\n",
};

/* All export functions */

/*
Inserts a new array in the 'db'
requires:
 - Main tree root pointer
 - quantity of numbers in arr
 - sum of the array numbers
 - pointer of the number array
 - string of output file.
returns:
 - pointer to the updated Main tree root.
*/
struct ClusterNode *dbInsert(struct ClusterNode *clusterNode,
    unsigned int newClustersize, long unsigned int newSum,
    unsigned int *newNumberArr, char *outFile);

/*
Deletes an array in the 'db'
requires:
 - Main tree root pointer
 - quantity of numbers in arr
 - sum of the array numbers
 - pointer of the number array
 - string of output file.
returns:
 - pointer to the updated Main tree root.
*/
struct ClusterNode *dbDelete(struct ClusterNode *clusterNode,
    unsigned int toDeleteClusterSize, long unsigned int toDeleteSum,
    unsigned int *toDeleteArr, char *outFile);

/*
Prints all the sets in order of smallest -> bigger
requires:
 - Main Tree root pointer.
 - string of output file.
*/
void dbSelectInOrder(struct ClusterNode *clusterRoot, char *outFile);

/*
verifies if the array exists in the 'db'
requires:
 - Main tree root pointer
 - quantity of numbers in arr
 - sum of the array numbers
 - pointer of the number array
 - string of output file.
*/
void dbSelect(struct ClusterNode *clusterNode, unsigned int selectedClusterSize,
    long unsigned int selectedSum, unsigned int *selectedArr, char *outFile);

/*
writes the status of the operation to the output file
requires:
 - string of output file
 - status of the operation.
*/
void statusToFile(char *outFile, statusCode STATUS_DATA);

/*
writes the number of the array to the output file
requires:
 - string of output file
 - number to write
*/
void numberToFile(char *outFile, unsigned int number);

/* All internal functions */
int max(int a, int b);

#endif