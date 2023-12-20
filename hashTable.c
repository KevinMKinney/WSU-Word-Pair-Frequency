#include "hashTable.h"

/* This function takes a single linked list and appends a new entry to the list 
using the "newListItem" function if an entry with the same values are not present 
in the list already. If an entry with the same values exist in the list, increment
the "amount" perameter. It returns the number of entries it passed.

Input:
 - list: a double pointer to the first entry in the list.
 - input: the string value of the soon to be new entry.
 - HV: the hash value of the soon to be new entry.

Output:
 - collision: the number of non-NULL entries passed before appended or 
*/
int listAppend(struct table** list, char* input, unsigned long long HV) {

	// init vars
	struct table* point = *list;
	int collisions = 0;

	// add new entry if list is empty
	if (*list == NULL) {
		*list = newListItem(input, HV);
		return collisions;
	}

	// increment count if the first entry has the same string
	if (strcmp(point->item, input) == 0) {
		point->amount++;
		free(input);
		return collisions;
	}

	// iterate through the list, checking if any entries have the same string
	while (point->next != NULL) {
		if (strcmp(point->item, input) == 0) {
			point->amount++;
			free(input);
			return collisions;
		} else {
			collisions++;
			point = point->next;
		}
	}

	// increment count if the last entry has the same string
	if (strcmp(point->item, input) == 0) {
		point->amount++;
		free(input);
		return collisions;
	}

	// append the new entry
	point->next = newListItem(input, HV);
	return collisions;
}

/* This function is a helper function to the "listAppend" function. It allocates
memory for the new entry as well as initialize the values of the entry.

Input:
 - input: the string value of the new entry.
 - HV: the hash value of the new entry.

Output:
 - entry: a pointer the new entry
*/
struct table* newListItem(char* input, unsigned long long HV) {
	struct table* entry = calloc(1, sizeof(struct table)); 

	// safety check for if the memory was allocated
	if (entry == NULL) {
		free(entry);
		fprintf(stderr, "Not enough space\n");
		exit(1);
	}

	// init params
	entry->item = input;
	entry->hashVal = HV;
	entry->amount = 1;
	entry->next = NULL;

	return entry;
}

/* This function creates a new hash table, moves the entries of the old hash
table to the new one (by using the moveList function), and frees the old
hash table.

Input:
 - hashTable: a double pointer to the old hash table.
 - size: a int pointer to the number of buckets in the old hash table.

Output:
 - newHashTable: a double pointer to the new hash table.
*/
struct table** hashResize(struct table** hashTable, int* size) {
	// init var
	int newSize = *size * GROWTHMAGNITUDE;
	struct table* list;
	struct table **newHashTable = calloc(newSize, sizeof(struct table*));

	// safety check for if the memory was allocated
	if (newHashTable == NULL) {
		free(newHashTable);
		fprintf(stderr, "Not enough space\n");
		exit(1);
	}

	// move entries to the new hash table
	for (int i = 0; i < *size; i++) {
		list = hashTable[i];
		moveList(newHashTable, &list, newSize);
	}

	// update hash table size
	*size = newSize;

	// free old hash table
	free(hashTable);

	return newHashTable;
}

/* This function is a helper function to the "hashResize" function. It uses
recursion to move the list entries from the end. Operates in a similar
fasion to the "listAppend" function.

Input:
 - newHashTable: a double pointer to the hash table where the entries are being
 moved to.
 - list: a double pointer to the list that is being moved.
 - size: the number of buckets the new hash table has.
*/
void moveList(struct table** newHashTable, struct table** list, int size) {
	// base case (for recursion)
	if (*list == NULL) {
		return;
	}

	// recusive call
	moveList(newHashTable, &((*list)->next), size);

	(*list)->next = NULL;
	struct table** point = &newHashTable[(int)((*list)->hashVal % size)];

	// add new entry if list is empty
	if (*point == NULL) {
		*point = *list;
		return;
	}

	// iterate through the list
	while ((*point)->next != NULL) {
		point = &((*point)->next);
	}

	// finish the move
	(*point)->next = *list;
	return;
}

/* This function is for debugging purposes. It shows the hash table and its 
contents by printing it to stdout.

Input:
 - hashTable: a double pointer to the hash table.
 - hashSize: the number of buckets in the hash table.
*/
void printHash(struct table** hashTable, int hashSize) {
	struct table* list;
	printf("\n");
	for (int i = 0; i < hashSize; i++) {
		list = hashTable[i];
		printf("Bucket %d: ", i);
		while (list != NULL) {
			printf("(%d) %s > ", list->amount, list->item);
			list = list->next;
		}
		printf("\n");
	}
}

/* This function iterrates through the hash table to get the exact number
of entries in the table.

Input:
 - hashTable: a double pointer to the hash table.
 - hashSize: the number of buckets in the hash table.

Output:
 - itemAmount: the number of entries in the hash table
*/
int getHashSize(struct table** hashTable, int hashSize) {
	// init var
	struct table* list;
	int itemAmount = 0;

	// for each bucket...
	for (int i = 0; i < hashSize; i++) {
		list = hashTable[i];
		// ...count the number of entries
		while (list != NULL) {
			itemAmount++;
			list = list->next;
		}
	}
	return itemAmount;
}

/* This function frees the allocated memory in a list recursively. Used on 
each bucket in the hash table.

Input:
 - list: a pointer to the first entry in the list.
*/
void listClean(struct table* list) {
	if (list != NULL) {
		// recursive call
		listClean(list->next);
		// free memory
		free(list->item);
		free(list);
	}
	return;
}
