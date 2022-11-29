#include "essentials.h"

short unsigned int calcSumNodeHeight(struct SumNode *N) {
  if (N == NULL)
    return 0;
  return N->sumNodeHeight;
}

/* returns leftHeight -rightHeight */
int getSumBalance(struct SumNode *N) {
  if (N == NULL)
    return 0;
  return calcSumNodeHeight(N->lft) - calcSumNodeHeight(N->rgt);
}

struct SumNode *newSumNode(long unsigned int sum) {
  struct SumNode *SumNode = (struct SumNode *)malloc(sizeof(struct SumNode));
  SumNode->sum = sum;
  SumNode->lft = NULL;
  SumNode->rgt = NULL;
  SumNode->sumNodeHeight = 1;
  SumNode->listRoot = NULL;
  return (SumNode);
}

struct SumNode *sumRgtRotate(struct SumNode *y) {
  struct SumNode *x = y->lft;
  struct SumNode *T2 = x->rgt;
  x->rgt = y;
  y->lft = T2;
  y->sumNodeHeight =
      max(calcSumNodeHeight(y->lft), calcSumNodeHeight(y->rgt)) + 1;
  x->sumNodeHeight =
      max(calcSumNodeHeight(x->lft), calcSumNodeHeight(x->rgt)) + 1;
  // printf("right rotated\n");
  return x;
}

struct SumNode *sumLftRotate(struct SumNode *x) {
  struct SumNode *y = x->rgt;
  struct SumNode *T2 = y->lft;
  y->lft = x;
  x->rgt = T2;
  x->sumNodeHeight =
      max(calcSumNodeHeight(x->lft), calcSumNodeHeight(x->rgt)) + 1;
  y->sumNodeHeight =
      max(calcSumNodeHeight(y->lft), calcSumNodeHeight(y->rgt)) + 1;
  // printf("left rotated\n");
  return y;
}

struct SumNode *
sumSearch(struct SumNode *SumNode, long unsigned int wantedsum) {
  if (SumNode == NULL) {
    return NULL;
  }

  if (SumNode->sum < wantedsum) {
    return sumSearch(SumNode->rgt, wantedsum);
  }

  if (SumNode->sum > wantedsum) {
    return sumSearch(SumNode->lft, wantedsum);
  }

  return SumNode;
}

struct SumNode *sumInsert(struct SumNode *SumNode, long unsigned int sum) {
  if (SumNode == NULL) {
    // empty node found, return new node
    return (newSumNode(sum));
  }
  if (sum < SumNode->sum) {
    // tree is not empty, recursivly look for place to insert to the lft
    // (smaller)
    SumNode->lft = sumInsert(SumNode->lft, sum);
  } else if (sum > SumNode->sum) {
    // tree is not empty, recursivly look for place to insert to the rgt
    // (bigger)
    SumNode->rgt = sumInsert(SumNode->rgt, sum);
  } else {
    // sum already exists, return root
    return SumNode;
  }

  // AVL balancing, happens recursivly from bottom to top in the 'tree is not
  // empty' if.
  SumNode->sumNodeHeight =
      1 + max(calcSumNodeHeight(SumNode->lft), calcSumNodeHeight(SumNode->rgt));
  int balance = getSumBalance(SumNode);
  if (balance > 1 && sum < SumNode->lft->sum)
    return sumRgtRotate(SumNode);

  if (balance < -1 && sum > SumNode->rgt->sum)
    return sumLftRotate(SumNode);

  if (balance > 1 && sum > SumNode->lft->sum) {
    SumNode->lft = sumLftRotate(SumNode->lft);
    return sumRgtRotate(SumNode);
  }

  if (balance < -1 && sum < SumNode->rgt->sum) {
    SumNode->rgt = sumRgtRotate(SumNode->rgt);
    return sumLftRotate(SumNode);
  }
  // node is all balanced and no rotation is needed
  return SumNode;
}

struct SumNode *minValueSumNode(struct SumNode *SumNode) {
  struct SumNode *current = SumNode;
  /* loop down to find the lftmost leaf */
  while (current->lft != NULL)
    current = current->lft;
  return current;
}

struct SumNode *deleteSumNode(struct SumNode *root, long unsigned int sum) {
  if (root == NULL) {
    // tree is empty, nothing to delete
    return root;
  }

  if (sum < root->sum) {
    // tree is not empty, recursively search for node on the left (smaller)
    root->lft = deleteSumNode(root->lft, sum);
  }

  else if (sum > root->sum) {
    // tree is not empty, recursively search for node on the right (bigger)
    root->rgt = deleteSumNode(root->rgt, sum);
  }

  else {
    // found the node to delete
    if ((root->lft == NULL) || (root->rgt == NULL)) {
      // only 1 children or less delete
      struct SumNode *temp = root->lft ? root->lft : root->rgt;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      // the node has children, trade it with the leftmost children of the right
      // children
      struct SumNode *temp = minValueSumNode(root->rgt);
      // ! must copy the values of temp to root
      *root->listRoot = *temp->listRoot;
      root->sum = temp->sum;
      // will recursively call this function to delete the leftmost children of
      // the right.
      root->rgt = deleteSumNode(root->rgt, temp->sum);
    }
  }

  if (root == NULL) {
    // delete happened and the node is null, return as is
    return root;
  }

  // delete happened with the node switching palces with any of its children,
  // rebalance
  root->sumNodeHeight =
      1 + max(calcSumNodeHeight(root->lft), calcSumNodeHeight(root->rgt));
  int balance = getSumBalance(root);
  if (balance > 1 && getSumBalance(root->lft) >= 0)
    return sumRgtRotate(root);
  if (balance > 1 && getSumBalance(root->lft) < 0) {
    root->lft = sumLftRotate(root->lft);
    return sumRgtRotate(root);
  }
  if (balance < -1 && getSumBalance(root->rgt) <= 0)
    return sumLftRotate(root);
  if (balance < -1 && getSumBalance(root->rgt) > 0) {
    root->rgt = sumRgtRotate(root->rgt);
    return sumLftRotate(root);
  }
  return root;
}

void sumTreePrintInOrder(struct SumNode *root) {
  if (root != NULL) {
    sumTreePrintInOrder(root->lft);
    printf("%lu ", root->sum);
    sumTreePrintInOrder(root->rgt);
  }
}

int validateSumTree(struct SumNode *root) {
  if (root->lft != NULL && root->rgt != NULL) {
    printf(
        "f:%lu lc: %lu rc: %lu\n", root->sum, root->lft->sum, root->rgt->sum);
    validateSumTree(root->lft);
    validateSumTree(root->rgt);
  } else if (root->lft != NULL) {
    printf("f:%lu lc: %lu rc: NA\n", root->sum, root->lft->sum);
    validateSumTree(root->lft);
  } else if (root->rgt != NULL) {
    printf("f:%lu lc: NA rc: %lu\n", root->sum, root->rgt->sum);
    validateSumTree(root->rgt);
  }
  // if (root->lft != NULL) {
  //   if (root->lft->sum < root->sum) {
  //     validateTree(root->lft);
  //   } else {
  //     printf("error in %u left child %u", root->sum, root->lft->sum);
  //   }
  // }
  // if (root->rgt != NULL) {
  //   if (root->rgt->sum > root->sum) {
  //     validateTree(root->rgt);
  //   } else {
  //     printf("error in %u right child %u", root->sum, root->rgt->sum);
  //   }
  // }
}