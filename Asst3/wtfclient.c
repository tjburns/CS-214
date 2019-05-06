
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <openssl/sha.h>


#define PORT 8609

int fileSize(char * filename) {
	int ret = 0;
	struct stat info;
	
	if ((filename != NULL) && (stat(filename, &info) == 0))
		ret = (int)info.st_size;
	return ret;
}


// TODO: Write error-checking for this function
void configure(int argc, char ** argv) 
{
    char* ip_address_hostname = "";
    char* port_num = "";
    char* delimiter = "\n";
    int config_fd = 0;
    char* server_info = "";

    if (argc != 4)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 4 arguments expected.");
        exit(1);
    }
    else
    {
        ip_address_hostname = argv[2];
        port_num = argv[3];
		int port = atoi(port_num);
		
		if (port < 0 || port > 65535) {
			fprintf(stderr, "ERROR: Server port is not within range.\n");
			exit(1);
		}
		
        strcat(server_info, ip_address_hostname);
        strcat(server_info, delimiter);
        strcat(server_info, port_num);

        config_fd = open(".configure", O_CREAT | O_RDWR, S_IRGRP | S_IWGRP);
        write(config_fd, server_info, sizeof(server_info));
        close(config_fd);
    }
}

// helper function
char ** checkConfigure() 
{
	char ** config_tokens;
	config_tokens = (char**) malloc(10 * sizeof(char*));
	int i = 0, j = 0;
	for (i = 0; i < 10; i++) {
		config_tokens[i] = (char*)malloc(100 * sizeof(char));
	}
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 100; j++)
			config_tokens[i][j] = 0;
	}
    int config_fd = 0;
    int status = 0;

    config_fd = open(".configure", O_RDONLY);

    if (config_fd == -1)
    {
        fprintf(stderr, "Error: file could not be opened.\n");
        exit(1);
    }
    else
    {
        int filesize = 0;
	    struct stat size_info;

	    if ((".configure" != NULL) && (stat(".configure", &size_info) == 0))
        {
            filesize = (int)size_info.st_size;
        }
        else // failure case to run if configure was not called before the command in question was called
        {
            fprintf(stderr, "Error: The configure command was not run before this command was called.\n");
            exit(1);
        }

	    char filebuffer[filesize];
	    status = read(config_fd, &filebuffer, filesize);

		i = 0;
        char * tok = strtok(filebuffer, "\n");
        
        while (tok != NULL) {
        	config_tokens[i] = tok;
        	tok = strtok(NULL, "\n");
        }

        if (config_tokens[0] == NULL || config_tokens[1] != NULL)
        {
            fprintf(stderr, "Error: Server information could not be fetched from .configure file.\n");
            exit(1);
        }
    }
    
    return config_tokens;
}

void checkout(int argc, char ** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 3 arguments expected.");
        exit(1);
    }

    //if ( || checkConfigure() == 1)
}

void update(char* projectname)
{

}

void upgrade(char* projectname)
{

}

void commit(char* projectname)
{

}

void push(char* projectname)
{

}

void create(char* projectname)
{

}

void destroy(char* projectname)
{

}

void add(char* projectname, char* filename)
{
	
}

void wtfremove(char* projectname, char* filename)
{

}

void currentversion(char* projectname)
{

}

void history(char* projectname)
{

}

void rollback(char* projectname, int version_num)
{

}

void compress() {

}

int wtfconnect() {
	
	char ** config_content = checkConfigure();
	// config_content[0] is server ip
	// config_content[1] is server port
	
	struct sockaddr_in client_addr;
	struct sockaddr_in serv_addr;
	int sock = 0;
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
		fprintf(stderr, "\nSocket creation error\n");
		exit(1);
	}
	
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(config_content[1]));
	
	if (inet_pton(AF_INET, config_content[0], &serv_addr.sin_addr) <= 0) {
		fprintf(stderr, "Invalid address/Address not supported.\n");
		exit(1);
	}
	
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		fprintf(stderr, "Connection failed\n");
		exit(1);
	}
	
}

int main (int argc, char ** argv) {
	
	if (argc < 3) {
		fprintf(stderr, "Incorrect number of command line arguments.\n");
	}
	
	// determine client operation
	if (strcmp(argv[1], "configure") == 0) {
		configure(argc, argv);
	}
	
	// connect to wtf using configured ip and port
	int sock = wtfconnect();
	
	if (strcmp(argv[1], "checkout") == 0) {
		checkout(argc, argv);
	}
	else if (strcmp(argv[1], "update") == 0) {
	
	}
	else if (strcmp(argv[1], "upgrade") == 0) {
	
	}
	else if (strcmp(argv[1], "commit") == 0) {
	
	}
	else if (strcmp(argv[1], "push") == 0) {
	
	}
	else if (strcmp(argv[1], "create") == 0) {
	
	}
	else if (strcmp(argv[1], "destroy") == 0) {
	
	}
	else if (strcmp(argv[1], "add") == 0) {
	
	}
	else if (strcmp(argv[1], "remove") == 0) {
	
	}
	else if (strcmp(argv[1], "currentversion") == 0) {
	
	}
	else if (strcmp(argv[1], "history") == 0) {
	
	}
	else if (strcmp(argv[1], "rollback") == 0) {
	
	}
	else if (strcmp(argv[1], "compress") == 0) {
	
	}
	
	return 0;
}
