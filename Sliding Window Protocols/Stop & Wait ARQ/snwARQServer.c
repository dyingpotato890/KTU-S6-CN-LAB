#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    int server, newSock, k = 5, m = 1, p;
    char buffer[1024];
    struct sockaddr_in servAddr, store;
    
    socklen_t addrSize = sizeof(servAddr);
    server = socket(PF_INET, SOCK_STREAM, 0);
    
    if (server == -1) {
        printf("Error creating socket\n");
        exit(1);
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8100);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));
    if (bind(server, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1){
        printf("Error in binding\n");
        exit(1);
    }

    if (listen(server, 5) == 0){
        printf("Server listening on port 8000\n");
    } else {
        printf("Error in listening\n");
        exit(1);
    }
    
    newSock = accept(server, (struct sockaddr*)&store, &addrSize);
    if (newSock == -1){
        printf("Error In Accepting Connection!\n");
        exit(1);
    }
    printf("Connection accepted\n");

    while (k != 0){
        int y = recv(newSock, buffer, sizeof(buffer), 0);
        if (y == -1){
            printf("Error In Receiving\n");
            exit(1);
        } else {
            printf("Server received: %s\n", buffer);
        }
    
        if (strncmp(buffer, "frame", 5) == 0){
            printf("Received frame %d successfully!\n", m);
        } else {
            printf("Frame %d Not Received!\n", m);
        }
        
        if (m % 2 == 0){
            strcpy(buffer, "ack");
        } else {
            strcpy(buffer, "kca");
            printf("Ack Lost!\n");
            
            for (p = 1; p <= 3; p++){
                printf("Waiting For %d Seconds\n", p);
                sleep(1);
            }
            
            printf("Retransmitting Ack\n");
            strcpy(buffer, "ack");
        }

        printf("Server sending: %s\n", buffer);
        int z = send(newSock, buffer, strlen(buffer), 0);
        if (z == -1){
            printf("Error In Sending\n");
            exit(1);
        }
        k--;
        m++;
    }
    
    close(newSock);
    close(server);
    return 0;
}

/*
Server listening on port 8000
Connection accepted
Server received: frame
Received frame 1 successfully!
Ack Lost!
Waiting For 1 Seconds
Waiting For 2 Seconds
Waiting For 3 Seconds
Retransmitting Ack
Server sending: ack
Server received: frame
Received frame 2 successfully!
Server sending: ack
Server received: frame
Received frame 3 successfully!
Ack Lost!
Waiting For 1 Seconds
Waiting For 2 Seconds
Waiting For 3 Seconds
Retransmitting Ack
Server sending: ack
Server received: frame
Received frame 4 successfully!
Server sending: ack
Server received: frame
Received frame 5 successfully!
Ack Lost!
Waiting For 1 Seconds
Waiting For 2 Seconds
Waiting For 3 Seconds
Retransmitting Ack
Server sending: ack
*/
