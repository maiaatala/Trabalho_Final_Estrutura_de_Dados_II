#include "essentials.h"

int max(int a, int b) { return (a > b) ? a : b; }

/* //todo: Printf virar fprintf */

struct ClusterNode *dbInsert(struct ClusterNode *clusterNode,
    unsigned int newClustersize, long unsigned int newSum) {
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
  // add the sum in the specific cluster node
  wantedClusterNode->sumNodeRoot =
      sumInsert(wantedClusterNode->sumNodeRoot, newSum);
  // todo: add the arr to the list in the sumNode.
  return clusterNode;
}

void auxSumPrintInOrder(struct SumNode *sumRoot, unsigned int clusterSize) {
  if (sumRoot != NULL) {
    auxSumPrintInOrder(sumRoot->lft, clusterSize);
    printf("sum: %lu -> [", sumRoot->sum);
    printAllList(sumRoot->listRoot, clusterSize);
    printf("]  ");
    auxSumPrintInOrder(sumRoot->rgt, clusterSize);
  }
}

void printInOrder(struct ClusterNode *clusterRoot) {
  if (clusterRoot != NULL) {
    printInOrder(clusterRoot->lft);
    printf("conj %u with ", clusterRoot->clusterSize);
    auxSumPrintInOrder(clusterRoot->sumNodeRoot, clusterRoot->clusterSize);
    printf("\n");
    printInOrder(clusterRoot->rgt);
  }
}
