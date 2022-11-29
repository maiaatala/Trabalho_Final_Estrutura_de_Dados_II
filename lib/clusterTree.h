#ifndef CLUSTERTREE_H
#define CLUSTERTREE_H

#include "essentials.h"
#include "list.h"
#include "sumTree.h"

struct ClusterNode {
  unsigned int clusterSize;
  struct SumNode *sumNodeRoot;
  struct ClusterNode *lft;
  struct ClusterNode *rgt;
  short int clustherHeight;
};

int max(int a, int b);

struct ClusterNode *newClusterNode(unsigned int clusterSize);

/* returns leftHeight -rightHeight */
int getBalance(struct ClusterNode *N);

struct ClusterNode *insert(struct ClusterNode *ClusterNode, unsigned int clusterSize);

struct ClusterNode *deleteClusterNode(struct ClusterNode *root, unsigned int clusterSize);

void inOrder(struct ClusterNode *root);

int validateTree(struct ClusterNode *root);

// funcao de busca.
struct ClusterNode *search(struct ClusterNode *ClusterNode, unsigned int wantedClusterSize);

#endif