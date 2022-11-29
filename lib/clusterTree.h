#ifndef CLUSTERTREE_H
#define CLUSTERTREE_H

#include "essentials.h"

struct ClusterNode *clusterInsert(
    struct ClusterNode *ClusterNode, unsigned int clusterSize);

struct ClusterNode *deleteClusterNode(
    struct ClusterNode *root, unsigned int clusterSize);

void clusterTreePrintInOrder(struct ClusterNode *root);

int validateClusterTree(struct ClusterNode *root);

/* funcao de busca. Retorna o cluster desejado.*/
struct ClusterNode *clusterSearch(
    struct ClusterNode *ClusterNode, unsigned int wantedClusterSize);

#endif