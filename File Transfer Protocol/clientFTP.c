#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
	int client_socket;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE] = {0};
	char filename[BUFFER_SIZE] = {0};

	// Create client socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0) {
	    perror("Socket Creation Failed!");
	    exit(EXIT_FAILURE);
	}

	// Configure server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Connect to server
	if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("Connection Failed!");
		exit(EXIT_FAILURE);
	}
	
	// Get filename from user
	printf("Enter The Filename To Request: ");
	scanf("%s", filename);

	// Send filename to server
	send(client_socket, filename, strlen(filename), 0);

	// Receive and print file content
	printf("\nFile Content Received:\n");
	while (recv(client_socket, buffer, BUFFER_SIZE, 0) > 0) {
		printf("%s", buffer);
		memset(buffer, 0, BUFFER_SIZE);
	}

	printf("\n");
	close(client_socket);

	return 0;
}
