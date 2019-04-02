

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include "countEntries.h"
#include "huffmanTree.h"

//TODO count number of methods and make sure they're all in the header file
//TODO make sure all fds and dds are closed
//TODO make sure all mallocs are freed
//TODO add some modularity

input * inputs = NULL;

input * newEntry(char * str) {

	input * newEntry = (input*)malloc(sizeof(input));
	if (newEntry == NULL) {
		fprintf(stderr, "ERROR: Memory allocation failed.\n");
		exit(1);
	}
	newEntry->entry = (char *)malloc(strlen(str) * sizeof(char));
	strcpy(newEntry->entry, str);
	newEntry->count = 1;
	newEntry->next = NULL;
	newEntry->left = NULL;
	newEntry->right = NULL;
	newEntry->code = NULL;

	return newEntry;
}

void listInsert(input ** headRef, input * newEntry) {
	//char * inputString = (char*)malloc(strlen(newEntry->entry) * sizeof(char));
	
	input * curr = *headRef;
	//strcpy(inputString, newEntry->entry);
	
	if (*headRef == NULL) {
		//printf("list created at head\n");
		newEntry->next = *headRef;
		*headRef = newEntry;
		
		return;
	}
	else {
		//char * currString = (char *)malloc(strlen((*headRef)->entry) * sizeof(char));
		//strcpy(currString, (*headRef)->entry);
		
		//TODO
		
		//printf("comparing %s to %s\n", inputString, currString);
		
		// insertionNode is a leaf
		if (strcmp(newEntry->entry, "") != 0) {
		
			if (strcmp(newEntry->entry, (*headRef)->entry) == 0) {
				//printf("%s found in list\n", currString);
				(*headRef)->count = (*headRef)->count + 1;
				return;
			}
		
			curr = *headRef;
			
			while(curr->next != NULL) {
				// check if entry already in list
					// check first at head
				
					// check the rest of the list
				//free(currString);
				//currString = (char *) malloc(strlen(curr->next->entry) * sizeof(char));
				//strcpy(currString, curr->next->entry);
				//printf("comparing %s to %s\n", inputString, currString);
				if (strcmp(curr->next->entry, newEntry->entry) == 0) {
					//printf("%s found in list\n", curr->next->entry);
					curr->next->count = curr->next->count + 1;
					//printf("value of count: %d\n", curr->count);
					return;
				}
				curr = curr->next;
			}
			// otherwise add to list at the end
			//printf("%s added to the end of list\n", newEntry->entry);
			newEntry->next = curr->next;
			curr->next = newEntry;
		}
		// insertionNode is a tree
		else if (strcmp(newEntry->entry, "") == 0) {
			
			// ALWAYS ADD Tree to the end of the list
			curr = *headRef;
			
			while(curr->next != NULL) {
				
				curr = curr->next;
			}
			
			newEntry->next = curr->next;
			curr->next = newEntry;
		}
	}

}

void delete(input ** headRef, input * deletionEntry){

	printf("deleting: %s\n", deletionEntry->entry);
	
	input * temp = *headRef, *prev;
	
	// deal with removal of trees and leaves differently
	// check if leaf
	if (strcmp(temp->entry, "") != 0) {
	
		if(temp != NULL && strcmp(temp->entry, deletionEntry->entry) == 0 ){
			*headRef = temp->next;
			free(temp);
			return;
		}
		
		while (temp != NULL && strcmp(temp->entry, deletionEntry->entry) != 0){
			prev = temp;
			temp = temp->next;
		}

		if(temp == NULL)
			return;
		
		prev->next = temp->next;
	}
	// handle tree case
	else if (strcmp(temp->entry, "") == 0) {
	
		if(temp != NULL && strcmp(temp->entry, deletionEntry->entry) == 0 && temp->count == deletionEntry->count){
			*headRef = temp->next;
			free(temp);
			return;
		}
		
		while (temp != NULL && strcmp(temp->entry, deletionEntry->entry) != 0 && temp->count != deletionEntry->count){
			prev = temp;
			temp = temp->next;
		}

		if(temp == NULL)
			return;
		
		prev->next = temp->next;
	}
	
	//free(temp);
		
}

void split(input * start, input ** frontRef, input ** backRef) {
	input * front;
	input * back;
	
	back = start;
	front = start->next;
	
	while (front != NULL) {
		front = front->next;
		if (front != NULL) {
			back = back->next;
			front = front->next;
		}
	}
	
	*frontRef = start;
	*backRef = back->next;
	back->next = NULL;
}
input * merge(input * a , input * b) {
	input * result = NULL;
	
	if (a == NULL) {
		return b;
	}
	else if (b == NULL){
		return a;
	}
	
	if (a->count <= b->count) {
		result = a;
		result->next = merge(a->next, b);
	}
	else {
		result = b;
		result->next = merge(a, b->next);
	}
	
	return result;
}
void mergeSort(input ** headRef) {
	input * head = *headRef;
	input * a;
	input * b;
	
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}
	
	split(head, &a, &b);
	
	mergeSort(&a);
	mergeSort(&b);
	
	*headRef = merge(a, b);
}

void printEntries(input * head) {
	input * temp = head;
	while (temp != NULL) {
		printf("%s\t%d\n", temp->entry, temp->count);
		temp = temp->next;
	}
}
void printCodelist(input * head) {
	input * temp = head;
	while (temp != NULL) {
		printf("%s\t%s\n", temp->entry, temp->code);
		temp = temp->next;
	}
}

void freeList(input * head) {
   input * curr;

   while (head != NULL)
    {
       curr = head;
       head = head->next;
       free(curr);
    }
}

void freeTree(input * root) {
	
	if (root == NULL) {
		return;
	}
	
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

void treeInsert(input ** headRef, input * node1, input * node2) {
	input * head = *headRef;
	
	input * newTree = newEntry("");
	newTree->count = node1->count + node2->count;
	
	input * leftLeaf = newEntry(node1->entry);
	leftLeaf->count = node1->count;
	leftLeaf->left = node1->left;
	leftLeaf->right = node1->right;
	
	input * rightLeaf = newEntry(node2->entry);
	rightLeaf->count = node2->count;
	rightLeaf->left = node2->left;
	rightLeaf->right = node2->right;
	
	newTree->left = leftLeaf;
	newTree->right = rightLeaf;
	
	//printf("\nloop\n");
	listInsert(&head, newTree);
	//delete(&head, node1);
	//delete(&head, node2);
	/*
	input * temp = newEntry(node1->entry);
	delete(&head, temp);
	printEntries(head); printf("\n");
	temp = newEntry(node2->entry);
	delete(&head, temp);
	printEntries(head); printf("\n");
	*/
}

input * codeTreeInsert(input * root, char * entry, char * code) {
	
	/*
	if (root == NULL) {
		root = newEntry("");
		root->left = newEntry("");
		root->right = newEntry("");
	}
	
	printf("%s\t%s\n", code, entry);
	int i = 0;
	for (i = 0; i < strlen(code); i++) {
		if (code[i] == '0') {
			if (root->left == NULL) {
				input * temp = newEntry("");
				root->left = temp;
			}
			root = root->left;
		}
		else if (code[i] == '1') {
			if (root->right == NULL) {
				input * temp = newEntry("");
				root->right = temp;
			}
			root = root->right;
		}
		else
			printf("problem in code traversal\n");
	}
	
	input * insert = newEntry(entry);
	root = insert;
	printf("%s added to tree at %s\n", entry, code);
	*/
	
	if (root == NULL || !(code[0] == '0' || code[0] == '1'))
		return newEntry(entry);
	
	if (code[0] == '0') {
		if (root->left == NULL)
			root->left = newEntry("");
		root->left = codeTreeInsert(root->left, entry, code+1);
	}
	else if (code[0] == '1') {
		if (root->right == NULL) 
			root->right = newEntry("");
		root->right = codeTreeInsert(root->right, entry, code+1);
	}
	
	return root;
}

void writeCodebook(input ** headRef) {
	
	input * head = *headRef;
	input * temp1 = head;
	input * temp2 = head->next;
	
	while (head->next != NULL) {
		treeInsert(&head, temp1, temp2);
		delete(&head, head);
		delete(&head, head);
		mergeSort(&head);
		printEntries(head);
	}
	
}

printPreorder(input * inputs) {
	
	if (inputs == NULL) {
		return;
	}
	
	printf("%s\t%d\n", inputs->entry, inputs->count);
	
	printPreorder(inputs->left);
	printPreorder(inputs->right);
}

void printCode(int arr[], int length, int fd) {
	int i;
	char buff[4];
	for (i = 0; i < length; i++) {
		printf("%d", arr[i]);
		sprintf(buff, "%d", arr[i]);
		write(fd, buff, strlen(buff));
	}
	//printf("\n");
}
void printCodes(input * root, int arr[], int top, int fd) {
	
	if (root->left) {
		arr[top] = 0;
		printCodes(root->left, arr, top+1, fd);
	}
	if (root->right) {
		arr[top] = 1;
		printCodes(root->right, arr, top+1, fd);
	}
	if (strcmp(root->entry, "") != 0) {
		printCode(arr, top, fd);
		printf("\t%s\n", root->entry);
		write(fd, "\t", 1);
		write(fd, root->entry, strlen(root->entry));
		write(fd, "\n", 1);
	}
}

void writeCompressionCode(int fd, input * codes, char * word) {
	input * temp = codes;
	while (temp != NULL) {
		if(strcmp(temp->entry, word) == 0) {
			write(fd, temp->code, strlen(temp->code));
		}
		temp = temp->next;
	}
}

int fileSize(char * filename) {
	int ret = 0;
	struct stat info;
	
	if ((filename != NULL) && (stat(filename, &info) == 0))
		ret = (int)info.st_size;
	return ret;
}

void countWords(char *file) {

	int fd = open(file, O_RDONLY);

	//input * inputs = *wordListRef;

	if (fd != -1) {
		printf("opened file!\n\n");

		int status = 0;
		char buffer;
		char word[fileSize(file)];
		int i = 0;
		
		do {
			status = read(fd, &buffer, 1);
			//printf("%d\n", buffer);
			//printf("%s\n", word);	
			
			// control code is found
			if (buffer <= 32 || buffer == 127 || buffer == ' ' || buffer == '\t' || buffer == '\n'){
				
				word[i] = '\0';
				
				if (word[0] != 0) {
					input * entry1 = newEntry(word);
					listInsert(&inputs, entry1);
				}
				//printEntries(head);
				
				//printf("%d\n", buffer);
				char arrBuff[3];
				if (buffer == '\t') {
					arrBuff[0] = '\\';
					arrBuff[1] = 't';
					arrBuff[2] = '\0';
				}
				else if (buffer == '\n') {
					arrBuff[0] = '\\';
					arrBuff[1] = 'n';
					arrBuff[2] = '\0';
				}
				else {
					arrBuff[0] = buffer;
					arrBuff[1] = '\0';
				}
				input * entry2 = newEntry(arrBuff);
				listInsert(&inputs, entry2);
				
				//printEntries(head);
						
				for (i = 0; i < fileSize(file); i++) {
					word[i] = 0;
				}		
				i = 0;
				arrBuff[0] = 0;
				arrBuff[1] = 0;
			}
			else {
			//printf("reaches here2");
				word[i] = buffer;
				i++;
			}
			
		} while (status > 0);
	}
	else {
		fprintf(stderr, "Error: File given does not exist.\n");
		exit(1);
	}

	close(fd);
	
	//printEntries(inputs);
	mergeSort(&inputs);
	printEntries(inputs);
}

void createCodebook() {

	//input * inputs = wordListRef;
	
	// testing example on assignment description
	//input * temp = newEntry("\\n");
	//delete(&inputs, temp);
	printf("\nSORTED ENTRIES\n");
	printEntries(inputs);
	
	//writeCodebook(&inputs);
	input * curr = inputs;
	
	int i = 0;
	while (inputs->next != NULL) {
	
		input * temp1 = inputs;
		input * temp2 = inputs->next;
		
		treeInsert(&inputs, temp1, temp2);
		delete(&inputs, temp1);
		delete(&inputs, temp2);
		
		printf("\nLIST\n");
		mergeSort(&inputs);
		printEntries(inputs);
		printf("\nTREE:\n");
		printPreorder(inputs);
		
	}
	
	printf("\nFINAL LIST:\n");
	printEntries(inputs);
	
	printf("\nFINAL TREE:\n");
	printPreorder(inputs);
	
	int arr[1024];
	int top = 0;
	printf("\n\\\n");
	
	int output = open("HuffmanCodebook", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	write(output, "\\\n", 2);
	printCodes(inputs, arr, top, output);
	close(output);
	printf("\n");
	
	freeTree(inputs);
}

void compress(char * file, char * book) {
	
	int fd = open(book, O_RDONLY);
	int fd2 = open(file, O_RDONLY);

	input * codebook = NULL;

	// open codebook and create list version to be searched
	if (fd != -1 && fd2 != -1) {
		printf("opened files!\n\n");

		int status = 0;
		char buffer;
		char word[fileSize(file)];
		char code[fileSize(file)];
		int i = 0;
		
		// read and store escape char stored at top of codebook file
		char escapeChar;
		status = read(fd, &escapeChar, 1);
		// read and ignore the following newline
		status = read(fd, &buffer, 1);
		do {
			status = read(fd, &buffer, 1);
			//printf("%c\n", buffer);
			//printf("%s\n", code);
			
			if (buffer == '\t')
			{
				code[i] = '\0';
				i = 0;
				
				while (buffer != '\n') {
					status = read(fd, &buffer, 1);
					
					if (buffer != '\n')
						word[i] = buffer;
					i++;
				}
				word[i] = '\0';
				//printf("%s\n", word);
				
				input * entry = newEntry(word);
				entry->code = (char*)malloc(strlen(code) * sizeof(char));
				strcpy(entry->code, code);
				listInsert(&codebook, entry);
				
				//printCodelist(codebook);
				
				for (i = 0; i < fileSize(file); i++) {
					word[i] = 0;
				}
				for (i = 0; i < fileSize(file); i++) {
					code[i] = 0;
				}
				i = 0;
			}	
			else {
				code[i] = buffer;
				i++;
			}
			 
		} while (status > 0);
		
		printCodelist(codebook);
		
		char newFile[1024];
		strcpy(newFile, file);
		strcat(newFile, ".hcz");
		int output = open(newFile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		
		do {
			status = read(fd2, &buffer, 1);
			//printf("%d\n", buffer);
			//printf("%s\n", word);	
			
			// control code is found
			if (buffer <= 32 || buffer == 127 || buffer == ' ' || buffer == '\t' || buffer == '\n'){
				
				word[i] = '\0';
				
				if (word[0] != 0) {
					writeCompressionCode(output, codebook, word);
				}
				//printEntries(head);
				
				//printf("%d\n", buffer);
				char arrBuff[3];
				if (buffer == '\t') {
					arrBuff[0] = '\\';
					arrBuff[1] = 't';
					arrBuff[2] = '\0';
				}
				else if (buffer == '\n') {
					arrBuff[0] = '\\';
					arrBuff[1] = 'n';
					arrBuff[2] = '\0';
				}
				else {
					arrBuff[0] = buffer;
					arrBuff[1] = '\0';
				}
				writeCompressionCode(output, codebook, arrBuff);
				
				//printEntries(head);
						
				for (i = 0; i < fileSize(file); i++) {
					word[i] = 0;
				}		
				i = 0;
				arrBuff[0] = 0;
				arrBuff[1] = 0;
			}
			else {
			//printf("reaches here2");
				word[i] = buffer;
				i++;
			}
			
		} while (status > 0);
		
		close(output);
	}
	else {
		if (fd2 == -1)
			fprintf(stderr, "Error: File given does not exist.\n");
		if (fd == -1)
			fprintf(stderr, "Error: Codebook given does not exist.\n");
		exit(1);
	}

	close(fd);
	close(fd2);
}

void decompress(char * file, char * book) {
	
	int fd = open(book, O_RDONLY);
	int fd2 = open(file, O_RDONLY);
	
	input * codebook = NULL;

	// open codebook and create list version to be searched
	if (fd != -1 && fd2 != -1) {
		printf("opened files!\n\n");

		int status = 0;
		char buffer;
		//printf("FILE SIZE RIGHT HERE GET YOUR FILE SIZE\n");
		//printf("%d\n", fileSize(book));
		char word[fileSize(book)];
		char code[fileSize(book)];
		int i = 0;
		
		// read and store escape char stored at top of codebook file
		char escapeChar;
		status = read(fd, &escapeChar, 1);
		// read and ignore the following newline
		status = read(fd, &buffer, 1);
		for (i = 0; i < fileSize(book); i++) {
			word[i] = 0;
		}
		for (i = 0; i < fileSize(book); i++) {
			code[i] = 0;
		}
		i = 0;
		do {
			status = read(fd, &buffer, 1);
			printf("%c\n", buffer);
			printf("%s\n", code);
			
			if (buffer == '\t')
			{
				printf("tab encountered\n");
				code[i] = '\0';
				i = 0;
				
				while (buffer != '\n') {
					status = read(fd, &buffer, 1);
					
					if (buffer != '\n')
						word[i] = buffer;
					printf("current string being built: %s\n", word);
					i++;
				}
				word[i] = '\0';
				//printf("%s\n", word);
				
				printf("inserting %s with code %s\n", word, code);
				input * entry = newEntry(word);
				entry->code = (char*)malloc(strlen(code) * sizeof(char));
				strcpy(entry->code, code);
				listInsert(&codebook, entry);
				
				//printCodelist(codebook);
				
				for (i = 0; i < fileSize(book); i++) {
					word[i] = 0;
				}
				for (i = 0; i < fileSize(book); i++) {
					code[i] = 0;
				}
				i = 0;
			}	
			else {
				code[i] = buffer;
				printf("current code: %s\n", code);
				i++;
			}
			 
		} while (status > 0);
		
		printCodelist(codebook);
		
		input * codeTree = newEntry("");
		
		while (codebook != NULL) {
			codeTreeInsert(codeTree, codebook->entry, codebook->code);
			printPreorder(codeTree);
			delete(&codebook, codebook);
		}
		
		printPreorder(codeTree);
		
		printf("reached string setting\n");
		char * decompressPath = (char*)malloc((strlen(file)-4) * sizeof(char));
		for (i = 0; i < strlen(file)-4; i++) {
			decompressPath[i] = file[i];
		}
		printf("%s\n", decompressPath);
		
		int output = open(decompressPath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		
		input * traverse = codeTree;
		
		do {
			status = read(fd2, &buffer, 1);
			
			if (buffer == '0') {
				if (traverse->left == NULL) {
					if (strcmp(traverse->entry, "\\n") == 0) {
						printf("%c", '\n');
						write(output, "\n", 1);
					}
					else if (strcmp(traverse->entry, "\\t") == 0) {
						printf("%c", '\t');
						write(output, "\t", 1);
					}
					else {
						printf("%s", traverse->entry);
						write(output, traverse->entry, strlen(traverse->entry));
					}
					traverse = codeTree;
				}
				traverse = traverse->left;
			}
			else if (buffer == '1') {
				if (traverse->right == NULL) {
					if (strcmp(traverse->entry, "\\n") == 0) {
						printf("%c", '\n');
						write(output, "\n", 1);
					}
					else if (strcmp(traverse->entry, "\\t") == 0) {
						printf("%c", '\t');
						write(output, "\t", 1);
					}
					else {
						printf("%s", traverse->entry);
						write(output, traverse->entry, strlen(traverse->entry));
					}
					traverse = codeTree;
				}
				traverse = traverse->right;
			}
			//else fprintf(stderr, "Error: In compression file code.\n");
		} while (status > 0);
		
		
		close(output);
	}
	else {
		if (fd2 == -1)
			fprintf(stderr, "Error: File given does not exist.\n");
		if (fd == -1)
			fprintf(stderr, "Error: Codebook given does not exist.\n");
		exit(1);
	}

	close(fd);
	close(fd2);
}
