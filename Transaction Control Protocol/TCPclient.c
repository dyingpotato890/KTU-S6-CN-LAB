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

int main() {
    char buffer[100];
    int status; // Error Flag
    int client_socket;
    struct sockaddr_in server_addr;

    /* Creating Socket */
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("Error in socket creation!\n");
        return 1;
    }
    printf("Socket created successfully!\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(3003); // Ensure correct byte order

    /* Connecting to the Server */
    status = connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (status == -1) {
        printf("Error in connecting to the server!\n");
        return 1;
    }
    printf("Connection successful!\n");

    /* Sending Data */
    printf("\nEnter the data to be sent: ");
    fgets(buffer, sizeof(buffer), stdin);

    status = send(client_socket, buffer, strlen(buffer), 0);
    if (status == -1) {
        printf("Error in sending data!\n");
        return 1;
    }
    printf("Message sent successfully!\n");

    /* Closing the Socket */
    close(client_socket);

    return 0;
}