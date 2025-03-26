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
    int status; /* Error Flag */
    socklen_t client_len;
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;

    /* Creating Socket */
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        printf("Error in socket creation!\n");
        return 1;
    }
    printf("Socket created successfully!\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(3003); // Ensure correct byte order

    /* Binding Process */
    status = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (status == -1) {
        printf("Error in binding!\n");
        return 1;
    }
    printf("Socket bound successfully!\n");

    /* Listening Process */
    status = listen(server_socket, 5);
    if (status == -1) {
        printf("Error in listening!\n");
        return 1;
    }
    printf("Server is listening for incoming connections...\n");

    client_len = sizeof(client_addr);

    /* Accepting Connection */
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket == -1) {
        printf("Error in accepting connection!\n");
        return 1;
    }
    printf("Client connected successfully!\n");

    /* Receiving Data */
    status = recv(client_socket, buffer, sizeof(buffer), 0);
    if (status == -1) {
        printf("Error in receiving data!\n");
        return 1;
    }
    
    buffer[status] = '\0'; // Null-terminate the received data
    printf("Message from Client: %s\n", buffer);

    /* Closing Sockets */
    close(client_socket);
    close(server_socket);

    return 0;
}