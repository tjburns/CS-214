
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>


#define PORT 8609

// TODO: Write error-checking for this function
void configure() 
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

        strcat(server_info, ip_address_hostname);
        strcat(server_info, delimiter);
        strcat(server_info, port_num);

        config_fd = open(".configure", O_CREAT | O_RDWR, S_IRGRP | S_IWGRP);
        write(config_fd, server_info, sizeof(server_info));
        close(config_fd);
    }
}

// helper function
int checkConfigure() 
{
    int config_fd = 0;

    config_fd = open(".configure", O_RDONLY);

    if (config_fd == -1)
    {
        fprintf(stderr, "Error: file could not be opened.");
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
            fprintf(stderr, "Error: The configure command was not run before this command was called.");
            return 1;
        }

	    char filebuffer[filesize];
	    file_contents = read(config_fd, &filebuffer, filesize);

        // No-body for loop that goes through and saves the IP address and Port from the .configure file to a variable for comparison
        for (char* config_tokens = strtok(file_contents, "\n"); config_tokens != NULL; config_tokens = strtok(NULL, "\n"))
        {
            continue;
        }

        if (config_tokens[0] != argv[2] && config_tokens[1] != argv[3])
        {
            fprintf(stderr, "Error: The supplied IP address/hostname and/or Port does not match what is stored in .configure.");
            return 2;
        }
        // Does this need coding here? ---> "All other commands must also fail if a connection to the server cannot be established."
        return 0;
    }
}

void checkout(char* projectname)
{


    if (argc != 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments given. 3 arguments expected.");
        exit(1);
    }

    if ( || checkConfigure() == 1)
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
