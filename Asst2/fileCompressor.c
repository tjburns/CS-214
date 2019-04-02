
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "huffmanTree.h"
#include "countEntries.h"

//TODO check if file is empty

void checkRegFile(char * path) {
	struct stat path_stat;
	stat(path, &path_stat);
	if(S_ISREG(path_stat.st_mode) <= 0) {
		fprintf(stderr, "Error: File given is not a regular file.\n");
		exit(1);
	}
}

int isCompressedFile(char * path) {
	char * ext = path;
	while (strstr(ext+1, ".") != NULL) {
		//printf("%s\n", ext);
		ext = strchr(ext+1, '.');
	}
	//printf("%s\n", ext);
	return !strcmp(ext, ".hcz");
}

// recursive operation that prints all files and directories in current directory and its subdirectories
void printdir(char * dirname) {
	DIR* dd = opendir(dirname);
	
	if (dd == NULL) {
		fprintf(stderr, "Error: Directory given does not exist");
		return;
	}
	printf("opened directory\n");
		
	struct dirent* status;
		
	while ((status = readdir(dd)) != NULL) {
		
		if (status->d_type == DT_DIR) {
			char path[1024];
			int i = 0;
			for(i = 0; i < 1024; i++) {
				path[i] = 0;
			}
			if (strcmp(status->d_name, ".") == 0 || strcmp(status->d_name, "..") == 0) {
				continue;
			}
			//printf("%s\n", dirname);
			strcat(path, dirname);
			strcat(path, status->d_name);
			strcat(path, "/");
			//printf("%s\n", path);
			printf("%s\n", status->d_name);
			printdir(path);
		}
		else {
			printf("%s\n", status->d_name);
		}
	}
	closedir(dd);
	
}

// same methodology as printDir but now performs an operation on each file enountered
void recursiveDirOp(char * dirname, int op, char * codebook) {
	DIR* dd = opendir(dirname);
	
	if (dd == NULL) {
		fprintf(stderr, "Error: Directory given does not exist");
		return;
	}
	printf("opened directory\n");
		
	struct dirent* status;
	char path[1024];
	int i = 0;
	
	while ((status = readdir(dd)) != NULL) {
		
		// current DIR* is a directory
			// open dir and recurse
		if (status->d_type == DT_DIR) {
			if (strcmp(status->d_name, ".") == 0 || strcmp(status->d_name, "..") == 0) {
				continue;
			}
			for(i = 0; i < 1024; i++) {
				path[i] = 0;
			}
			//printf("%s\n", dirname);
			strcat(path, dirname);
			strcat(path, status->d_name);
			strcat(path, "/");
			//printf("%s\n", path);
			printf("%s\n", status->d_name);
			recursiveDirOp(path, op, codebook);
		}
		// current DIR* is a file descriptor
		else if (status->d_type == DT_REG) {
			// find path of current file
			printf("found a file: %s\n", status->d_name);
			for(i = 0; i < 1024; i++) {
				path[i] = 0;
			}
			printf("%s\n", dirname);
			strcat(path, dirname);
			strcat(path, status->d_name);
			
			if (op == 0)
				countWords(path);
			if (op == 1)
				compress(path, codebook);
			if (op == 2) {
				if (isCompressedFile(path)) {
					decompress(path, codebook);
				}
			}
		}
	}
	closedir(dd);
}

int main (int argc, char ** argv) {
	
	char filename[1024];
	char dirname[1024];
	char bookname[1024];
	// runtime flags
	int recursiveMode = 0;
	int operation = -1;
	
	//countWords("./test.txt");
	//countWords("./test2.txt");
	//countWords("./test3.txt");
	//countWords("./test5.txt");
	//printdir("./level0/", 0);
	
	// command line comprehension - finding operation type and error cases
	if (argc <= 2) {
		fprintf(stderr, "Error: Incorrect command line input for fileCompressor.\n");
		exit(1);
	}
	
	if (strcmp(argv[1], "-R") == 0 || strcmp(argv[2], "-R") == 0) {
		recursiveMode = 1;
	}
	if (strcmp(argv[1], "-b") == 0 || strcmp(argv[2], "-b") == 0) {
		operation = 0;
	}
	else if (strcmp(argv[1], "-c") == 0 || strcmp(argv[2], "-c") == 0) {
		operation = 1;
	}
	else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[2], "-d") == 0) {
		operation = 2;
	}
	else {
		fprintf(stderr, "Error: No operation specified.\n");
		exit(1);
	}
	
	if (operation == -1) {
		fprintf(stderr, "Error: Incorrect command line input for fileCompressor.\n");
		exit(1);
	}
	
	// nonrecursive fileCompressor run
	if (recursiveMode == 0) {
		
		// build codebook - nonrecursive
		if (operation == 0) {
		
			// clear potential previous codebook ~ also in clean operation in makefile
			remove("HuffmanCodebook");
			
			
			// check if input is formatted correctly for comprehension
				// format: ./fileComressor -b <file>
			if (argc != 3) {
				fprintf(stderr, "Error: Incorrect number of command line arguments.\n");
				exit(1);
			}
			
			strcpy(filename, argv[2]);
			checkRegFile(filename);
			countWords(filename);
			createCodebook();
		}
		// compress - nonrecursive
		else if (operation == 1) {
			
			// check if input is formmated correctly for comprehension
			// format: ./fileCompressor -c <file> <codebook>
			if (argc != 4) {
				fprintf(stderr, "Error: Incorrect number of command line arguments.\n");
				exit(1);
			}
			
			strcpy(filename, argv[2]);
			strcpy(bookname, argv[3]);
			checkRegFile(filename);
			compress(filename, bookname);
		} 
		// decompress - nonrecursive
		else if (operation == 2) {
			
			// check if input is formmated correctly for comprehension
			// format: ./fileCompressor -d <file> <codebook>
			if (argc != 4) {
				fprintf(stderr, "Error: Incorrect number of command line arguments.\n");
				exit(1);
			}
			
			strcpy(filename, argv[2]);
			strcpy(bookname, argv[3]);
			//checkRegFile(filename);
			if (isCompressedFile(filename)) {
				decompress(filename, bookname);
			}
			else {
				fprintf(stderr, "Error: File given is not a compressed file.\n");
			}
		}
	}
	// recursive mode fileCompressor run
	else {
	
		// build codebook - recursive
		if (operation == 0) {
		
			// clear potential previous codebook ~ also in clean operation in makefile
			remove("HuffmanCodebook");
			
			// check if input is formmated correctly for comprehension
			// format: ./fileCompressor -b <directory>
			if (argc!= 4) {
				fprintf(stderr, "Error: Incorrect number of command line arguments.\n");
				exit(1);
			}
			
			strcpy(dirname, argv[3]);
			
			recursiveDirOp(dirname, operation, "");
			createCodebook();
		}
		// compress - recursive
		else if (operation == 1) {
			
			if (argc!= 5) {
				fprintf(stderr, "Error: Incorrect number of command line arguments.\n");
				exit(1);
			}
			
			strcpy(dirname, argv[3]);
			strcpy(bookname, argv[4]);
			
			recursiveDirOp(dirname, operation, bookname);
		} // decompress - nonrecursive
		else if (operation == 2) {
			if (argc!= 5) {
				fprintf(stderr, "Error: Incorrect number of command line arguments.\n");
				exit(1);
			}
			
			strcpy(dirname, argv[3]);
			strcpy(bookname, argv[4]);
			
			recursiveDirOp(dirname, operation, bookname);
		}
	}
	
	return 0;
}
