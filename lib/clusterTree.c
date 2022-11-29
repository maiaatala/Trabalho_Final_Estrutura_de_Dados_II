#include "essentials.h"

int clustherHeight(struct ClusterNode *N) {
  if (N == NULL)
    return 0;
  return N->clustherHeight;
}

/* returns leftHeight -rightHeight */
int getClusterBalance(struct ClusterNode *N) {
  if (N == NULL)
    return 0;
  return clustherHeight(N->lft) - clustherHeight(N->rgt);
}

struct ClusterNode *newClusterNode(unsigned int clusterSize) {
  struct ClusterNode *ClusterNode =
      (struct ClusterNode *)malloc(sizeof(struct ClusterNode));
  ClusterNode->clusterSize = clusterSize;
  ClusterNode->lft = NULL;
  ClusterNode->rgt = NULL;
  ClusterNode->clustherHeight = 1;
  ClusterNode->sumNodeRoot = NULL;
  return (ClusterNode);
}

struct ClusterNode *clusterRgtRotate(struct ClusterNode *y) {
  struct ClusterNode *x = y->lft;
  struct ClusterNode *T2 = x->rgt;
  x->rgt = y;
  y->lft = T2;
  y->clustherHeight = max(clustherHeight(y->lft), clustherHeight(y->rgt)) + 1;
  x->clustherHeight = max(clustherHeight(x->lft), clustherHeight(x->rgt)) + 1;
  // printf("right rotated\n");
  return x;
}

struct ClusterNode *clusterLftRotate(struct ClusterNode *x) {
  struct ClusterNode *y = x->rgt;
  struct ClusterNode *T2 = y->lft;
  y->lft = x;
  x->rgt = T2;
  x->clustherHeight = max(clustherHeight(x->lft), clustherHeight(x->rgt)) + 1;
  y->clustherHeight = max(clustherHeight(y->lft), clustherHeight(y->rgt)) + 1;
  // printf("left rotated\n");
  return y;
}

struct ClusterNode *
clusterSearch(struct ClusterNode *ClusterNode, unsigned int wantedClusterSize) {
  if (ClusterNode == NULL) {
    return NULL;
  }

  if (ClusterNode->clusterSize < wantedClusterSize) {
    return clusterSearch(ClusterNode->rgt, wantedClusterSize);
  }

  if (ClusterNode->clusterSize > wantedClusterSize) {
    return clusterSearch(ClusterNode->lft, wantedClusterSize);
  }

  return ClusterNode;
}

struct ClusterNode *
clusterInsert(struct ClusterNode *ClusterNode, unsigned int clusterSize) {
  if (ClusterNode == NULL) {
    // empty node found, return new node
    return (newClusterNode(clusterSize));
  }
  if (clusterSize < ClusterNode->clusterSize) {
    // tree is not empty, recursivly look for place to insert to the lft
    // (smaller)
    ClusterNode->lft = clusterInsert(ClusterNode->lft, clusterSize);
  } else if (clusterSize > ClusterNode->clusterSize) {
    // tree is not empty, recursivly look for place to insert to the rgt
    // (bigger)
    ClusterNode->rgt = clusterInsert(ClusterNode->rgt, clusterSize);
  } else {
    // clusterSize already exists, return root
    return ClusterNode;
  }

  // AVL balancing, happens recursivly from bottom to top in the 'tree is not
  // empty' if.
  ClusterNode->clustherHeight = 1 + max(clustherHeight(ClusterNode->lft),
                                        clustherHeight(ClusterNode->rgt));
  int balance = getClusterBalance(ClusterNode);
  if (balance > 1 && clusterSize < ClusterNode->lft->clusterSize)
    return clusterRgtRotate(ClusterNode);

  if (balance < -1 && clusterSize > ClusterNode->rgt->clusterSize)
    return clusterLftRotate(ClusterNode);

  if (balance > 1 && clusterSize > ClusterNode->lft->clusterSize) {
    ClusterNode->lft = clusterLftRotate(ClusterNode->lft);
    return clusterRgtRotate(ClusterNode);
  }

  if (balance < -1 && clusterSize < ClusterNode->rgt->clusterSize) {
    ClusterNode->rgt = clusterRgtRotate(ClusterNode->rgt);
    return clusterLftRotate(ClusterNode);
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

struct ClusterNode *
deleteClusterNode(struct ClusterNode *root, unsigned int clusterSize) {
  if (root == NULL) {
    // tree is empty, nothing to delete
    return root;
  }

  if (clusterSize < root->clusterSize) {
    // tree is not empty, recursively search for node on the left (smaller)
    root->lft = deleteClusterNode(root->lft, clusterSize);
  }

  else if (clusterSize > root->clusterSize) {
    // tree is not empty, recursively search for node on the right (bigger)
    root->rgt = deleteClusterNode(root->rgt, clusterSize);
  }

  else {
    // found the node to delete
    if ((root->lft == NULL) || (root->rgt == NULL)) {
      // only 1 children or less delete
      struct ClusterNode *temp = root->lft ? root->lft : root->rgt;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      // the node has children, trade it with the leftmost children of the right
      // children
      struct ClusterNode *temp = minValueClusterNode(root->rgt);
      // ! must copy the values of temp to root
      *root->sumNodeRoot = *temp->sumNodeRoot;
      root->clusterSize = temp->clusterSize;
      // will recursively call this function to delete the leftmost children of
      // the right.
      root->rgt = deleteClusterNode(root->rgt, temp->clusterSize);
    }
  }

  if (root == NULL) {
    // delete happened and the node is null, return as is
    return root;
  }

  // delete happened with the node switching palces with any of its children,
  // rebalance
  root->clustherHeight =
      1 + max(clustherHeight(root->lft), clustherHeight(root->rgt));
  int balance = getClusterBalance(root);
  if (balance > 1 && getClusterBalance(root->lft) >= 0)
    return clusterRgtRotate(root);
  if (balance > 1 && getClusterBalance(root->lft) < 0) {
    root->lft = clusterLftRotate(root->lft);
    return clusterRgtRotate(root);
  }
  if (balance < -1 && getClusterBalance(root->rgt) <= 0)
    return clusterLftRotate(root);
  if (balance < -1 && getClusterBalance(root->rgt) > 0) {
    root->rgt = clusterRgtRotate(root->rgt);
    return clusterLftRotate(root);
  }
  return root;
}

void preOrder(struct ClusterNode *root) {
  if (root != NULL) {
    printf("%u ", root->clusterSize);
    preOrder(root->lft);
    preOrder(root->rgt);
  }
}

void posOrder(struct ClusterNode *root) {
  if (root != NULL) {
    posOrder(root->lft);
    posOrder(root->rgt);
    printf("%u ", root->clusterSize);
  }
}

void clusterTreePrintInOrder(struct ClusterNode *root) {
  if (root != NULL) {
    clusterTreePrintInOrder(root->lft);
    printf("%u ", root->clusterSize);
    clusterTreePrintInOrder(root->rgt);
  }
}

int validateClusterTree(struct ClusterNode *root) {
  if (root->lft != NULL && root->rgt != NULL) {
    printf(
        "f:%u lc: %u rc: %u\n", root->clusterSize, root->lft->clusterSize,
        root->rgt->clusterSize);
    validateClusterTree(root->lft);
    validateClusterTree(root->rgt);
  } else if (root->lft != NULL) {
    printf("f:%u lc: %u rc: NA\n", root->clusterSize, root->lft->clusterSize);
    validateClusterTree(root->lft);
  } else if (root->rgt != NULL) {
    printf("f:%u lc: NA rc: %u\n", root->clusterSize, root->rgt->clusterSize);
    validateClusterTree(root->rgt);
  }
  // if (root->lft != NULL) {
  //   if (root->lft->clusterSize < root->clusterSize) {
  //     validateTree(root->lft);
  //   } else {
  //     printf("error in %u left child %u", root->clusterSize,
  //     root->lft->clusterSize);
  //   }
  // }
  // if (root->rgt != NULL) {
  //   if (root->rgt->clusterSize > root->clusterSize) {
  //     validateTree(root->rgt);
  //   } else {
  //     printf("error in %u right child %u", root->clusterSize,
  //     root->rgt->clusterSize);
  //   }
  // }
}