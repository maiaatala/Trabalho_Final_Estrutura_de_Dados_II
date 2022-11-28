#include "./lib/clusterTree.h"
#include "./lib/essentials.h"
#include "./lib/list.h"
#include "./lib/sumTree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct ClusterNode *root = NULL;
  root = insert(root, 27);
  root = insert(root, 9);
  root = insert(root, 19);
  root = insert(root, 91);
  root = insert(root, 90);
  root = insert(root, 72);
  printf("The output of an AVL tree in preOrder form: \n");
  preOrder(root);
  printf("\n");
  root = deleteClusterNode(root, 9);
  root = deleteClusterNode(root, 72);
  printf("The tree in preOrder traversal outputs after deletion: \n");
  preOrder(root);
  printf("\n");
  root = insert(root, 1);
  root = insert(root, 2709);
  printf("The tree in preOrder traversal outputs 2 more inserts: \n");
  preOrder(root);
  printf("\n");
  return 0;
}