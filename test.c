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

  while (getc(pont_file) != EOF) {
    contC++;
  }
  // printf("Quantidade de caractes: %d\n ", contC);
  fclose(pont_file);
  pont_file = fopen("arq.txt", "r"); //abrindo o arquivo
  
  char *vet_Arq;
  vet_Arq = malloc(sizeof(char) * contC);

  if (!vet_Arq) {
    printf("Não conseguiu alocar a memória\n");
    exit(1);
  }

  int a = 0;
  
  while (fgets(vet_Arq, contC, pont_file) != NULL) {
    int contSum = 0;

    if (a == 0) {
      a++;
      continue;
    }
    
    char operacao = vet_Arq[0]; // passando os sinais de operações para char operacao.
    char *conjunto = &vet_Arq[1]; // pegando o conjunto sem o sinal e salvando no ponteiro conjunto.

    int i = 2;
    char *value; // ponteiro para armazenar o conjunto limpo, sem o tamanho ou sinal
    
    do { //pegando a quantidade de numeros do conjuntos separadamente e armazenando em value.
      if (conjunto[i] != ' ') {
        value = &conjunto[i];
        break;
      }
      i++;
    } while (conjunto[i] != '\n');//enquanto for diferente do final da linha

    const char regex[2] = " ";
    char *token;
    token = strtok(conjunto, regex);
    int quantidadeNumeros; 
    int subconjunto;
    int entrou;
    entrou = 0;
  
    op = operacao;
    if (op == '0') {
      break;
    }
    
    int numSize = 0;
    int numQtd = 0;
    sum = 0;
    while (token != NULL) {
      
      if (entrou == 0) { 
        quantidadeNumeros = atoi(token);
        entrou++;
        token = strtok(NULL, regex);
      }
      if (numSize == 0) {
        clusterSize = quantidadeNumeros;
        numberArr = malloc(sizeof(unsigned int) * clusterSize);
        numSize++;
      
      }
      numberArr[contSum] = atoi(token);
      sum += numberArr[contSum];
      contSum++;
      root = dbInsert(root, clusterSize, sum, numberArr);
      token = strtok(NULL, regex);
    }
  }
  printf("DB: ");

  dbSelectInOrder(root);

  fclose(pont_file);
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

int main() {
  mainTest();
  // variableSizes();
}
