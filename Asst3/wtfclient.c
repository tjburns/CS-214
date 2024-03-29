// CS 214 – Systems Programming, Asst3
// Created by Tom Burns and Andrew Dulichan on May 6, 2019

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
//#include <openssl/sha.h>


#define PORT 8609

int fileSize(char * filename) {
	int ret = 0;
	struct stat info;
	
	if ((filename != NULL) && (stat(filename, &info) == 0))
		ret = (int)info.st_size;
	return ret;
}


// TODO: Write error-checking for this function
void wtfconfigure(int argc, char** argv) 
{
    char* ip_address_hostname = (char*)malloc(strlen(argv[2]) * sizeof(char));
    char* port_num = (char*)malloc(strlen(argv[3]) * sizeof(char));
    char* delimiter = "\n";
    int config_fd = 0;
    char* server_info = (char*)malloc((strlen(argv[2])+5+strlen(argv[3])) * sizeof(char));

    if (argc != 4)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 4 arguments expected.\n");
        exit(1);
    }
    else
    {
        strcpy(ip_address_hostname, argv[2]);
        strcpy(port_num, argv[3]);
        printf("ip: %s\nport: %s\n", ip_address_hostname, port_num);
		int port = atoi(port_num);
		
		if (port < 0 || port > 65535) {
			fprintf(stderr, "ERROR: Server port is not within range.\n");
			exit(1);
		}
		
        strcat(server_info, ip_address_hostname);
        strcat(server_info, delimiter);
        strcat(server_info, port_num);

        config_fd = open(".configure", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        printf(".configure file created\n");
        write(config_fd, server_info, strlen(server_info));
        close(config_fd);
    }
}

// helper function
char ** checkConfigure() 
{
	char ** config_tokens;
	config_tokens = (char**) malloc(10 * sizeof(char*));
	int i = 0, j = 0;

	for (i = 0; i < 10; i++)
	{
		config_tokens[i] = (char*)malloc(100 * sizeof(char));
	}

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 100; j++)
			config_tokens[i][j] = 0;
	}

    int config_fd = 0;
    int status = 0;

    config_fd = open(".configure", O_RDONLY);

    if (config_fd == -1)
    {
        printf("Configure has not been called yet.\n");
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
        	i++;
        	tok = strtok(NULL, "\n");
        }
	
		for (i = 0; i < 2; i++) {
			printf("token[%d]: %s\n", i, config_tokens[i]);
		}
		
        if (config_tokens[0] == NULL || config_tokens[1] == NULL)
        {
            fprintf(stderr, "Error: Server information could not be fetched from .configure file.\n");
            exit(1);
        }
    }
    
    return config_tokens;
}

void checkout(int argc, char** argv)
{
	
    if (argc != 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 3 arguments expected.");
        exit(1);
    }
	
}

void update(int argc, char** argv)
{
	
    if (argc != 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 3 arguments expected.");
        exit(1);
    }
}

void upgrade(int argc, char** argv)
{
	
    if (argc != 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 3 arguments expected.");
        exit(1);
    }
}

void commit(int argc, char** argv)
{
	
    if (argc != 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 3 arguments expected.");
        exit(1);
    }
}

void push(int argc, char** argv)
{
	
    if (argc != 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 3 arguments expected.");
        exit(1);
    }
}

void create(int argc, char** argv)
{
	
	if (argc != 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 3 arguments expected.");
        exit(1);
    }
}

void destroy(int argc, char** argv)
{
	
	if (argc != 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 3 arguments expected.");
        exit(1);
	}
}

void add(int argc, char** argv)
{
	if (argc != 4)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 4 arguments expected.");
        exit(1);
	}
}

void wtfremove(int argc, char** argv)
{
	if (argc != 4)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 4 arguments expected.");
        exit(1);
	}
}

void currentversion(int argc, char** argv)
{
	if (argc != 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 3 arguments expected.");
        exit(1);
	}
}

void history(int argc, char** argv)
{
	
	if (argc != 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 3 arguments expected.");
        exit(1);
	}
}

void rollback(int argc, char** argv)
{
	
	if (argc != 4)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 4 arguments expected.");
        exit(1);
	}
}

void compress()
{
	// To be added
}

int wtfconnect()
{
	char ** config_content = checkConfigure();
	// config_content[0] is server ip
	// config_content[1] is server port
	
	struct sockaddr_in client_addr;
	struct sockaddr_in serv_addr;
	int sock = 0;
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
		fprintf(stderr, "\nSocket creation error\n");
		return 1;
	}
	
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(config_content[1]));
	
	if (inet_pton(AF_INET, config_content[0], &serv_addr.sin_addr) <= 0) {
		fprintf(stderr, "Invalid address/Address not supported.\n");
		return 1;
	}
	
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		fprintf(stderr, "Connection failed\n");
		return 1;
	}
}

int main (int argc, char ** argv) {
	
	if (argc < 3) {
		fprintf(stderr, "Incorrect number of command line arguments.\n");
		exit(1);
	}
	
	// determine client operation
	if (strcmp(argv[1], "configure") == 0) {
		wtfconfigure(argc, argv);
		return 0;
	}
	
	// connect to wtf using configured ip and port
	int sock = wtfconnect();
	
	if (strcmp(argv[1], "checkout") == 0)
	{
		checkout(argc, argv);
	}
	else if (strcmp(argv[1], "update") == 0)
	{
		update(argc, argv);
	}
	else if (strcmp(argv[1], "upgrade") == 0)
	{
		upgrade(argc, argv);
	}
	else if (strcmp(argv[1], "commit") == 0)
	{
		commit(argc, argv);
	}
	else if (strcmp(argv[1], "push") == 0)
	{
		push(argc, argv);
	}
	else if (strcmp(argv[1], "create") == 0)
	{
		create(argc, argv);
	}
	else if (strcmp(argv[1], "destroy") == 0)
	{
		destroy(argc, argv);
	}
	else if (strcmp(argv[1], "add") == 0)
	{
		add(argc, argv);
	}
	else if (strcmp(argv[1], "remove") == 0)
	{
		wtfremove(argc, argv);
	}
	else if (strcmp(argv[1], "currentversion") == 0)
	{
		currentversion(argc, argv);
	}
	else if (strcmp(argv[1], "history") == 0)
	{
		history(argc, argv);
	}
	else if (strcmp(argv[1], "rollback") == 0)
	{
		rollback(argc, argv);
	}
	else if (strcmp(argv[1], "compress") == 0)
	{
		// To be added
	}
	else
	{
		fprintf(stderr, "No client commands given to the client side WTF client.\n");
	}
	
	return 0;
}
