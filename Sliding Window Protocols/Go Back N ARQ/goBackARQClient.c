#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void main(){
    int cli_sock, i, j, flag = 1, note = 1;
    char msg1[50] = "ACK", write_buff[50], read_buff[100];

    struct sockaddr_in client;
    cli_sock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&client, 0, sizeof(client));

    client.sin_family = AF_INET;
    client.sin_port = htons(7004);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(cli_sock, (struct sockaddr *)&client, sizeof(client)) == -1) {
        printf("Connection failed");
        exit(0);
    }

    printf("\nReceiver of Go Back N where N = 8\n\n");
    for (i = 0; i < 8; i++) {
        memset(&read_buff, 0, sizeof(read_buff));
        memset(&write_buff, 0, sizeof(write_buff));

        if (i == 5 && flag == 1) {
            flag = 0;
            read(cli_sock, read_buff, sizeof(read_buff));
        }

        read(cli_sock, read_buff, sizeof(read_buff));
        if (read_buff[strlen(read_buff) - 1] != i + '0') {
            printf("\n --- Packet from Sender %d Lost - %d Received Out of Order - Discarding ---\n", i, i + 1);
            i--;
        } else {
            if (i == 0) {
                printf("-> %s\n", read_buff);
                read(cli_sock, read_buff, sizeof(read_buff));
                i++;
            }

            printf("-> %s\n", read_buff);
            if ((i == 5) || (i == 3)) {
                read(cli_sock, read_buff, sizeof(read_buff));
                printf("-> %s\n", read_buff);
                i++;
            }
            if (i == 7)
                j = 0;
            else
                j = i + 1;
                
            if ((i == 6) || (i == 4) || (i == 1))
                printf("<- ACK %d - Cumulative Acknowledgement\n", j);
            else
                printf("<- ACK %d - Individual Acknowledgement\n", j);
            printf("-----------------------------------------------------\n");
            strcpy(write_buff, msg1);
            write_buff[strlen(msg1)] = j + '0';
            write(cli_sock, write_buff, sizeof(write_buff));
        }
    }
    close(cli_sock);
}