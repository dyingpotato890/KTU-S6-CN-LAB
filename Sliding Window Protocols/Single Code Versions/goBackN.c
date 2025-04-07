#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
  srand(time(NULL));
  
  int windowSize, n, base = 0, timer;

  printf("Enter Total Number Of Frames: ");
  scanf("%d", &n);
  printf("Enter Timer (In Sec): ");
  scanf("%d", &timer);
  printf("Enter Window Size: ");
  scanf("%d", &windowSize);

  while (base < n) {
    printf("Sending packet %d to receiver\n", base);
    sleep(timer);

    if (rand() % 10 < 2) {
      printf("Acknowledgement of packet %d has not been received\n", base);
      sleep(1);

      for (int i = base + 1; i < base + windowSize && i < n; i++) {
        printf("Sending packet %d to receiver\n", i);
        printf("Packet %d has been dropped by receiver\n", i);
        sleep(1);
      }
    } else {
      printf("Acknowledgement for packed %d has been received\n", base);
      base++;
    }
  }

  return 0;
}