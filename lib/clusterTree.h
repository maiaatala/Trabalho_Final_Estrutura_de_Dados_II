#ifndef CLUSTERTREE_H
#define CLUSTERTREE_H

#include "essentials.h"
#include "list.h"
#include "sumTree.h"

struct ClusterNode {
  int clusterSize;
  struct SumNode *sumNodeRoot;
  struct ClusterNode *lft;
  struct ClusterNode *rgt;
  short int clustherHeight;
};

int max(int a, int b);
struct ClusterNode *newClusterNode(int clusterSize);
struct ClusterNode *rgtRotate(struct ClusterNode *y);
struct ClusterNode *lftRotate(struct ClusterNode *x);
int getBalance(struct ClusterNode *N);
struct ClusterNode *insert(struct ClusterNode *ClusterNode, int clusterSize);
struct ClusterNode *minValueClusterNode(struct ClusterNode *ClusterNode);
struct ClusterNode *deleteClusterNode(struct ClusterNode *root, int clusterSize);
void preOrder(struct ClusterNode *root);

#endif