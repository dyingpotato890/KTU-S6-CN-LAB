#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int n, timer, windowSize;
    printf("Enter total number of frames: ");
    scanf("%d", &n);

    printf("Enter timer (seconds): ");
    scanf("%d", &timer);

    printf("Enter window size: ");
    scanf("%d", &windowSize);

    int packets[n];
    int retransmit[n]; // Flags to mark packets for retransmission
    int ack[n];

    for (int i = 0; i < n; i++) {
        packets[i] = i;
        retransmit[i] = 0;
        ack[i] = 0;
    }

    int base = 0;

    while (base < n) {
        printf("\n=== Sending Window From Packet %d to Packet %d ===\n", base, base + windowSize - 1);

        // Send packets in window
        for (int i = base; i < base + windowSize && i < n; i++) {
            if (ack[i] == 0) {
                printf("Sending Packet %d to Receiver\n", packets[i]);
                sleep(timer);

                // Simulate packet loss
                int lost = rand() % n;
                if (lost == packets[i]) {
                    printf("Acknowledgement for Packet %d NOT Received. Will Retransmit.\n", packets[i]);
                    retransmit[i] = 1;
                } else {
                    printf("Acknowledgement for Packet %d Received.\n", packets[i]);
                    ack[i] = 1;
                }
            }
        }

        // Retransmit if necessary
        for (int i = base; i < base + windowSize && i < n; i++) {
            if (retransmit[i] == 1) {
                printf("Retransmitting Packet %d\n", packets[i]);
                sleep(timer);

                // Simulate second attempt (assume success)
                printf("Acknowledgement for Packet %d Received After Retransmission.\n", packets[i]);
                ack[i] = 1;
                retransmit[i] = 0;
            }
        }

        // Slide window forward
        while (ack[base] == 1 && base < n) {
            base++;
        }
    }

    printf("\nAll Packets Sent and Acknowledged Successfully.\n");
    return 0;
}