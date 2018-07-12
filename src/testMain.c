#include "BinarySearchTreeAPI.h"

typedef struct integers {
	int num;
	char letter;
}Integers;

int compare(const void *a, const void *b) {
	int c = *((int *)b);
	int d = ((Integers *)a)->num;
	if(d > c) {
		return 1;
	}
	else if(d < c) {
		return -1;
	}
	return 0;
}

void deleteIntegers(void *data) {
	free(data);
	return;
}

void printIntegers(void *data) {
	Integers *toPrint = data;
	printf("%d and %c\n", toPrint->num, toPrint->letter);
	return;
}

int main(int argc, char ** argv) {
	Integers *input;
	Tree *testTree;
	TreeDataPtr *toFind;
	TreeDataPtr ptr = NULL;
	input = malloc(sizeof(Integers));
	printf("TESTING: createBinTree, createTreeNode\n");
	testTree = createBinTree(&compare, &deleteIntegers);
	printf("Passed\n\n");
	printf("TESTING: addToTree\n");
	
	printf("adding: ");
	input->num = 56;
	input->letter = 'A';
	printIntegers(input);
	addToTree(testTree, input);
	
	printf("adding: ");
	input++;
	input = malloc(sizeof(Integers));
	input->num = 32;
	input->letter = 'C';
	printIntegers(input);
	addToTree(testTree, input);
	
	input++;
	input = malloc(sizeof(Integers));
	printf("adding: ");
	input->num = 65;
	input->letter = 'T';
	printIntegers(input);
	addToTree(testTree, input);
	
	input++;
	input = malloc(sizeof(Integers));
	printf("adding: ");
	input->num = 98;
	input->letter = 'G';
	printIntegers(input);
	addToTree(testTree, input);
	
	input++;
	input = malloc(sizeof(Integers));
	printf("adding: ");
	input->num = 70;
	input->letter = 'P';
	printIntegers(input);
	addToTree(testTree, input);
	
	input++;
	input = malloc(sizeof(Integers));
	printf("adding: ");
	input->num = 21;
	input->letter = 'G';
	printIntegers(input);
	addToTree(testTree, input);
	
	input++;
	input = malloc(sizeof(Integers));
	printf("adding: ");
	input->num = 45;
	input->letter = 'X';
	printIntegers(input);
	addToTree(testTree, input);
	
	printf("Passed\n\n");
	printf("TESTING: printPreOrder, printInOrder, printPostOrder\n");
	printPreOrder(testTree, &printIntegers);
	printf("\n");
	printInOrder(testTree, &printIntegers);
	printf("\n");
	printPostOrder(testTree, &printIntegers);
	printf("Passed\n\n");
	printf("TESTING: findInTree\nEXPECTED: 45 and X\n");
	toFind = malloc(sizeof(int));
	*(int *)toFind = 45;
	ptr = findInTree(testTree, toFind);
	if(ptr == NULL) {
		printf("Failed\n");
	}
	else {
		printf("OUTPUT: ");
		printIntegers(ptr);
		printf("Passed\n\n");
	}
	printf("TESTING: isTreeEmpty\nEXPECTED: 0\nOUTPUT: ");
	int out = isTreeEmpty(testTree);
	printf("%d\n", out);
	if(out == 1) {
		printf("Failed\n\n");
	}
	else {
		printf("Passed\n\n");
	}
	printf("TESTING: isLeaf\nEXPECTED: 0\nOUTPUT: ");
	out = isLeaf(testTree->root);
	printf("%d \n", out);
	if(out == 0) {
		printf("Passed\n\n");
	}
	else {
		printf("Failed\n\n");
	}
	printf("TESTING: getRootData\nEXPECTED: 56 and A\nOUTPUT: ");
	ptr = getRootData(testTree);
	if(ptr == NULL) {
		printf("Failed\n\n");
	}
	else {
		printIntegers(ptr);
		printf("Passed\n\n");
	}
	printf("TESTING: hasTwoChildren\nEXPECTED: 1\nOUTPUT: ");
	out = hasTwoChildren(testTree->root);
	printf("%d \n", out);
	if(out == 1) {
		printf("Passed\n\n");
	}
	else {
		printf("Failed\n\n");
	}
	printf("TESTING: getHeight\nEXPECTED: 2\nOUTPUT: ");
	out = getHeight(testTree->root->right);
	printf("%d\n", out);
	if(out != 2) {
		printf("Failed\n\n");
	}
	else {
		printf("Passed\n\n");
	}
	printf("TESTING: removeFromTree\n");
	*(int *)toFind = 70;
	ptr = findInTree(testTree, toFind);
	removeFromTree(testTree, ptr);
	*(int *)toFind = 32;
	ptr = findInTree(testTree, toFind);
	removeFromTree(testTree, ptr);
	*(int *)toFind = 45;
	ptr = findInTree(testTree, toFind);
	removeFromTree(testTree, ptr);
	*(int *)toFind = 56;
	ptr = findInTree(testTree, toFind);
	removeFromTree(testTree, ptr);
	printf("Passed\n\n");
	printf("TESTING: destroyBinTree\nEXPECTED: Empty Tree\nOUTPUT: ");
	destroyBinTree(testTree);
	testTree = NULL;
	printPreOrder(testTree, &printIntegers);
	printf("Passed\n");
	free(toFind);
	return 0;
}
