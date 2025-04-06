#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void main(){
    srand(time(NULL));

    printf("Enter The Total Number of Frames: ");
    int n;
    scanf("%d", &n);

    printf("Enter The Timer (in sec): ");
    int timer;
    scanf("%d", &timer);

    int i = 0;
    while(i < n){
        printf("Sending Packet %d to the Receiver\n", i);
        sleep(timer);

        int lost = rand() % n;
        if(i == lost){
            printf("Acknowledgement for Packet %d Has Not Been Received\n", i);
            sleep(1);
            printf("Retransmitting Packet %d Back to Receiver\n", i);
        }
        else{
            printf("Acknowledgement for Packet %d Has Been Received\n", i);
            i++;
        }
    }
}