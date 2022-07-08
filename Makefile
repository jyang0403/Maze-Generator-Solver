CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g

hw3: hw3.o maze.o print_functions.o
	$(CC) -o hw3 hw3.o maze.o print_functions.o
hw3.o: hw3.c maze.h print_functions.h
	$(CC) $(CFLAGS) -c hw3.c
maze.o: maze.c maze.h
	$(CC) $(CFLAGS) -c maze.c
print_functions.o: print_functions.c print_functions.h
	$(CC) $(CFLAGS) -c print_functions.c
clean:
	rm -f *.o hw3
