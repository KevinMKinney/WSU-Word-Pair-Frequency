#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// macros (subject to change)

// amount of buckets the hash table starts with (has to be an integer and at least 1)
#define STARTINGHASHSIZE 3

// the megnitude of hash resizing (has to be an integer and at least 1)
#define GROWTHMAGNITUDE 3

// the maximum ratio of entries in a bucket to the number of buckets (has to be a positive float)
#define DENSITYRATIO 1.3

// struct for linked list
struct table {
	char* item; 
	unsigned long long hashVal;
	int amount;
	struct table* next;
};

// functions in "hashTable.c"
int listAppend(struct table** list, char* input, unsigned long long HV);
struct table* newListItem(char* input, unsigned long long HV);
struct table** hashResize(struct table** hashTable, int* size);
void moveList(struct table** newHashTable, struct table** list, int size);
void printHash(struct table** hashTable, int hashSize);
int getHashSize(struct table** hashTable, int hashSize);
void listClean(struct table* list);

// functions in "output.c"
void displayFrequency(struct table** hashTable, int hashSize, int count);
int compareFunction(const void* a, const void* b);

#endif