#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

void rsendd(int ch, int c_sock) {
	char buffer2[60];
	bzero(buffer2, sizeof(buffer2));
	
	strcpy(buffer2, "Retransmission Message: ");
	buffer2[strlen(buffer2)] = (ch) + '0';
	buffer2[strlen(buffer2)] = '\0';
	
	printf("Resending Message To CLient: %s \n", buffer2);
	write(c_sock, buffer2, sizeof(buffer2));
	usleep(1000);
}


int main(){
	int c_sock;
	
	int s_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server, other;
	memset(&server, 0, sizeof(server));
	memset(&other, 0, sizeof(other));
	
	server.sin_family = AF_INET;
	server.sin_port = htons(7004);
	server.sin_addr.s_addr = INADDR_ANY;
	socklen_t add;
	
	if (bind(s_sock, (struct sockaddr *)&server, sizeof(server)) == -1) {
		printf("Binding Failed!\n");
		return 0;
	}
	
	printf("\nServer - Selective Repeat ARQ\n\n");
	
	listen(s_sock, 10);
	add = sizeof(other);
	c_sock = accept(s_sock, (struct sockaddr *)&other, &add);
	
	time_t t1, t2;
	char msg[50] = "Server Message: ";
	char buffer[50];
	int flag = 1;
	
	fd_set set1, set2, set3;
	struct timeval timeout1, timeout2, timeout3;
	int rv1, rv2, rv3;
	
	int tot = 0;
	int ok[20];
	memset(ok, 0, sizeof(ok));
	
	while (tot < 9) {
		int toti = tot;
		for (int j = (0 + toti); j < (3 + toti); j++) {
			bzero(buffer, sizeof(buffer));
			char buff2[60];
			bzero(buff2, sizeof(buff2));
			strcpy(buff2, "Server Message: ");
			
			buff2[strlen(buff2)] = (j) + '0';
			buff2[strlen(buff2)] = '\0';
			
			printf("Message Sent To Client: %s \n", buff2);
			write(c_sock, buff2, sizeof(buff2));
			usleep(1000);
		}
		
		for (int k = 0 + toti; k < (toti + 3); k++) {
		qq:
		
		FD_ZERO(&set1);
		FD_SET(c_sock, &set1);
		
		timeout1.tv_sec = 2;
		timeout1.tv_usec = 0;
		
		rv1 = select(c_sock + 1, &set1, NULL, NULL, &timeout1);
		if (rv1 == -1) {
			perror("Select Error");
		} else if (rv1 == 0) {
			printf("Timeout For Message: %d \n", k);
			rsendd(k, c_sock);
			goto qq;
		} else {
			read(c_sock, buffer, sizeof(buffer));
			printf("Message From Client: %s \n", buffer);
			if (buffer[0] == 'n') {
				printf("Corrupted Message Acknowledgement (msg %d) \n", buffer[strlen(buffer) - 1] - '0');
				rsendd((buffer[strlen(buffer) - 1] - '0'), c_sock);
				goto qq;
			} else {
				tot++;
			}
		}
		}
	}
	
	close(c_sock);
	close(s_sock);
	return 0;
}
