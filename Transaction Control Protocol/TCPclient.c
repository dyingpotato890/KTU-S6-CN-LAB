/*
Compile Using: gcc TCPclient.c -o client
./client
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	char buffer[100];
	int k; // Error Flag
	int sock_desc;
	struct sockaddr_in client;
	
	/*Creating Socket*/
	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_desc == -1){
		printf("Error In Socket Creation!");
		return 1;
	}
	printf("Socket Created Successfully!\n");
	
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = 3003;
	
	/*Connecting Process*/
	k = connect(sock_desc, (struct sockaddr *)&client, sizeof(client));
	if (k == -1){
		printf("Error In Connecting To The Server!");
		return 1;
	}
	printf("Connection Successful!\n");
	
	/*Data Sending Process*/
	printf("\nEnter The Data To Be Sent: ");
	fgets(buffer, 100, stdin);
		
	k = send(sock_desc, buffer, strlen(buffer), 0);
	if (k == -1){
		printf("Error In Sending Data!");
		return 1;
	}
	printf("Message Sent!\n");
		
	close(sock_desc);
	
	return 0;
}