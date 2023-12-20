	Kevin Kinney
	CS 360
	Assignment 1 
	9/7/22
	McCamish

Overview:
	This is a C program designed to read words from one or more files, and prints out a list of the most frequently occurring sequential pairs of words and the number of times they occurred, in decreasing order of occurrence. The user may also specify a minimum number of occurences for the sequential word pairs, which limits the list and is useful for a larger data set.

	This is handled by using a dynamic hash table with seperate chaining that resizes based on the ratio of buckets to items per bucket. If you so desire, you can change some parameters of the hash table through changing the macros in the "hashTable.h" file.

How to Compile & Run:

 	While in the same directory, you can run "make" to compile all files and create an executable titled "wordpairs". Running "make run" will do the same, but also run the executable (more on that below). You can also run "make clean" to remove the executable. There are also "make valgrind" and "make prof", but these are for debugging purposes.

 	When running the executable, the user is prompted with the following:

 	wordpairs <count> fileName1 <fileName2> <fileName3> ...

 Input specifics:

 	count - the minimum number of occurences for the sequential word pairs to be printed.
 	filename# - the path and file name to the file which you want the program to run on.

 	The "<>" mean that the input is optional. 