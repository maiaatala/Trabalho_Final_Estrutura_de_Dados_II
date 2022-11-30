#include "./lib/essentials.h"

int main() {
  // todo: check if first number is bigger than the unsigned int number

  struct ClusterNode *root = NULL;

  root = dbInsert(root, 3, 40);
  root = dbInsert(root, 3, 90);
  root = dbInsert(root, 4, 55);
  root = dbInsert(root, 7, 10);
  root = dbInsert(root, 7, 800);
  root = dbInsert(root, 7, 500);
  root = dbInsert(root, 5, 35);
  root = dbInsert(root, 5, 50);
  root = dbInsert(root, 5, 60);

  printInOrder(root);
  // clusterTreePrintInOrder(root);
  // printf("\n");
  // struct ClusterNode *wantedNode = clusterSearch(root, 5);
  // sumTreePrintInOrder(wantedNode->sumNodeRoot);
  // printf("\n");
  // wantedNode = clusterSearch(root, 3);
  // sumTreePrintInOrder(wantedNode->sumNodeRoot);
  // printf("\n");
  // wantedNode = clusterSearch(root, 7);
  // sumTreePrintInOrder(wantedNode->sumNodeRoot);
  // printf("\n");
}