#include "clusterTree.h"

int max(int a, int b) { return (a > b) ? a : b; }

int clustherHeight(struct ClusterNode *N) {
  if (N == NULL)
    return 0;
  return N->clustherHeight;
}

int getBalance(struct ClusterNode *N) {
  if (N == NULL)
    return 0;
  return clustherHeight(N->lft) - clustherHeight(N->rgt);
}

struct ClusterNode *newClusterNode(unsigned int clusterSize) {
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

struct ClusterNode *search(struct ClusterNode *ClusterNode, unsigned int wantedClusterSize) {
  if (ClusterNode == NULL) {
    return NULL;
  }

  if (ClusterNode->clusterSize < wantedClusterSize) {
    return search(ClusterNode->rgt, wantedClusterSize);
  }

  if (ClusterNode->clusterSize > wantedClusterSize) {
    return search(ClusterNode->lft, wantedClusterSize);
  }

  return ClusterNode;
}

struct ClusterNode *insert(struct ClusterNode *ClusterNode, unsigned int clusterSize) {
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

struct ClusterNode *deleteClusterNode(struct ClusterNode *root, unsigned int clusterSize) {
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
      // the node has children, trade it with the leftmost children of the right children
      struct ClusterNode *temp = minValueClusterNode(root->rgt);
      // ! must copy the values of temp to root
      *root->sumNodeRoot = *temp->sumNodeRoot;
      root->clusterSize = temp->clusterSize;
      // will recursively call this function to delete the leftmost children of the right.
      root->rgt = deleteClusterNode(root->rgt, temp->clusterSize);
    }
  }

  if (root == NULL) {
    // delete happened and the node is null, return as is
    return root;
  }

  // delete happened with the node switching palces with any of its children, rebalance
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

void inOrder(struct ClusterNode *root) {
  if (root != NULL) {
    inOrder(root->lft);
    printf("%u ", root->clusterSize);
    inOrder(root->rgt);
  }
}

int validateTree(struct ClusterNode *root) {
  if (root->lft != NULL && root->rgt != NULL) {
    printf("f:%u lc: %u rc: %u\n", root->clusterSize, root->lft->clusterSize, root->rgt->clusterSize);
    validateTree(root->lft);
    validateTree(root->rgt);
  } else if (root->lft != NULL) {
    printf("f:%u lc: %u rc: NA\n", root->clusterSize, root->lft->clusterSize);
    validateTree(root->lft);
  } else if (root->rgt != NULL) {
    printf("f:%u lc: NA rc: %u\n", root->clusterSize, root->rgt->clusterSize);
    validateTree(root->rgt);
  }
  // if (root->lft != NULL) {
  //   if (root->lft->clusterSize < root->clusterSize) {
  //     validateTree(root->lft);
  //   } else {
  //     printf("error in %u left child %u", root->clusterSize, root->lft->clusterSize);
  //   }
  // }
  // if (root->rgt != NULL) {
  //   if (root->rgt->clusterSize > root->clusterSize) {
  //     validateTree(root->rgt);
  //   } else {
  //     printf("error in %u right child %u", root->clusterSize, root->rgt->clusterSize);
  //   }
  // }
}