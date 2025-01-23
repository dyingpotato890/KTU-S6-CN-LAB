#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int isFaulty() {
	int d = rand() % 4;
	return (d > 2);
}

int main(){
	srand(time(0));
	
	int c_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	
	client.sin_family = AF_INET;
	client.sin_port = htons(7004);
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if (connect(c_sock, (struct sockaddr *)&client, sizeof(client)) == -1) {
		printf("Connection Failed!\n");
		return 0;
	}
	
	printf("\nClient - With Individual Acknowledgement Scheme\n\n");
	
	char msg1[50] = "Acknowledgement of: ";
	char msg2[50];
	char msg3[50] = "Negative Acknowledgement: ";
	char buffer[100];
	
	int count = -1, flag = 1;
	while (count < 8) {
		bzero(buffer, sizeof(buffer));
		bzero(msg2, sizeof(msg2));
		
		if (count == 7 && flag == 1) {
			printf("Here\n");
			flag = 0;
			read(c_sock, buffer, sizeof(buffer));
			continue;
		}
		
		int n = read(c_sock, buffer, sizeof(buffer));
		char i = buffer[strlen(buffer) - 1];
		printf("Message Received From Server: %s \n", buffer);
		
		int isFault = isFaulty();
		printf("Corruption Status: %d \n", isFault);
		printf("Acknowledgement Sent For Message.\n");
		
		if (isFault) {
			strcpy(msg2, msg3);
		} else {
			strcpy(msg2, msg1);
			count++;
		}
		
		msg2[strlen(msg2)] = i;
		write(c_sock, msg2, sizeof(msg2));
	}
	
	close(c_sock);
	return 0;
}
