// CS 214 - Systems Programming, Asst3
// Created by Tom Burns and Andrew Dulichan on May 6, 2019

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
#include <signal.h>


pthread_mutex_t lock;

// catches Ctrl+C input
//TODO close all threads, sockets, and fds
void sigIntHandler(int sig_num) {
	
	signal(SIGINT, sigIntHandler);


	printf("\n\nSERVER CLOSED.\n");
	exit(0);
}

void * connection_handler(void * socket_desc) {
	
	// lock the current thread with global mutex when operations are being done on server
	pthread_mutex_lock(&lock);	

	int sock = *(int *) socket_desc;
	

	// unlock mutex when operation is complete
	pthread_mutex_unlock(&lock);
}

int main(int argc, char ** argv) {
	
	signal(SIGINT, sigIntHandler);
	int server_fd, client_socket, valread;
	struct sockaddr_in servaddr, clientaddr;
	int opt = 1;
	int addrlen1 = sizeof(servaddr);
	int addrlen2 = sizeof(clientaddr);
	pthread_t threads[100];
	int i = 0;

	if (argc != 2) {
		fprintf(stderr, "ERROR: Incorrect number of command line arguments for server setup.\n");
		exit(1);
	}
	
	// set server port # to listen on
	int port = atoi(argv[1]);
	if (port < 0 || port > 65535) {
		fprintf(stderr, "ERROR: Server port is not within range.\n");
		exit(1);
	}
	
	// multi threaded server on given port #
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {	
		perror("socket failed");
		exit(1);
	}
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(1);
	}
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(port);
	
	if (bind(server_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind failed");
		exit(1);
	}
	// max connections pending is 3 here
	if (listen(server_fd, 20) < 0) {
		perror("listen");
		exit(1);
	}
	printf("Waiting for incoming connections...\n");
	
	// ignore broken pipe signal
	signal(SIGPIPE, SIG_IGN);
	
	//pthread_attr_init(&pthread_attr_t);
	//pthread_attr_setdetachstate(&pthread_attr_t, PTHREAD_CREATE_DETACHED);
	
	
	
	while (1) { 
		
		if ((client_socket = accept(server_fd, (struct sockaddr *)&clientaddr, (socklen_t*)&addrlen2)) < 0) {
			perror("accept");
			exit(1);
		}
		
		printf("Connection accepted\n");
		
		if (pthread_create(&threads[i], NULL, connection_handler, (void*) &client_socket) < 0) {
			perror("could not create thread");
			return 1;
		}
		
		printf("Thread created for new client connection.\n");
		
	}
	
    return 0;
}
