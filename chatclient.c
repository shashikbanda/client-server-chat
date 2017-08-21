#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void readLineFromInput(char* line);
int main( int argc, char *argv[] ) {
	int port; //Port number entered from command line.
	int sock_fd; //Socket file descriptor.
	int server_fd; //Server file descriptor.
	char name[15];
	char input[512]; //Add extra characters for length of username.
	char buffer[512] = {0};


	struct sockaddr_in address;
	struct sockaddr_in serv_addr;

	if(argc < 3) {
		printf("Please enter a PORT number to connect to.\n");
		return 1;
	}
	
	port = atoi(argv[2]);
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);

	printf("Please enter username: ");
	scanf("%s", name);
	while(strlen(name) > 10) {
		printf("Sorry, name can be at most 10 characters.\n");
		memset(name, 0, sizeof(name));
		printf("Please enter username: ");
		scanf("%s", name);
	}
	//Need to do error checking to make sure name is less than 10 characters.

	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    char successMsg[100];
    strcpy(successMsg, "Hosts Successfully Connected on Port ");
    strcat(successMsg, argv[2]);
    printf("%s\n", successMsg);
	send(sock_fd, successMsg, strlen(successMsg), 0);

    char str[512];
	strcpy(str, name);
	strcat(str, "> ");
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	printf("%s> ", name);

	// scanf("%s", input);
	scanf("%[^\n]s", input);

	while(strlen(input) > 500) {
		printf("Input Message Too Long. Please keep under 500 characters.\n");
		printf("%s> ", name);
		setvbuf(stdin, NULL, _IONBF, 0);
		scanf("%[^\n]s", input);
	}
	
	strcat(str, input);
	
	while(strcmp(input, "\\quit") != 0) {
		send(sock_fd, str, strlen(str), 0);
		read( sock_fd , buffer, sizeof(buffer));
		if(strcmp(buffer, "\\quit") != 0) {
			printf("%s\n", buffer);
		}
		else {
			memset(input ,0, sizeof(input));
			strcpy(input, "\\quit");
			printf("%s\n", input);
			break;
		}
		
		memset(buffer, 0, sizeof(buffer));
		memset(input ,0, sizeof(input));
		memset(str ,0, sizeof(str));
		
		printf("%s> ", name);
		setvbuf(stdin, NULL, _IONBF, 0);
		scanf("%[^\n]s", input);

		while(strlen(input) > 500) {
			printf("Input Message Too Long. Please keep under 500 characters.\n");
			printf("%s> ", name);
			setvbuf(stdin, NULL, _IONBF, 0);
			scanf("%[^\n]s", input);
		}

		strcpy(str, name);
		strcat(str, "> ");
		strcat(str, input);
	}
	send(sock_fd, input, strlen(input), 0);

	return 0;
}

