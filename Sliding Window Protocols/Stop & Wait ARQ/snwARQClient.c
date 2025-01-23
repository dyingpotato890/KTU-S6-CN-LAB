#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    int client, y, x, k = 5, m = 1, p;
    char buffer[1024];
    struct sockaddr_in servAddr;
    
    socklen_t addrSize = sizeof(servAddr);
    client = socket(PF_INET, SOCK_STREAM, 0);
    
    if (client == -1) {
        printf("Error creating socket\n");
        exit(1);
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8100);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

    y = connect(client, (struct sockaddr*)&servAddr, addrSize);
    if (y == -1){
        printf("Error In Connection\n");
        exit(1);
    } else {
        printf("Connected to server\n");
    }
    
    while (k != 0){
        if (m <= 5){
            printf("Sending %d\n", m);
        }

        if (m % 2 == 0){
            strcpy(buffer, "frame");
        } else {
            strcpy(buffer, "error");
            printf("Packet Lost!\n");
            
            for (p = 1; p <= 3; p++){
                printf("Waiting For %d Seconds\n", p);
                sleep(1);
            }
            
            printf("Retransmitting Packet\n");
            strcpy(buffer, "frame");
        }

        printf("Client sending: %s\n", buffer);
        int x = send(client, buffer, strlen(buffer), 0);
        if (x == -1){
            printf("Error In Sending\n");
            exit(1);
        } else {
            printf("Sent %d\n", m);
        }
        
        int z = recv(client, buffer, sizeof(buffer), 0);
        if (z == -1){
            printf("Error In Receiving Data!\n");
            exit(1);
        } else {
            printf("Received response: %s\n", buffer);
        }

        k--;
        m++;
        
        if (strncmp(buffer, "ack", 3) == 0){
            printf("Acknowledgement Received For %d\n", m - 1);
        } else {
            printf("Acknowledgement Not Received\n");
        }
    }
    
    close(client);
    return 0;
}


/*
Connected to server
Sending 1
Packet Lost!
Waiting For 1 Seconds
Waiting For 2 Seconds
Waiting For 3 Seconds
Retransmitting Packet
Client sending: frame
Sent 1
Received response: ackme
Acknowledgement Received For 1
Sending 2
Client sending: frame
Sent 2
Received response: ackme
Acknowledgement Received For 2
Sending 3
Packet Lost!
Waiting For 1 Seconds
Waiting For 2 Seconds
Waiting For 3 Seconds
Retransmitting Packet
Client sending: frame
Sent 3
Received response: ackme
Acknowledgement Received For 3
Sending 4
Client sending: frame
Sent 4
Received response: ackme
Acknowledgement Received For 4
Sending 5
Packet Lost!
Waiting For 1 Seconds
Waiting For 2 Seconds
Waiting For 3 Seconds
Retransmitting Packet
Client sending: frame
Sent 5
Received response: ackme
Acknowledgement Received For 5
*/
