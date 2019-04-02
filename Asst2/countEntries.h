
#ifndef COUNTENTRIES_H
#define COUNTENTRIES_H

typedef struct input {
	char * entry;
	char * code;
	int count;
	struct input * next;
	struct input * left;
	struct input * right;
} input;

input * newEntry(char * str);

void listInsert(input ** headRef, input * newEntry);
void treeInsert(input ** headRef, input * node1, input * node2);

void delete(input ** headRef, input * deletionEntry);

void split(input * start, input ** frontRef, input ** backRef);
input * merge(input * a , input * b);
void mergeSort(input ** headRef);

void printEntries(input * head);

void freeList(input * head);
void freeTree(input * root);

void countWords(char *file);

void createCodebook();

#endif //COUNTENTRIES_H
