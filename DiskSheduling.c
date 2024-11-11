#include <stdio.h>
#include <stdlib.h>

// Simple Bubble Sort function
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function for Shortest Seek Time First (SSTF) algorithm
void SSTF(int req[], int n, int head) {
    int totalMovement = 0;
    int completed[n], nearest, minDist;

    for (int i = 0; i < n; i++) completed[i] = 0;

    for (int i = 0; i < n; i++) {
        minDist = 1e9;
        for (int j = 0; j < n; j++) {
            if (!completed[j] && abs(req[j] - head) < minDist) {
                minDist = abs(req[j] - head);
                nearest = j;
            }
        }
        totalMovement += minDist;
        head = req[nearest];
        completed[nearest] = 1;

        // Print the head movement
        printf("Head moved to: %d\n", head);
    }

    printf("Total Head Movement (SSTF): %d\n", totalMovement);
}

// Function for SCAN (elevator) algorithm
void SCAN(int req[], int n, int head, int diskSize) {
    int totalMovement = 0, i;

    // Sort the requests in ascending order for scanning
    bubbleSort(req, n);

    // Find the first request greater than or equal to head position
    for (i = 0; i < n && req[i] < head; i++);

    // Move towards the left (towards 0) first for all smaller requests
    for (int j = i - 1; j >= 0; j--) {
        totalMovement += abs(req[j] - head);
        head = req[j];
        
        // Print the head movement
        printf("Head moved to: %d\n", head);
    }

    // Move to the end of the disk
    totalMovement += abs(head - 0); // Move to 0
    head = 0;
    printf("Head moved to: %d\n", head);

    // Now move towards the right (diskSize-1), servicing remaining requests
    for (int j = i; j < n; j++) {
        totalMovement += abs(req[j] - head);
        head = req[j];
        
        // Print the head movement
        printf("Head moved to: %d\n", head);
    }

    printf("Total Head Movement (SCAN): %d\n", totalMovement);
}

// Function for C-LOOK algorithm
void CLOOK(int req[], int n, int head) {
    int totalMovement = 0, i;

    // Sort the requests in ascending order
    bubbleSort(req, n);

    // Find the first request greater than or equal to head position
    for (i = 0; i < n && req[i] < head; i++);

    // Move towards the end of disk, servicing requests
    for (int j = i; j < n; j++) {
        totalMovement += abs(req[j] - head);
        head = req[j];
        
        // Print the head movement
        printf("Head moved to: %d\n", head);
    }

    // Jump to the start of the disk requests and continue servicing
    for (int j = 0; j < i; j++) {
        totalMovement += abs(req[j] - head);
        head = req[j];
        
        // Print the head movement
        printf("Head moved to: %d\n", head);
    }

    printf("Total Head Movement (C-LOOK): %d\n", totalMovement);
}

int main() {
    int n, head, diskSize;

    // Input the number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int req[n];

    // Input the request queue
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    // Input the initial head position
    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Input the disk size
    printf("Enter disk size: ");
    scanf("%d", &diskSize);

    // Call SSTF, SCAN, and C-LOOK functions
    SSTF(req, n, head);
    
    SCAN(req, n, head, diskSize);
    
    CLOOK(req, n, head);

    return 0;
}
