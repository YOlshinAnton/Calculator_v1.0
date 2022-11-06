CFLAGS=-Wall -Werror -Wextra -g

LIBS=-lm

graph:
	gcc -o ../build/graph $(CFLAGS) graph.c list.c stack.c token.c input.c process.c $(LIBS)

graph_test: graph
	../build/graph

input_test: input_test.c stack.c list.c token.c input.c process.c
	gcc -o ../build/input_test $(CFLAGS) input_test.c stack.c list.c token.c input.c process.c $(LIBS)
	../build/input_test

leaks: graph
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ../build/graph

leaks_input: input_test
	valgrind --track-origins=yes ../build/input_test

clean:
	rm -rf ../build/*