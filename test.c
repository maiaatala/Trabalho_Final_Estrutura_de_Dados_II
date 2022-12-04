#include "./lib/essentials.h"
#include <float.h>
#include <limits.h>

void clean_stdin() {
  int c;
  // limpa os \n e EOF do console, para que o fgets e pause funcionem
  // corretamente
  while ((c = getchar() != '\n' && c != EOF)) {
  }
}

// void mainTest() {
//   struct ClusterNode *root = NULL;
//   struct SumNode *wantedSumNode;
//   char op = '+';
//   unsigned int i, clusterSize, *numberArr;
//   long unsigned int sum;
//   char *outFile = "output.txt";

//   do {
//     printf("op:  ");
//     scanf("%c", &op);
//     switch (op) {
//     case '+':
//       printf("-- INSERT --\n");
//       printf("qntNumbers:  ");
//       scanf("%u", &clusterSize);
//       numberArr = malloc(sizeof(unsigned int) * clusterSize);
//       sum = 0;
//       for (i = 0; i < clusterSize; i++) {
//         printf("number %u:  ", i);
//         scanf("%u", &numberArr[i]);
//         sum += numberArr[i];
//       }
//       root = dbInsert(root, clusterSize, sum, numberArr, outFile);
//       break;

//     case '-':
//       printf("-- DELETE --\n");
//       printf("qntNumbers:  ");
//       scanf("%u", &clusterSize);
//       numberArr = malloc(sizeof(unsigned int) * clusterSize);
//       sum = 0;
//       for (i = 0; i < clusterSize; i++) {
//         printf("number %u:  ", i);
//         scanf("%u", &numberArr[i]);
//         sum += numberArr[i];
//       }
//       root = dbInsert(root, clusterSize, sum, numberArr, outFile);
//       break;

//     case '=':
//       printf("-- SELECT --\n");
//       printf("qntNumbers:  ");
//       scanf("%u", &clusterSize);
//       numberArr = malloc(sizeof(unsigned int) * clusterSize);
//       sum = 0;
//       for (i = 0; i < clusterSize; i++) {
//         printf("number %u:  ", i);
//         scanf("%u", &numberArr[i]);
//         sum += numberArr[i];
//       }
//       root = dbInsert(root, clusterSize, sum, numberArr, outFile);
//       break;

//     case '*':
//       printf("-- SELECT ALL --\n");
//       dbSelectInOrder(root);

//       break;
//     }
//     if (op == '0') {
//       break;
//     }

//     clean_stdin();
//   } while (True);

//   // printAllList(wantedSumNode->listRoot, 3);
// }

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

// void popTest() {
//   struct ListNode *root = NULL;
//   char op = '+';
//   unsigned int i, clusterSize = 2, *numberArr;
//   long unsigned int sum;
//   char *outFile = "output.txt";

//   do {
//     printf("op:  ");
//     scanf("%c", &op);
//     if (op == '0') {
//       break;
//     }

//     if (op == '+') {
//       numberArr = malloc(sizeof(unsigned int) * clusterSize);
//       sum = 0;
//       for (i = 0; i < clusterSize; i++) {
//         printf("number %u:  ", i);
//         scanf("%u", &numberArr[i]);
//         sum += numberArr[i];
//       }
//       root = push(root, numberArr, clusterSize, outFile);
//     }
//     if (op == '-') {
//       numberArr = malloc(sizeof(unsigned int) * clusterSize);
//       sum = 0;
//       for (i = 0; i < clusterSize; i++) {
//         printf("number %u:  ", i);
//         scanf("%u", &numberArr[i]);
//         sum += numberArr[i];
//       }
//       root = pop(root, numberArr, clusterSize);
//     }
//     clean_stdin();
//   } while (True);

//   printAllList(root, clusterSize);
//   printf("\n");
// }

// void ikaroTest() {
//   char *outFile = "output.txt";

//   // struct ClusterNode *root = NULL;
//   struct ClusterNode *root = NULL;
//   struct SumNode *wantedSumNode;
//   char op = '+';
//   unsigned int i, clusterSize, *numberArr;
//   long unsigned int sum;
//   // int contC = 0;
//   FILE *pont_file;
//   pont_file = fopen("arq_com_as_operacoes.txt", "r"); // abrindo o arquivo
//   const unsigned MAX_LENGTH = 256;

//   //! ???
//   // while (getc(pont_file) != EOF) {
//   //   contC++;
//   // }
//   // printf("Quantidade de caractes: %d\n ", contC);
//   // fclose(pont_file);
//   // pont_file = fopen("arq_com_as_operacoes.txt", "r"); // abrindo o arquivo

//   char *vet_Arq;
//   vet_Arq = malloc(sizeof(char) * MAX_LENGTH);

//   if (!vet_Arq) {
//     printf("Não conseguiu alocar a memória\n");
//     exit(1);
//   }

//   int a = 0;

//   while (fgets(vet_Arq, MAX_LENGTH, pont_file) != NULL) {
//     int contSum = 0;

//     if (a == 0) {
//       a++;
//       continue;
//     }

//     char operacao =
//         vet_Arq[0]; // passando os sinais de operações para char operacao.
//     char *conjunto = &vet_Arq[1]; // pegando o conjunto sem o sinal e
//     salvando
//                                   // no ponteiro conjunto.

//     int i = 2;
//     char *value; // ponteiro para armazenar o conjunto limpo, sem o tamanho
//     ou
//                  // sinal

//     do { // pegando a quantidade de numeros do conjuntos separadamente e
//          // armazenando em value.
//       if (conjunto[i] != ' ') {
//         value = &conjunto[i];
//         break;
//       }
//       i++;
//     } while (conjunto[i] != '\n'); // enquanto for diferente do final da
//     linha

//     const char regex[2] = " ";
//     char *token;
//     token = strtok(conjunto, regex);
//     int quantidadeNumeros;
//     int subconjunto;
//     int entrou;
//     entrou = 0;

//     op = operacao;
//     if (op == '0') {
//       break;
//     }

//     int numSize = 0;
//     int numQtd = 0;
//     sum = 0;
//     while (token != NULL) {

//       if (entrou == 0) {
//         quantidadeNumeros = atoi(token);
//         entrou++;
//         token = strtok(NULL, regex);
//       }
//       if (numSize == 0) {
//         clusterSize = quantidadeNumeros;
//         numberArr = malloc(sizeof(unsigned int) * clusterSize);
//         numSize++;
//       }
//       numberArr[contSum] = atoi(token);
//       sum += numberArr[contSum];
//       contSum++;
//       root = dbInsert(root, clusterSize, sum, numberArr, outFile);
//       token = strtok(NULL, regex);
//     }
//   }
//   printf("DB: ");

//   dbSelectInOrder(root);

//   fclose(pont_file);
// }

void textTest(char *inFile, char *outFile) {
  // char *nome_arquivo = "arq_com_as_operacoes.txt";
  // char *nome_arquivo = "test.txt";
  // char *nome_arquivo = "entrada_1k.txt";
  /* file related variables */
  unsigned long tam_max = 0;
  /* db related variables */
  // int op;
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
      printf("-- INSERT  ");
      clusterSize = strtoul(token, NULL, 10);
      printf("size: %u\n", clusterSize);
      token = strtok(NULL, " "); // next char
      numberArr =
          (unsigned int *)malloc(sizeof(unsigned int) * 2 * clusterSize);
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
      printf("-- DELETE  ");
      clusterSize = strtoul(token, NULL, 10);
      printf("size: %u\n", clusterSize);
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
      printf("-- SELECT  ");
      clusterSize = strtoul(token, NULL, 10);
      printf("size: %u\n", clusterSize);
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
      printf("-- SELECT ALL --\n");
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
  // mainTest();
  // popTest();
  // ikaroTest();
  // textTest();
  // variableSizes();

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

  textTest(argv[1], argv[2]);

  return 0;
}