# METHOD 1
# final:
# 	gcc main.c ./lib/cadastro.c -o main

# METHOD 2
$(CC) = gcc
.PHONY: clean
# no need to write 'make final'
final:
	$(CC) main.c ./lib/clusterTree.c ./lib/essentials.c ./lib/list.c ./lib/sumTree.c -o main.o
	@./main.o
# @ makes the comand run silently

test:
	@$(CC) test.c ./lib/clusterTree.c ./lib/essentials.c ./lib/list.c ./lib/sumTree.c -o test.o
	@./test.o

clean:
	clear
	@rm -f *.o