#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 3003
#define BUFF_SIZE 1024

int main() {
    int client_socket, server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFF_SIZE];
    int status;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        printf("Socket Creation Failed!\n");
        return 0;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    status = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (status == -1) {
        printf("Binding Failed!\n");
        return 0;
    }

    status = listen(server_socket, 5);
    if (status == -1) {
        printf("Listening Failed!\n");
        return 0;
    }

    client_len = sizeof(client_addr);

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket == -1) {
        printf("Client Socket Failed!\n");
        return 0;
    }
    printf("Connection Established!\n");

    while (1) {
        printf("\nYOU: ");
        fgets(buffer, BUFF_SIZE, stdin);

        status = send(client_socket, buffer, strlen(buffer), 0);
        if (status == -1) {
            printf("Error in Sending data!\n");
            return 1;
        }
        memset(buffer, 0, BUFF_SIZE);

        printf("\nFRIEND: ");

        status = recv(client_socket, buffer, BUFF_SIZE, 0);
        if (status == -1) {
            printf("Error in Receiving data!\n");
            return 1;
        }
        printf("%s", buffer);
        memset(buffer, 0, BUFF_SIZE);
    }

    close(client_socket);
    close(server_socket);

    return 0;
}