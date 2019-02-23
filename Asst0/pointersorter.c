#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct node{
	char * data;
   	struct node * link;

};

struct node * newNode(char * str){
	struct node * newNode = (struct node*) malloc(sizeof(struct node));
	if (newNode == NULL) {
		printf("FATAL ERROR: Memory allocation failed.\n");
		exit(0);
	}
	
	newNode->data = str;
	newNode->link = NULL;

	return newNode;
}

// a sorted insert method that traverses the LL comparing the input to the tokens, finds where it belongs, and inserts it into the list
// logic order: check if head is null -> compare to head value -> compare to current token during traversal
// at each point during the logic trace: if found -> insert + return
void insert(struct node ** headRef, struct node* newNode){
	
	char * inputString = malloc(strlen(newNode->data) * sizeof(char));
	if (inputString == NULL) {
		printf("FATAL ERROR: Memory allocation failed.\n");
		exit(0);
	}
	strcpy(inputString, newNode->data);
	
	struct node * curr;

	// check if the list is empty
	// if it is -> insert at the head of the LL and return
	if(*headRef == NULL) {
		newNode->link = *headRef;
		*headRef = newNode;
		
		return;
	}
	// otherwise traverse the list
	else{
		char * currToken = (char *) malloc(strlen((*headRef)->data) * sizeof(char));
		if (currToken == NULL) {
			printf("FATAL ERROR: Memory allocation failed.\n");
			exit(0);
		}
		strcpy(currToken, (*headRef)->data);
		
		//head comparison check --- has to be done in its own seperate case following the chosen logic tree
		// if done with a methodology there could be one loop following the head null check
		// but somehow that went over my head and it would be more work to change it than to just keep the current logical order
		// the runtime or complexity of the insertion algorithm would not be affected however so changing it would only make it look nicer --- a project for another time
		int headUpdated = 0;
		int i = 0;
		while (i < strlen(inputString) && i < strlen(currToken)) {
			
			// same case check -> input char could either be same case or greater/less than the token char
			if (((inputString[i] >= 'a' && inputString[i] <= 'z') && (currToken[i] >= 'a' && currToken[i] <= 'z')) || ((inputString[i] >= 'A' && inputString[i] <= 'Z') && (currToken[i] >= 'A' && currToken[i] <= 'Z'))) {
			
				//current input char is greater than token char
				if (inputString[i] > currToken[i]) {
					newNode->link = *headRef;
					*headRef = newNode;
				
					headUpdated = 1;
				
					return;
				}
				//chars are equal -> loop again comparing next characters in input/token
				else if (inputString[i] == currToken[i]) {
					i++;
					// substring condition -> check if input is longer than the token
					if (i == strlen(inputString) || i == strlen(currToken)) {
						if (strlen(inputString) > strlen(currToken)) {
							newNode->link = *headRef;
							*headRef = newNode;
							
							headUpdated = 1;
							
							return;					
						}	
					}
					continue;
				}
				//token char is greater than the input char -> go to next token in list
				else {
					break;
				}
			}
			//input capital, token lowercase check -> input belongs here at the head
			else if ((inputString[i] >= 'A' && inputString[i] <= 'Z') && (currToken[i] >= 'a' && currToken[i] <= 'z')) {
				newNode->link = *headRef;
				*headRef = newNode;
				
				headUpdated = 1;
				
				return;
			}
			//input lowercase, token capital -> go to next token in list
			else{
				break;
			}
			
			//this code is never reached within the loop --- here for novelty and/or just in case?
			//printf("head check loop --- UNREACHABLE");
			i++;
		}
		
		// check if the input token replaced the head of the LL
		if (!headUpdated) {
		
			// begin looping through the remainder of the list (tokens after the head)
			curr = *headRef;
	
			int posFound = 0;
			while(curr->link != NULL){
		
				i = 0;
				free(currToken);
				currToken = (char *) malloc(strlen(curr->link->data) * sizeof(char));
				if (currToken == NULL) {
					printf("FATAL ERROR: Memory allocation failed.\n");
					exit(0);
				}
				strcpy(currToken, curr->link->data);
			
				//loop through the chars of the NEXT token and input strings
				while (i < strlen(inputString) && i < strlen(currToken)) {
			
					// check if chars are the same case 
					if (((inputString[i] >= 'a' && inputString[i] <= 'z') && (currToken[i] >= 'a' && currToken[i] <= 'z')) || ((inputString[i] >= 'A' && inputString[i] <= 'Z') && (currToken[i] >= 'A' && currToken[i] <= 'Z'))) {
			
						//input token is greater than the next token -> belongs at this point in the LL
						if (inputString[i] > currToken[i]) {
							posFound = 1;
							
							break;
						}
						//chars are equal -> loop again comparing next characters (same strings)
						else if (inputString[i] == currToken[i]) {
							i++;
							// substring condition
							if (i == strlen(inputString) || i == strlen(currToken)) {
								//check if input is longer than next token
								if (strlen(inputString) > strlen(currToken)) {
									posFound = 1;
									
									break;
								}
							}
							continue;
						}
						//token char is greater than the input char -> go to next token in list
						else {
							break;
						}
					}
					//input string capital, token lowercase -> found position in list
					else if ((inputString[i] >= 'A' && inputString[i] <= 'Z') && (currToken[i] >= 'a' && currToken[i] <= 'z')) {
						posFound = 1;
						break;
					}
					else {
						break;
					}
					i++;
				}
				//check if position of input string is found in LL
				if (posFound == 1) {
					break;
				}
				// if not -> go to next token
				else {
					curr = curr->link;
				}
			}
			
			// set input where it belongs in the linked list based on the above (sorted)insert
			newNode->link = curr->link;
			curr->link = newNode;
			
			return;
		}
	}
}

void print(struct node * head){
   	struct node * temp = head;
   	while(temp != NULL){
		printf("%s\n", temp->data);
		temp = temp->link;
	}
}

// method for freeing the LL created for storing the input tokens
void freeList(struct node* head)
{
   struct node * curr;

   while (head != NULL)
    {
       curr = head;
       head = head->link;
       free(curr);
    }
}

int main(int argc, char ** argv){
	
	//check if command line input is correct format (number of args)
	if (argc != 2){
       		printf("ERROR: Found %d arguments, was expecting 1.\nUsage: ./pointersorter \"input here\"\n", (argc-1));
       		exit(0);
   	}

   	char * input = (char *) malloc(strlen(argv[1]) * sizeof(char));
   	if (input == NULL) {
		printf("FATAL ERROR: Memory allocation failed.\n");
		exit(0);
	}
   	strcpy(input, argv[1]);
   	int length = strlen(input);
 	
   	//make new LL -> first element(base) is "head"
   	struct node * head = NULL;
	
	//begin looping through the input string -> i will be updated to the last index used by the previous token to reduce the number of loops
   	int i, j;
   	for (i = 0; i < length; i++) {
   		
   		//since length of tokens is unknown the first and last index of each token must be parsed by their indices before being stored in the linked list
   		int firstIndex;
   		int lastIndex; //= firstIndex;
		
		//check for alphanumeric -> otherwise ignore the character (it is a delimiter)
   		if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
   		
   			firstIndex = i;
   			lastIndex = 0;
   			
   			// loop for finding the current token from the input string to be stored in the list
   			for(j = firstIndex; j < length; j++) {
   				//check again for alphanumeric at each index
   				//	if - delimiter set last index to the previous index that was just checked
   				//	else - go to the next index of the input string
   				if (!((input[j] >= 'a' && input[j] <= 'z') || (input[j] >= 'A' && input[j] <= 'Z'))) {
   					lastIndex = j-1;
   					
   					break;
   				}
   				else if (j == (length-1)) {
   					lastIndex = j;
   				}
   			}
   			
			//make a temp string to store the token
   			char * temp = (char *) malloc(((lastIndex - firstIndex) + 1) * sizeof(char));
   			if (temp == NULL) {
				printf("FATAL ERROR: Memory allocation failed.\n");
				exit(0);
			}
   			int k;
   			for (k = 0; k < (lastIndex - firstIndex + 1); k++) {
   				//parse for the token based on the indices found
   				temp[k] = input[firstIndex + k];
   			}
   			temp[k] = '\0';
			
			// send the token to the sorted insert method -> token will then be in our LL
   			struct node * insertNode = newNode(temp);
			insert(&head, insertNode);
			
			i = lastIndex+1;
   		}
   	}

   	print(head);
   	
   	//free the (entire) LL
   	free(input);
   	freeList(head);

	return 0;
}
