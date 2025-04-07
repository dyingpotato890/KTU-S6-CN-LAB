#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>

#define PORT 3003
#define BUFF_SIZE 1024

int main() {
    int server_socket;
    int status;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFF_SIZE];

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        perror("Error in socket creation");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    status = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (status == -1) {
        perror("Error in binding");
        close(server_socket);
        return 1;
    }
    printf("Socket bound to port %d successfully!\n", PORT);

    while (1) {
        socklen_t client_len = sizeof(client_addr);

        status = recvfrom(server_socket, buffer, BUFF_SIZE, 0, (struct sockaddr *)&client_addr, &client_len);
        if (status == -1) {
            printf("Error In Sending Message!\n");
            return 1;
        }

        time_t current_time = time(NULL);
        char *time_str = ctime(&current_time);
        printf("Time On Server: %s", time_str);
        
        status = sendto(server_socket, time_str, strlen(time_str), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
        if (status == -1) {
            printf("Error In Sending Message!\n");
            return 1;
        }
    }

    close(server_socket);

    return 0;
}