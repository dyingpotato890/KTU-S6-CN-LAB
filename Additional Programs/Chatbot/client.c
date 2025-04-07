#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 3003
#define BUFF_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFF_SIZE];
    int status;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("Socket Creation Failed!\n");
        return 0;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    status = connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (status == -1) {
      printf("Connection Failed!\n");
      return 0;
    }
    printf("Connection Established!\n");

    while (1) {
        printf("\nFRIEND: ");
        status = recv(client_socket, buffer, BUFF_SIZE, 0);
        if (strcmp(buffer, "exit") == 0){
            break;
        }
        if (status == -1) {
            printf("Error in Receiving data!\n");
            return 1;
        }
        printf("%s", buffer);
        memset(buffer, 0, BUFF_SIZE);

        printf("\nYOU: ");
        fgets(buffer, BUFF_SIZE, stdin);
        status = send(client_socket, buffer, strlen(buffer), 0);
        if (status == -1) {
            printf("Error in Sending data!\n");
            return 1;
        }
        memset(buffer, 0, BUFF_SIZE);
    }

    close(client_socket);

    return 0;
}