#include "./lib/essentials.h"
#include <limits.h>

void startProgram(char *inFile, char *outFile) {
  unsigned long tam_max = 0;
  unsigned int i, clusterSize, *numberArr;
  long unsigned int sum;
  struct ClusterNode *root = NULL;

  FILE *fp = fopen(inFile, "r");
  if (fp == NULL) {
    printf("Erro: não foi possível abrir o arquivo %s", inFile);
    return;
  }

  const unsigned MAX_LENGTH = 2500000;
  char buffer[MAX_LENGTH];

  if ((fscanf(fp, "%lu", &tam_max)) == EOF) {
    printf("ERRO fscanf\n");
    exit(1);
  }
  if (tam_max > (unsigned int)UINT_MAX) {
    printf("Numbers over the limit this program can handle\n");
    exit(1);
  }

  // LOOP PARA TROCA DE LINHA
  while (fgets(buffer, MAX_LENGTH, fp)) {
    // a linha vai para token
    char *token = strtok(buffer, " ");
    // pega o resto da linha sem o op
    token = strtok(NULL, " ");

    switch (buffer[0]) {
    case '+':
      // printf("-- INSERT  ");
      clusterSize = strtoul(token, NULL, 10);
      // printf("size: %u\n", clusterSize);
      token = strtok(NULL, " "); // next char
      numberArr = (unsigned int *)malloc(sizeof(unsigned int) * clusterSize);
      sum = 0;
      for (i = 0; i < clusterSize; i++) {
        numberArr[i] = strtoul(token, NULL, 10);
        // printf("%u \t", numberArr[i]);
        sum += numberArr[i];
        token = strtok(NULL, " "); // next char
      }
      // printf("\n");
      root = dbInsert(root, clusterSize, sum, numberArr, outFile);
      break;

    case '-':
      // printf("-- DELETE  ");
      clusterSize = strtoul(token, NULL, 10);
      // printf("size: %u\n", clusterSize);
      token = strtok(NULL, " "); // next char
      numberArr = malloc(sizeof(unsigned int) * clusterSize);
      sum = 0;
      for (i = 0; i < clusterSize; i++) {
        numberArr[i] = strtoul(token, NULL, 10);
        token = strtok(NULL, " "); // next char
        // printf("%u \t", numberArr[i]);
        sum += numberArr[i];
      }
      root = dbDelete(root, clusterSize, sum, numberArr, outFile);
      break;

    case '=':
      // printf("-- SELECT  ");
      clusterSize = strtoul(token, NULL, 10);
      // printf("size: %u\n", clusterSize);
      token = strtok(NULL, " "); // next char
      numberArr = malloc(sizeof(unsigned int) * clusterSize);
      sum = 0;
      for (i = 0; i < clusterSize; i++) {
        numberArr[i] = strtoul(token, NULL, 10);
        token = strtok(NULL, " "); // next char
        // printf("%u \t", numberArr[i]);
        sum += numberArr[i];
      }
      // printf("\n");
      dbSelect(root, clusterSize, sum, numberArr, outFile);
      break;

    case '*':
      // printf("-- SELECT ALL --\n");
      dbSelectInOrder(root, outFile);
      statusToFile(outFile, OPERATION_END);
      break;

    case '0':
      return;
      break;

    default:
      continue;
      break;
    }

    // printf("end of line\n");
  }

  fclose(fp);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Rode o programa no cmd com: ./main [arq_entrada] [arq_saida]\n");
    return 1;
  }

  FILE *fInput;
  FILE *fOutput;
  fOutput = fopen(argv[2], "w");
  fclose(fOutput);

  if (!(fInput = fopen(argv[1], "a+")) || (!(fOutput = fopen(argv[2], "a+")))) {
    /* retorna erro caso arquivo de entrada ou de saida nao existam */
    printf("Erro ao abrir o arquivo!");
    exit(1);
  }
  fclose(fInput);
  fclose(fOutput);

  startProgram(argv[1], argv[2]);

  return (0);
}