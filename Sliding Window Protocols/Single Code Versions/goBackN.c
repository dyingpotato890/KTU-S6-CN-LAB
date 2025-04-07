#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_PACKETS 100

int main() {
    srand(time(NULL));

    int total_packets, timer, window_size;
    printf("Enter Total Number Of Frames: ");
    scanf("%d", &total_packets);
    printf("Enter Timer (In Sec): ");
    scanf("%d", &timer);
    printf("Enter Window Size: ");
    scanf("%d", &window_size);

    int base = 0; // First unacknowledged packet
    int next_seq = 0; // Next packet to send

    while (base < total_packets) {
        while (next_seq < base + window_size && next_seq < total_packets) {
            printf("Sending Packet %d To Receiver\n", next_seq);
            sleep(timer);
            next_seq++;
        }

        int lost = (rand() % 10) < 3;
        if (lost) {
            printf("ACK for Packet %d Not Received! Retransmitting...\n", base);
            next_seq = base; // Reset next_seq to retransmit from base
        } else {
            printf("ACK for Packet %d Received. Window Advanced.\n", base);
            base++;
        }
    }

    printf("All Packets Transmitted Successfully!\n");
    return 0;
}