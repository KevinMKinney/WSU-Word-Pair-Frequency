#include "hashTable.h"

/* This function prints (to stdout) the word pairs in order with a frequency 
above count.

Input:
 - hashTable: a double pointer to the hash table.
 - hashSize: the number of buckets in the hash table.
 - count: the minimum frequency of the printed word pairs.
*/
void displayFrequency(struct table** hashTable, int hashSize, int count) {

	// make an array of the hash table for qsort()
	int arraySize = getHashSize(hashTable, hashSize);
	struct table array[arraySize];

	// init vars
	int lastIndex = 0;
	struct table* point;

	// for each bucket...
	for (int i = 0; i < hashSize; i++) {
		point = hashTable[i];
		// add entries into array
		while (point != NULL) {
			array[lastIndex] = *point;
			lastIndex++;
			point = point->next;
		}
	}

	// sort the array
	qsort(array, arraySize, sizeof(struct table), compareFunction);
	//qsort(array, arraySize, sizeof(array)/arraySize, compareFunction);

	// print contents of array...
	for (int i = 0; i < arraySize; i++) {
		// ...until reached the end of the array or there are no more valid
		// words to print
		if (array[i].amount < count) {
			return;
		}
		printf("%10d %s\n", array[i].amount, array[i].item);
	}

	return;
}

/* This function is a comparator function to qsort (used in the "displayFrequency"
function).
*/
int compareFunction(const void* a, const void* b) {
	int aa = ((struct table*)a)->amount;
	int ba = ((struct table*)b)->amount;
	return (ba - aa);
}