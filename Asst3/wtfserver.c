#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char ** argv) {

	if (argc != 2) {
		fprintf(stderr, "ERROR: Incorrect number of command line arguments for server setup.\n");
		exit(0);
	}
	
	// set server port # to listen on
	int port = atoi(argv[1]);

	// multi threaded server on given port #
	
	
    return 0;
}
