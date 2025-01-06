/*
Compile Using: gcc UDPclient.c -o client
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
	struct sockaddr_in server, client;
	
	/*Creating Socket*/
	sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_desc == -1){
		printf("Error In Socket Creation!");
		return 1;
	}
	printf("Socket Created Successfully!\n");
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(3004);
	
	/*Data Sending Process*/
	printf("\nEnter The Data To Be Sent: ");
	fgets(buffer, 100, stdin);
		
	k = sendto(sock_desc, buffer, strlen(buffer), 0, (struct sockaddr *)&server, sizeof(server));
	if (k == -1)
		printf("Error In Sending Data!");
	printf("Message Sent Successfully!\n");
		
	close(sock_desc);
	
	return 0;
}