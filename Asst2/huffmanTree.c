
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "huffmanTree.h"
#include "countEntries.h"

/*
void treeInsert(input ** headRef, input * node1, input * node2) {
	input * head = *headRef;
	
	input * newTree = newEntry("NODE");
	newTree->count = node1->count + node2->count;
	newTree->left = node1;
	newTree->right = node2;
	
	printf("\nloop\n");
	insertEntry(&head, newTree);
	//delete(&head, node1);
	//delete(&head, node2);
	input * temp = newEntry(node1->entry);
	delete(&head, temp);
	printEntries(head); printf("\n");
	temp = newEntry(node2->entry);
	delete(&head, temp);
	printEntries(head); printf("\n");
}

void writeCodebook(input * list) {
	
	input * head = list;
	input * temp1 = head;
	input * temp2 = head->next;
	
	while (head->next != NULL) {
		treeInsert(head, temp1, temp2);
		mergeSort(head);
		//printEntries(head);
	}
	
}
*/
