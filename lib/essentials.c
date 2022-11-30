#include "essentials.h"

int max(int a, int b) { return (a > b) ? a : b; }

/*
todo: Printf virar fprintf
*/

struct ClusterNode *dbInsert(struct ClusterNode *clusterNode,
    unsigned int newClustersize, long unsigned int newSum,
    unsigned int *newNumberArr) {
  struct ClusterNode *wantedClusterNode =
      clusterSearch(clusterNode, newClustersize);
  // if cluster does not yet exist, creates it
  if (wantedClusterNode == NULL) {
    clusterNode = clusterInsert(clusterNode, newClustersize);
    wantedClusterNode = clusterSearch(clusterNode, newClustersize);
    // if cluster still doesn't exist, error has occured. exit
    if (wantedClusterNode == NULL) {
      printf("%s", error_descriptions[INSERT_ERROR]);
      return clusterNode;
    }
  }

  // specific sum node to insert the array
  struct SumNode *wantedSumNode =
      sumSearch(wantedClusterNode->sumNodeRoot, newSum);
  if (wantedSumNode == NULL) {
    wantedClusterNode->sumNodeRoot =
        sumInsert(wantedClusterNode->sumNodeRoot, newSum);
    wantedSumNode = sumSearch(wantedClusterNode->sumNodeRoot, newSum);
    if (wantedSumNode == NULL) {
      printf("%s", error_descriptions[INSERT_ERROR]);
      return clusterNode;
    }
  }

  // insert list
  wantedSumNode->listRoot =
      push(wantedSumNode->listRoot, newNumberArr, newClustersize);

  // Signal that the operation has ended
  printf("%s", error_descriptions[SUCCESSFUL_OPERATION]);
  return clusterNode;
}

/* Iterates through the Secondary Tree in order */
void auxSumPrintInOrder(struct SumNode *sumRoot, unsigned int clusterSize) {
  if (sumRoot != NULL) {
    auxSumPrintInOrder(sumRoot->lft, clusterSize);
    printf("sum: %lu -> [", sumRoot->sum);
    printAllList(sumRoot->listRoot, clusterSize);
    printf("]  ");
    auxSumPrintInOrder(sumRoot->rgt, clusterSize);
  }
}

/* Iterates through the Main Tree in order */
void dbSelectInOrder(struct ClusterNode *clusterRoot) {
  if (clusterRoot != NULL) {
    dbSelectInOrder(clusterRoot->lft);
    printf("conj %u with ", clusterRoot->clusterSize);
    auxSumPrintInOrder(clusterRoot->sumNodeRoot, clusterRoot->clusterSize);
    printf("\n");
    dbSelectInOrder(clusterRoot->rgt);
  }
}
