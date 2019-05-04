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
	
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {	
		perror("socket failed");
		exit(1);
	}
	
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(1);
	}
	    
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(1);
	}
	
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(1);
	}
	
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
		perror("accept");
		exit(1);
	}
	
	//valread = read(new_socket, buffer, 1024);
	//printf("%s\n", buffer);
	//send(new_socket, hello, strlen(hello), 0);
	//printf("hello sent\n");
	
	valread = read(new_socket, buffer, 1024);
	//TODO error checking
	int fd = open(buffer, O_RDONLY);
	printf("File opened on server side.\n");
	int status = 0;
	/* print out the file char by char 
	char filebuff;
	do {
		status = read(fd, &buffer, 1);
		send(new_socket, buffer, 1, 0);
	
	} while (status > 0);
	*/
	int filesize = 0;
	struct stat info;
	if ((buffer != NULL) && (stat(buffer, &info) == 0))
		filesize = (int)info.st_size;
	char filebuff[filesize];
	status = read(fd, &filebuff, filesize);
	send(new_socket, filebuff, filesize, 0);
	printf("File contents sent to client side.\n");

	return 0;
}
