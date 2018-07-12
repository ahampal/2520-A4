#Flags
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
LIB = lib/

#rules
main: 
	$(CC) $(CFLAGS) -L$(LIB) src/main.c -lBinarySearchTreeAPI -Iinclude -o bin/main
	
test:
	$(CC) $(CFLAGS) -L$(LIB) src/testMain.c -lBinarySearchTreeAPI -Iinclude -o bin/test
	
API:
	$(CC) $(CFLAGS) -c src/BinarySearchTreeAPI.c -Iinclude -o assets/BinarySearchTreeAPI.o
	ar rc lib/libBinarySearchTreeAPI.a assets/BinarySearchTreeAPI.o
	ranlib lib/libBinarySearchTreeAPI.a
