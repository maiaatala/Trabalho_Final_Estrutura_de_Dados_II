#include "./lib/essentials.h"

int main() {
  struct ClusterNode *root = NULL;
  root = clusterInsert(root, 27);
  root = clusterInsert(root, 9);
  root = clusterInsert(root, 19);
  root = clusterInsert(root, 91);
  root = clusterInsert(root, 90);
  // root = clusterInsert(root, 72);
  // validateTree(root);
  printf("The output of an AVL tree in inOrder form: \n");
  clusterTreePrintInOrder(root);
  printf("\n");
  struct ClusterNode *wantedNode = clusterSearch(root, 90);
  printf("wanted node clusterSize: %u and height: %d\n",
      wantedNode->clusterSize, wantedNode->clustherHeight);
  printf("wanted node leftchild: %u \n", wantedNode->lft->clusterSize);
  // printf("\n");
  // root = deleteClusterNode(root, 9);
  // root = deleteClusterNode(root, 72);
  // printf("The tree in preOrder traversal outputs after deletion: \n");
  // preOrder(root);
  // printf("\n");
  // root = clusterInsert(root, 1);
  // root = clusterInsert(root, 2709);
  // printf("The tree in preOrder traversal outputs 2 more inserts: \n");
  // preOrder(root);
  // printf("\n");
  // return 0;
}