#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8609


int main(int argc, char ** argv) {
	
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char * hello  = "Hello from client";
	char buffer[1024] = {0};

	char * filename = "./testfile.txt";
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed\n");
		return -1;
	}

	//send(sock, hello, strlen(hello), 0);
	//printf("Hello message sent\n");
	//valread = read(sock, buffer, 1024);
	//printf("%s\n", buffer);
	
	send(sock, filename, strlen(filename), 0);
	int filesize = 0;
	struct stat info;	
	if ((filename != NULL) && (stat(filename, &info) == 0))
		filesize = (int)info.st_size;
	printf("sent a filename\nfilecontents:\n");
	/* print out the file char by char
	do {
		valread = read(sock, buffer, 1);
		printf("%s", buffer);
	} while (valread > 0);
	*/
	/* print out by single buffer */
	valread = read(sock, buffer, filesize);
	printf("%s", buffer);
	
	return 0;
}
