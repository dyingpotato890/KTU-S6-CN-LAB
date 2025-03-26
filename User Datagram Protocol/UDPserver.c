#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 3004  // Hardcoded port number

int main() {
    int server_socket;
    char buffer[100];
    socklen_t client_len;
    int status;
    struct sockaddr_in server_addr, client_addr;

    /* Creating Socket */
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        perror("Error in socket creation");
        return 1;
    }
    printf("Socket created successfully!\n");

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);  // Using hardcoded port

    /* Binding Process */
    status = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (status == -1) {
        perror("Error in binding");
        close(server_socket);
        return 1;
    }
    printf("Socket bound to port %d successfully!\n", PORT);

    client_len = sizeof(client_addr);

    /* Receiving Process */
    status = recvfrom(server_socket, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client_addr, &client_len);
    if (status < 0) {
        perror("Error in receiving data");
        close(server_socket);
        return 1;
    }

    printf("Received Message: %s\n", buffer);

    /* Closing the Socket */
    close(server_socket);

    return 0;
}