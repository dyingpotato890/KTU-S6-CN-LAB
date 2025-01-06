/*
Compile Using: gcc UDPserver.c -o server
./server 3004
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int sock_desc;
    char buffer[100];
    socklen_t client_len;
    int k; // For error checking
    struct sockaddr_in server, client;
    
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    /* Creating Socket */
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc == -1) {
        perror("Error In Socket Creation");
        return 1;
    }
    printf("Socket Created Successfully!\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1])); // Get Port from Argument

    /* Binding Process */
    k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1) {
        perror("Error In Binding");
        close(sock_desc);
        return 1;
    }
    printf("Socket Binded Successfully!\n");

    client_len = sizeof(client);

    /* Receiving Process */
    k = recvfrom(sock_desc, buffer, 100, 0, (struct sockaddr *)&client, &client_len);
    if (k < 0) {
        perror("Error In Receiving Data");
        close(sock_desc);
        return 1;
    }
    printf("Listening....\n");

    printf("Datagram From Client: %s\n", buffer);
    
    close(sock_desc);
    return 0;
}