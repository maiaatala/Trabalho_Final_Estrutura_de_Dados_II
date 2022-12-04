# METHOD 1
# final:
# 	gcc main.c ./lib/cadastro.c -o main

# METHOD 2
$(CC) = gcc
.PHONY: clean
# no need to write 'make final'
final:
	@$(CC) main.c ./lib/clusterTree.c ./lib/essentials.c ./lib/list.c ./lib/sumTree.c -o main.o
	@./main.o
# @ makes the comand run silently

test:
	@$(CC) test.c ./lib/clusterTree.c ./lib/essentials.c ./lib/list.c ./lib/sumTree.c -o test.o
	@./test.o ./txtFiles/test.txt ./txtFiles/output_test.txt

small:
	@$(CC) test.c ./lib/clusterTree.c ./lib/essentials.c ./lib/list.c ./lib/sumTree.c -o test.o
	@./test.o ./txtFiles/arq_com_as_operacoes.txt ./txtFiles/output_file.txt

1k:
	@$(CC) test.c ./lib/clusterTree.c ./lib/essentials.c ./lib/list.c ./lib/sumTree.c -o test.o
	@./test.o ./txtFiles/entrada_1k.txt ./txtFiles/output_file_1k.txt

2k:
	@$(CC) test.c ./lib/clusterTree.c ./lib/essentials.c ./lib/list.c ./lib/sumTree.c -o test.o
	@./test.o ./txtFiles/entrada_2k.txt ./txtFiles/output_file_2k.txt

clean:
	clear
	@rm -f *.o