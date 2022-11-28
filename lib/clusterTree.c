#include "clusterTree.h"

int max(int a, int b) { return (a > b) ? a : b; }

int clustherHeight(struct ClusterNode *N) {
  if (N == NULL)
    return 0;
  return N->clustherHeight;
}

struct ClusterNode *newClusterNode(int clusterSize) {
  struct ClusterNode *ClusterNode = (struct ClusterNode *)malloc(sizeof(struct ClusterNode));
  ClusterNode->clusterSize = clusterSize;
  ClusterNode->lft = NULL;
  ClusterNode->rgt = NULL;
  ClusterNode->clustherHeight = 1;
  ClusterNode->sumNodeRoot = NULL;
  return (ClusterNode);
}

struct ClusterNode *rgtRotate(struct ClusterNode *y) {
  struct ClusterNode *x = y->lft;
  struct ClusterNode *T2 = x->rgt;
  x->rgt = y;
  y->lft = T2;
  y->clustherHeight = max(clustherHeight(y->lft), clustherHeight(y->rgt)) + 1;
  x->clustherHeight = max(clustherHeight(x->lft), clustherHeight(x->rgt)) + 1;
  printf("right rotated\n");
  return x;
}

struct ClusterNode *lftRotate(struct ClusterNode *x) {
  struct ClusterNode *y = x->rgt;
  struct ClusterNode *T2 = y->lft;
  y->lft = x;
  x->rgt = T2;
  x->clustherHeight = max(clustherHeight(x->lft), clustherHeight(x->rgt)) + 1;
  y->clustherHeight = max(clustherHeight(y->lft), clustherHeight(y->rgt)) + 1;
  printf("left rotated\n");
  return y;
}

int getBalance(struct ClusterNode *N) {
  if (N == NULL)
    return 0;
  return clustherHeight(N->lft) - clustherHeight(N->rgt);
}

struct ClusterNode *insert(struct ClusterNode *ClusterNode, int clusterSize) {
  if (ClusterNode == NULL) {
    // empty node found, return new node
    return (newClusterNode(clusterSize));
  }
  if (clusterSize < ClusterNode->clusterSize) {
    // tree is not empty, recursivly look for place to insert to the lft (smaller)
    ClusterNode->lft = insert(ClusterNode->lft, clusterSize);
  } else if (clusterSize > ClusterNode->clusterSize) {
    // tree is not empty, recursivly look for place to insert to the rgt (bigger)
    ClusterNode->rgt = insert(ClusterNode->rgt, clusterSize);
  } else {
    // clusterSize already exists, return root
    return ClusterNode;
  }

  // AVL balancing, happens recursivly from bottom to top in the 'tree is not empty' if.
  ClusterNode->clustherHeight = 1 + max(clustherHeight(ClusterNode->lft), clustherHeight(ClusterNode->rgt));
  int balance = getBalance(ClusterNode);
  if (balance > 1 && clusterSize < ClusterNode->lft->clusterSize)
    return rgtRotate(ClusterNode);

  if (balance < -1 && clusterSize > ClusterNode->rgt->clusterSize)
    return lftRotate(ClusterNode);

  if (balance > 1 && clusterSize > ClusterNode->lft->clusterSize) {
    ClusterNode->lft = lftRotate(ClusterNode->lft);
    return rgtRotate(ClusterNode);
  }

  if (balance < -1 && clusterSize < ClusterNode->rgt->clusterSize) {
    ClusterNode->rgt = rgtRotate(ClusterNode->rgt);
    return lftRotate(ClusterNode);
  }
  // node is all balanced and no rotation is needed
  return ClusterNode;
}

struct ClusterNode *minValueClusterNode(struct ClusterNode *ClusterNode) {
  struct ClusterNode *current = ClusterNode;
  /* loop down to find the lftmost leaf */
  while (current->lft != NULL)
    current = current->lft;
  return current;
}

struct ClusterNode *deleteClusterNode(struct ClusterNode *root, int clusterSize) {
  if (root == NULL)
    return root;
  if (clusterSize < root->clusterSize)
    root->lft = deleteClusterNode(root->lft, clusterSize);
  else if (clusterSize > root->clusterSize)
    root->rgt = deleteClusterNode(root->rgt, clusterSize);
  else {
    if ((root->lft == NULL) || (root->rgt == NULL)) {
      struct ClusterNode *temp = root->lft ? root->lft : root->rgt;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      struct ClusterNode *temp = minValueClusterNode(root->rgt);
      root->clusterSize = temp->clusterSize;
      root->rgt = deleteClusterNode(root->rgt, temp->clusterSize);
    }
  }
  if (root == NULL)
    return root;
  root->clustherHeight = 1 + max(clustherHeight(root->lft), clustherHeight(root->rgt));
  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->lft) >= 0)
    return rgtRotate(root);
  if (balance > 1 && getBalance(root->lft) < 0) {
    root->lft = lftRotate(root->lft);
    return rgtRotate(root);
  }
  if (balance < -1 && getBalance(root->rgt) <= 0)
    return lftRotate(root);
  if (balance < -1 && getBalance(root->rgt) > 0) {
    root->rgt = rgtRotate(root->rgt);
    return lftRotate(root);
  }
  return root;
}

void preOrder(struct ClusterNode *root) {
  if (root != NULL) {
    printf("%d ", root->clusterSize);
    preOrder(root->lft);
    preOrder(root->rgt);
  }
}