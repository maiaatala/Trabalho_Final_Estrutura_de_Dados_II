#include "./lib/essentials.h"

void clean_stdin() {
  int c;
  // limpa os \n e EOF do console, para que o fgets e pause funcionem
  // corretamente
  while ((c = getchar() != '\n' && c != EOF)) {
  }
}

int main() {
  struct ClusterNode *root = NULL;
  struct SumNode *wantedSumNode;
  char op = '+';
  unsigned int i, clusterSize, *numberArr;
  long unsigned int sum;

  do {
    printf("op:  ");
    scanf("%c", &op);
    if (op == '0') {
      break;
    }
    printf("qntNumbers:  ");
    scanf("%u", &clusterSize);
    numberArr = malloc(sizeof(unsigned int) * clusterSize);
    sum = 0;
    for (i = 0; i < clusterSize; i++) {
      printf("number %u:  ", i);
      scanf("%u", &numberArr[i]);
      sum += numberArr[i];
    }
    root = dbInsert(root, clusterSize, sum);
    wantedSumNode =
        sumSearch(clusterSearch(root, clusterSize)->sumNodeRoot, sum);
    wantedSumNode->listRoot = push(wantedSumNode->listRoot, numberArr);
    clean_stdin();
  } while (True);

  // printAllList(wantedSumNode->listRoot, 3);
  printInOrder(root);
}