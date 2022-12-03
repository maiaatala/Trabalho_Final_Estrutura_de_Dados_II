#include "./lib/essentials.h"
#include <float.h>
#include <limits.h>
#include <string.h>

void clean_stdin() {
  int c;
  // limpa os \n e EOF do console, para que o fgets e pause funcionem
  // corretamente
  while ((c = getchar() != '\n' && c != EOF)) {
  }
}

void mainTest() {

  // struct ClusterNode *root = NULL;
  // struct SumNode *wantedSumNode;

  // unsigned int is = 0, clusterSize, *numberArr;
  // long unsigned int sum;
  // char c;
  struct ClusterNode *root = NULL;
  struct SumNode *wantedSumNode;
  char op = '+';
  unsigned int i, clusterSize, *numberArr;
  long unsigned int sum;
  int contC = 0;
  FILE *pont_file;
  pont_file = fopen("arq.txt", "r"); // abrindo o arquivo

  do {
    printf("op:  ");
    scanf("%c", &op);
    switch (op) {
    case '+':
      printf("-- INSERT --");
      printf("qntNumbers:  ");
      scanf("%u", &clusterSize);
      numberArr = malloc(sizeof(unsigned int) * clusterSize);
      sum = 0;
      for (i = 0; i < clusterSize; i++) {
        printf("number %u:  ", i);
        scanf("%u", &numberArr[i]);
        sum += numberArr[i];
      }
      root = dbInsert(root, clusterSize, sum, numberArr);
      break;

    case '-':
      printf("-- DELETE --");
      printf("qntNumbers:  ");
      scanf("%u", &clusterSize);
      numberArr = malloc(sizeof(unsigned int) * clusterSize);
      sum = 0;
      for (i = 0; i < clusterSize; i++) {
        printf("number %u:  ", i);
        scanf("%u", &numberArr[i]);
        sum += numberArr[i];
      }
      root = dbInsert(root, clusterSize, sum, numberArr);
      break;

    case '=':
      printf("-- SELECT --");
      printf("qntNumbers:  ");
      scanf("%u", &clusterSize);
      numberArr = malloc(sizeof(unsigned int) * clusterSize);
      sum = 0;
      for (i = 0; i < clusterSize; i++) {
        printf("number %u:  ", i);
        scanf("%u", &numberArr[i]);
        sum += numberArr[i];
      }
      root = dbInsert(root, clusterSize, sum, numberArr);
      break;

    case '*':
      printf("-- SELECT ALL --");
      dbSelectInOrder(root);

      break;
    }
    if (op == '0') {
      break;
    }

    clean_stdin();
  } while (True);

  // printAllList(wantedSumNode->listRoot, 3);
}

void variableSizes() {

  printf("CHAR_BIT    :   %d\n", CHAR_BIT);
  printf("CHAR_MAX    :   %d\n", CHAR_MAX);
  printf("CHAR_MIN    :   %d\n", CHAR_MIN);
  printf("INT_MAX     :   %d\n", INT_MAX);
  printf("INT_MIN     :   %d\n", INT_MIN);
  printf("LONG_MAX    :   %ld\n", (long)LONG_MAX);
  printf("LONG_MIN    :   %ld\n", (long)LONG_MIN);
  printf("SCHAR_MAX   :   %d\n", SCHAR_MAX);
  printf("SCHAR_MIN   :   %d\n", SCHAR_MIN);
  printf("SHRT_MAX    :   %d\n", SHRT_MAX);
  printf("SHRT_MIN    :   %d\n", SHRT_MIN);
  printf("UCHAR_MAX   :   %d\n", UCHAR_MAX);
  printf("UINT_MAX    :   %u\n", (unsigned int)UINT_MAX);
  printf("ULONG_MAX   :   %lu\n", (unsigned long)ULONG_MAX);
  printf("USHRT_MAX   :   %d\n", (unsigned short)USHRT_MAX);
}

void popTest() {
  struct ListNode *root = NULL;
  char op = '+';
  unsigned int i, clusterSize = 2, *numberArr;
  long unsigned int sum;

  do {
    printf("op:  ");
    scanf("%c", &op);
    if (op == '0') {
      break;
    }

    if (op == '+') {
      numberArr = malloc(sizeof(unsigned int) * clusterSize);
      sum = 0;
      for (i = 0; i < clusterSize; i++) {
        printf("number %u:  ", i);
        scanf("%u", &numberArr[i]);
        sum += numberArr[i];
      }
      root = push(root, numberArr, clusterSize);
    }
    if (op == '-') {
      numberArr = malloc(sizeof(unsigned int) * clusterSize);
      sum = 0;
      for (i = 0; i < clusterSize; i++) {
        printf("number %u:  ", i);
        scanf("%u", &numberArr[i]);
        sum += numberArr[i];
      }
      root = pop(root, numberArr, clusterSize);
    }
    clean_stdin();
  } while (True);

  printAllList(root, clusterSize);
  printf("\n");
}

int main() {
  // mainTest();
  popTest();
  // variableSizes();
}
