#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

struct node {
    int packet;
    struct node* next;
};

struct node* head = NULL;

void addNode(int packet) {
    struct node* temp = head;
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->packet = packet;

    if (head == NULL)
        head = newNode;
    else {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    newNode->next = NULL;
}

void main() {
    srand(time(NULL));

    printf("Enter Total Number Of Frames: ");
    int n;
    scanf("%d", &n);

    printf("Enter Timer (In Sec): ");
    int timer;
    scanf("%d", &timer);

    printf("Enter Window Size: ");
    int size;
    scanf("%d", &size);

    int i = 0;
    for (i = 0; i < size; i++)
        addNode(i);

    while (head != NULL) {
        printf("Sending Packet %d To Receiver\n", head->packet);
        sleep(timer);

        int lost = rand() % n;
        if (lost == head->packet) {
            printf("Acknowledgement For Packet %d Has Not Been Received\n", head->packet);
            sleep(1);

            struct node* temp = head->next;
            while (temp != NULL) {
                printf("Sending Packet %d To Receiver\n", temp->packet);
                sleep(1);
                printf("Packet %d Has Been Discarded By The Receiver\n", temp->packet);
                temp = temp->next;
            }
            printf("Retransmitting Packet %d Back To Receiver\n", head->packet);
        } else {
            printf("Acknowledgement For Packet %d Has Been Received\n", head->packet);

            struct node* temp = head;
            head = head->next;
            if (i < n) {
                addNode(i);
                i++;
            }
            free(temp);
        }
    }
}