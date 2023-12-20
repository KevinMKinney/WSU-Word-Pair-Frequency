#include "crc64.h"
#include "getWord.h"
#include "hashTable.h"

int main() {
	
	// init vars
	int hashSize = STARTINGHASHSIZE;
	struct table **hashTable = calloc(hashSize, sizeof(struct table*));

	if (hashTable == NULL) {
		free(hashTable);
		fprintf(stderr, "Not enough memory\n");
		exit(1);
	}

	int nameSize = 256;
	char input[nameSize];

	// PI format: wordpairs <count> fileName1 <fileName2> <fileName3> ...		
	printf("wordpairs ");

	// get input
	int count = 0;
	scanf("%d", &count);

	fgets(input, sizeof(input), stdin);
	
	for (int i = 0; i < sizeof(input); i++) {
		if (input[i] == '\n') {
			input[i] = ' ';
			break;
		}
	}

	// more init vars
	char *inputs = strtok(input, " ");
	FILE *file;
	int collisions = 0;
	char *str1 = NULL;
	char *betweenChar = " ";
	char *str2 = NULL;
	char *hashString = NULL;
	unsigned long long hashVal;

	// for each input in stdin 
	while (inputs != NULL) {
		// check if file is valid
		file = fopen(inputs, "r");
		if (file == NULL) {
			printf("%s is not a valid file\n", inputs);
		} else {
			// read file's words 
			while ((str2 = getNextWord(file)) != NULL) {
				if (str1 != NULL) {
					// combine words for hashed value and hash table
					hashString = calloc(1, strlen(str1)+strlen(betweenChar)+strlen(str2) + 3);
					strcpy(hashString, str1);
					strcat(hashString, betweenChar);
					strcat(hashString, str2);

					// get hashed value
					hashVal = crc64(hashString);

					free(str1);

					// add to hash table
					collisions = listAppend(&hashTable[(int)(hashVal % hashSize)], hashString, hashVal);
					
					// if there is too much entries in a hash table bucket...
					if (hashSize < (collisions * DENSITYRATIO)) {
						// ... resize the hash table.
						hashTable = hashResize(hashTable, &hashSize);
					}
				}
				str1 = str2;				
			}
			free(str1);
			fclose(file);
		}
			
		inputs = strtok(NULL, " ");
	}

	// for debugging 
	//printHash(hashTable, hashSize);

	displayFrequency(hashTable, hashSize, count);

	// memory clean-up
	for(int i = 0; i < hashSize; i++) {
		listClean(hashTable[i]);
	}
	free(hashTable);

	return 0;
}