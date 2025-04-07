#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

#define PORT 3003
#define BUFF_SIZE 1024

int main() {
    int client_socket;
    int status;
    struct sockaddr_in server_addr;
    char buffer[BUFF_SIZE];

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        printf("Error in socket creation!\n");
        return 1;
    }
    printf("Socket created successfully!\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    while (1) {
        printf("\nEnter the data to be sent: ");
        fgets(buffer, sizeof(buffer), stdin);

        status = sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        if (status == -1) {
            printf("Error In Sending Message!\n");
            return 1;
        }
        printf("%s Sent Successfully!\n", buffer);

        socklen_t server_len = sizeof(server_addr);

        status = recvfrom(client_socket, buffer, BUFF_SIZE, 0, (struct sockaddr *)&server_addr, &server_len);
        if (status == -1) {
            printf("Error In Sending Message!\n");
            return 1;
        }

        printf("Time From Server: %s\n", buffer);
    }

    close(client_socket);

    return 0;
}