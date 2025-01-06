/*
Compile using: gcc TCPserver.c -o server
./server
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char buffer[100];
    int k; /*Error Flag*/
    socklen_t len;
    int sock_desc, temp_sock_desc;
    struct sockaddr_in server, client;

    /*Creating Socket*/
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) {
        printf("Error In Socket Creation!");
        return 1;
    }
    printf("Socket Created Successfully!\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3003;

    /*Binding Process*/
    k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1) {
        printf("Error In Binding!");
        return 1;
    }
    printf("Socket Binded Successfully!\n");

    /*Listening Process*/
    k = listen(sock_desc, 5);
    if (k == -1) {
        printf("Error In Listening!");
        return 1;
    }

    len = sizeof(client);

    /*Accepting Process*/
    temp_sock_desc = accept(sock_desc, (struct sockaddr *)&client, &len);
    if (temp_sock_desc == -1) {
        printf("Error In Temporary Socket Creation!");
        return 1;
    }
    printf("Acceptance Successfully!\n");

    /*Receiving Process*/
    k = recv(temp_sock_desc, buffer, 100, 0);
    if (k == -1) {
        printf("Error In Receiving Data!");
        return 1;
    }
    printf("Listening....\n");

    printf("Message From Client: %s\n", buffer);

    close(temp_sock_desc);
    close(sock_desc);

    return 0;
}