#include "essentials.h"

int max(int a, int b) { return (a > b) ? a : b; }

void statusToFile(char *outFile, statusCode STATUS_DATA) {
  FILE *fp = fopen(outFile, "a");
  if (fp == NULL) {
    printf("error writing output data\n");
    exit(1);
  }
  fprintf(fp, "%s", error_descriptions[STATUS_DATA]);
  fclose(fp);
}

void numberToFile(char *outFile, unsigned int number) {
  FILE *fp = fopen(outFile, "a");
  if (fp == NULL) {
    printf("error writing output data\n");
    exit(1);
  }
  fprintf(fp, "%u ", number);
  fclose(fp);
}

struct ClusterNode *dbInsert(struct ClusterNode *clusterNode,
    unsigned int newClustersize, long unsigned int newSum,
    unsigned int *newNumberArr, char *outFile) {
  struct ClusterNode *wantedClusterNode =
      clusterSearch(clusterNode, newClustersize);
  // if cluster does not yet exist, creates it
  if (wantedClusterNode == NULL) {
    clusterNode = clusterInsert(clusterNode, newClustersize);
    wantedClusterNode = clusterSearch(clusterNode, newClustersize);
    // if cluster still doesn't exist, error has occured. exit
    if (wantedClusterNode == NULL) {
      statusToFile(outFile, INSERT_ERROR);
      statusToFile(outFile, OPERATION_END);
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
      statusToFile(outFile, INSERT_ERROR);
      statusToFile(outFile, OPERATION_END);
      return clusterNode;
    }
  }

  // insert list
  wantedSumNode->listRoot =
      push(wantedSumNode->listRoot, newNumberArr, newClustersize, outFile);

  // Signal that the operation has ended
  statusToFile(outFile, OPERATION_END);
  return clusterNode;
}

void auxPrintArr(
    unsigned int *numberArr, unsigned int clusterSize, char *outFile) {
  unsigned int i;
  FILE *fp = fopen(outFile, "a");
  if (fp == NULL) {
    printf("error writing output data\n");
    exit(1);
  }
  for (i = 0; i < clusterSize; i++) {
    fprintf(fp, "%u ", numberArr[i]);
    // printf("  %u", numberArr[i]);
  }
  fprintf(fp, "\n");
  fclose(fp);
}

void auxPrintAllList(
    struct ListNode *listRoot, unsigned int clusterSize, char *outFile) {
  if (listRoot != NULL) {
    auxPrintArr(listRoot->listArr, clusterSize, outFile);
    // printf(",");
    auxPrintAllList(listRoot->nxt, clusterSize, outFile);
  }
}

/* Iterates through the Secondary Tree in order */
void auxSumPrintInOrder(
    struct SumNode *sumRoot, unsigned int clusterSize, char *outFile) {
  if (sumRoot != NULL) {
    auxSumPrintInOrder(sumRoot->lft, clusterSize, outFile);
    // printf("sum: %lu -> [", sumRoot->sum);
    auxPrintAllList(sumRoot->listRoot, clusterSize, outFile);
    // printf("]  ");
    auxSumPrintInOrder(sumRoot->rgt, clusterSize, outFile);
  }
}

/* Iterates through the Main Tree in order */
void dbSelectInOrder(struct ClusterNode *clusterRoot, char *outFile) {
  if (clusterRoot != NULL) {
    dbSelectInOrder(clusterRoot->lft, outFile);
    // printf("conj %u with ", clusterRoot->clusterSize);
    auxSumPrintInOrder(
        clusterRoot->sumNodeRoot, clusterRoot->clusterSize, outFile);
    // printf("\n");
    dbSelectInOrder(clusterRoot->rgt, outFile);
  }
}

struct ClusterNode *dbDelete(struct ClusterNode *clusterNode,
    unsigned int toDeleteClusterSize, long unsigned int toDeleteSum,
    unsigned int *toDeleteArr, char *outFile) {
  struct ClusterNode *wantedClusterNode =
      clusterSearch(clusterNode, toDeleteClusterSize);
  // if cluster does not yet exist, we won't delete anything.
  if (wantedClusterNode == NULL) {
    statusToFile(outFile, INSERT_ERROR);
    statusToFile(outFile, OPERATION_END);
    return clusterNode;
  }

  // if sum node does not yet exist, we won't delete anything
  struct SumNode *wantedSumNode =
      sumSearch(wantedClusterNode->sumNodeRoot, toDeleteSum);
  if (wantedSumNode == NULL) {
    // if the sum node does not yet exist, we won't delete anything
    statusToFile(outFile, INSERT_ERROR);
    statusToFile(outFile, OPERATION_END);
    return clusterNode;
  }

  // attemps to delete it from the list
  wantedSumNode->listRoot =
      pop(wantedSumNode->listRoot, toDeleteArr, toDeleteClusterSize, outFile);

  // checks if the specific sum tree became empty after the deletion
  if (wantedSumNode->listRoot == NULL) {
    // deletes the sum node
    wantedClusterNode->sumNodeRoot =
        deleteSumNode(wantedClusterNode->sumNodeRoot, toDeleteSum);
  }

  // checks if the cluster node became empty after the deletion
  if (wantedClusterNode->sumNodeRoot == NULL) {
    // deletes the cluster node from the cluster tree
    clusterNode = deleteClusterNode(clusterNode, toDeleteClusterSize);
  }

  // Signal that the operation has ended
  statusToFile(outFile, OPERATION_END);
  return clusterNode;
}

/*
function to search the array in the dynamic list, prints resuls directly to
the file
*/
void findArrInList(struct ListNode *listNode, unsigned int *selectedArr,
    unsigned int arrSize, char *outFile) {
  if (listNode == NULL) {
    statusToFile(outFile, INSERT_ERROR);
    statusToFile(outFile, OPERATION_END);
    return;
  }

  switch (compareListArr(listNode->listArr, selectedArr, 0, arrSize)) {
  case EQUAL:
    statusToFile(outFile, OPERATION_END);
    break;

  case NEW_IS_BIGGER:
    findArrInList(listNode->nxt, selectedArr, arrSize, outFile);
    break;

  default:
    statusToFile(outFile, INSERT_ERROR);
    statusToFile(outFile, OPERATION_END);
    break;
  }
}

void dbSelect(struct ClusterNode *clusterNode, unsigned int selectedClusterSize,
    long unsigned int selectedSum, unsigned int *selectedArr, char *outFile) {
  // searches for the selected cluster node
  struct ClusterNode *wantedClusterNode =
      clusterSearch(clusterNode, selectedClusterSize);
  // if cluster does not yet exist, select error.
  if (wantedClusterNode == NULL) {
    statusToFile(outFile, INSERT_ERROR);
    statusToFile(outFile, OPERATION_END);
    return;
  }

  // searches for the selected sum node
  struct SumNode *wantedSumNode =
      sumSearch(wantedClusterNode->sumNodeRoot, selectedSum);
  if (wantedSumNode == NULL) {
    // if the sum node does not yet exist, select error.
    statusToFile(outFile, INSERT_ERROR);
    statusToFile(outFile, OPERATION_END);
    return;
  }

  /* calls function to search the list */
  findArrInList(
      wantedSumNode->listRoot, selectedArr, selectedClusterSize, outFile);
}
