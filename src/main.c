#include "BinarySearchTreeAPI.h"

/**
 * Function that removes the punctuation at the end of input string and
 * replaces it with a null terminator
 * @param pointer of type char that points to input string
 * @return pointer of type char that points to input string with newline replaced
 */
char *formatInput(char *file);

/*
 * struct definition for a rule
 */
typedef struct personalRules{
	char *keyWord;
	char *sentence;
	double systemRating;
	double userRating;
	double learningRate;
	int numUses;
	int index;
}pRule;

/**
 * Function to print out a pRule struct
 * @param void pointer to struct
 */
void printRule(void *data) {
	pRule *tmp = (pRule *)data;
	printf("<%s> Rating: %0.3f System: %0.3f Occurences: %d\n", tmp->keyWord, tmp->userRating, tmp->systemRating, tmp->numUses);
	return;
}

/**
 * Function delete a pRule struct
 * @param void pointer to struct
 */
void deleteRule(void *data) {
	free(((pRule *)data)->keyWord);
	free(((pRule *)data)->sentence);
	free(data);
	return;
}

/**
 * Function to compare two structs of type pRule
 * @param constant void pointer to first struct
 * @param constant void pointer to second struct
 * @param integer value depending on whether the structs match
 */
int compareRule(const void *a, const void *b) {
	char *keyOne = ((pRule *)a)->keyWord;
	char *keyTwo = ((char *)b);
	if(strcmp(keyOne, keyTwo) == 0) {
		return 0;
	}
	return 1;
}

/**
 * Function that removes the punctuation at the end of input string and
 * replaces it with a null terminator
 * @param pointer of type char that points to input string
 * @return pointer of type char that points to input string with newline replaced
 */
char *formatInput(char *file) {
	for(int i = 0; i < strlen(file); i++) {
		*(file + i) = tolower(*(file + i));
		if(*(file + i) == '\n' || *(file + i) == '?' || *(file + i) == '.' ||*(file + i) == '!') {
			*(file + i) = '\0';
			return file;
		}
	}
	return file;
}

/**
 * Function that removes the newline character at the end of input string and
 * replaces it with a null terminator
 * @param pointer of type char that points to input string
 * @return pointer of type char that points to input string with newline replaced
 */
char *removeNewLine	(char *file) {
	for(int i = 0; i < strlen(file); i++) {
		if(*(file + i) == '\n') {
			*(file + i) = '\0';
		}
	}
	return file;
}

/**
 * Main function
 * @param integer arguement count
 * @param char** argument vector
 */
int main(int argc, char **argv) {
	Tree *ruleTree;
	FILE *fp;
	ruleTree = createBinTree(&compareRule, &deleteRule);
	char *line;
	pRule *rule;
	char *usrIn = NULL;
	char *usrImportance;
	int usrInNum = -10;
	int true = 0;
	usrIn = malloc(sizeof(char) * 70);
	usrImportance = malloc(sizeof(char) * 10);
	printf("File is: %s\n", argv[argc - 1]);
	if(argc > 1)
	{
		fp = fopen( argv[argc - 1], "r" );
	}
	else
	{
		printf("Missing file argument. Exiting program\n");
		return 0;
	}
	while( !feof(fp) ) {
		line = NULL;
		rule = NULL;
		line = malloc(sizeof(char) * 70);
		rule = malloc(sizeof(pRule));
		strcpy(line, "\0");
		fgets(line, 70, fp);
		line = formatInput(line);
		if(strcmp(line, "") != 0) {
			line = formatInput(line);
			rule->keyWord = line;
			line++;
			line = malloc(sizeof(char) * 70);
			fgets(line, 70, fp);
			rule->sentence = line;
			rule->systemRating = 0.5;
			rule->userRating = 0.5;
			rule->learningRate = 0.05;
			rule->numUses = 0;
			addToTree(ruleTree, rule);
			rule++;
			line++;
		}
		else {
			free(line);
			free(rule);
		}
	}
	while(usrInNum != 9) {
		printf("MAIN MENU\n\n1) Add a new rule\n2) Remove a rule\n3) Display Rules\n4) Modify rule rating\n5) Discuss\n\n9) Quit\n\nPlease enter an option: ");
		fgets(usrIn, 5, stdin);
		usrInNum = atoi(usrIn);
		switch(usrInNum) {
			case 1:
				rule++;
				line++;
				rule = malloc(sizeof(pRule));
				line = malloc(sizeof(char) * 70);
				printf("Keyword of new rule: ");
				fgets(line, 70, stdin);
				line = formatInput(line);
				true = 0;
				while(true == 0) {
					void *ptr = NULL;
					ptr = findInTree(ruleTree, line);
					if(strcmp(line, "") == 0) {
						printf("Cannot have an empty keyword.\nKeyword of new rule: ");
						fgets(line, 70, stdin);
						line = formatInput(line);
					}
					else if(ptr != NULL) {
						printf("Rule with this keyword already exists: \n");
						printRule(ptr);
						printf("Keyword of new rule: ");
						fgets(line, 70, stdin);
						line = formatInput(line);
					}
					else {
						true = 1;
					}
				}
				rule->keyWord = line;
				rule->numUses = 0;
				rule->learningRate = 0.05;
				line++;
				line = malloc(sizeof(char) * 70);
				printf("Sentence of new rule: ");
				fgets(line, 70, stdin);
				line = formatInput(line);		
				rule->sentence = line;
				printf("User rating of rule: ");
				fgets(usrImportance, 10, stdin);	
				usrImportance = removeNewLine(usrImportance);
				rule->userRating = 	atof(usrImportance);
				rule->systemRating = rule->userRating;
				addToTree(ruleTree, rule);
				printf("Successfully added new rule\n");
				break;
			case 2:
				line++;
				line = malloc(sizeof(char) * 70);
				printf("Keyword of rule to delete: ");
				fgets(line, 70, stdin);
				line = formatInput(line);
				void *check = NULL;
				check = findInTree(ruleTree, line);
				if(check == NULL) {
					printf("Rule does not exist\nReturning to main menu.\n");
					break;
				}
				void *ptr = NULL;
				removeFromTree(ruleTree, line);
				ptr = findInTree(ruleTree, line);
				if(ptr == NULL) {
					printf("Successfuly removed rule\n");
				}
				else {
					printf("Failed to remove rule\n");
				}
				free(line);
				break;
			case 3:
				printPreOrder(ruleTree, &printRule);
				break;
			case 4:
				line++;
				void *toModify = NULL;
				line = malloc(sizeof(char) * 70);
				printf("Keyword of rule to modify: ");
				fgets(line, 70, stdin);
				line = formatInput(line);
				toModify = findInTree(ruleTree, line);
				if(toModify == NULL) {
					printf("Rule does not exist, returning to main menu\n");
					break;
				}
				printf("Current user rating is: %0.3f\n", ((pRule *)toModify)->userRating);
				printf("New user rating value: ");
				fgets(line, 70, stdin);
				((pRule *)toModify)->userRating = atof(line);		
				break;
			case 5:
				line++;
				int count;
				double maxRating = -110000;
				char *maxLine = NULL;
				double *ratings = NULL;
				char *token = NULL;
				void *toRead = NULL;
				line = malloc(sizeof(char) * 70);
				printf("What would you like to discuss?\nUser: ");
				fgets(line, 70, stdin);
				line = formatInput(line);
				token = strtok(line, " ");
				count = 0;
				while(token != NULL) {
					toRead = findInTree(ruleTree, token);
					ratings = malloc(sizeof(double));
					if(toRead != NULL) {
						*ratings = ((pRule *)toRead)->userRating + ((pRule *)toRead)->systemRating;
						if(maxRating < *ratings) {
							maxRating = *ratings;
							maxLine = token;
						}
					}
					ratings++;
					count++;
					token = strtok(NULL, " ");
				}
				if(maxLine != NULL) {
					toRead = findInTree(ruleTree, maxLine);
				}
				if(toRead != NULL) {
					true = 0;
					line++;
					line = malloc(sizeof(char)*2);
					printf("Personal Assistant: %s\n", ((pRule *)toRead)->sentence);
					((pRule *)toRead)->numUses++;
					while(true == 0) {
						printf("Was this feedback helpful ('y' or 'n'): ");
						fgets(line, 2, stdin);
						line = formatInput(line);
						if(strcmp(line, "y") == 0) {
							((pRule *)toRead)->systemRating = ((pRule *)toRead)->systemRating + ( ((pRule *)toRead)->systemRating * ((pRule *)toRead)->learningRate/((pRule *)toRead)->numUses);
							true = 1;
							fgets(line, 2, stdin);
						}
						else if(strcmp(line, "n") == 0) {
							((pRule *)toRead)->systemRating = ((pRule *)toRead)->systemRating - ( ((pRule *)toRead)->systemRating * ((pRule *)toRead)->learningRate/((pRule *)toRead)->numUses);
							true = 1;
							fgets(line, 2, stdin);
						}
						else {
							printf("Invalid input, please retry.\n");
						}
					}
				}
				else {
					printf("I'm sorry I am still learning\n");
				}
				break;
			case 9:
				printf("Goodbye\n");
				break;
			default:
				printf("Unknown input. Retry\n");
				break;
		}
	}
	destroyBinTree(ruleTree);
	free(usrImportance);
	free(usrIn);
	fclose(fp);
	return 0;
}
