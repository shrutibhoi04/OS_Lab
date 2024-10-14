#include <stdio.h>
#include <stdlib.h>

#define MAX_CYLINDERS 200

void sstf(int requests[], int n, int head) {
    int completed[MAX_CYLINDERS] = {0};
    int seek_count = 0;
    int current_position = head;
    int i,j;

    printf("SSTF Disk Scheduling:\n");
    for (i = 0; i < n; i++) {
        int min_distance = 9999;
        int index = -1;
        for ( j = 0; j < n; j++) {
            if (!completed[j]) {
                int distance = abs(requests[j] - current_position);
                if (distance < min_distance) {
                    min_distance = distance;
                    index = j;
                }
            }
        }
        completed[index] = 1;
        seek_count += min_distance;
        current_position = requests[index];

        printf("Head moved to: %d\n", current_position);
    }
    printf("Total seek time (SSTF): %d\n\n", seek_count);
}

int main() {
    int requests[] = { 98, 183, 37, 122, 14, 124, 65, 67 };
    int n = sizeof(requests) / sizeof(requests[0]);
    int initial_head = 50; 
    int total_cylinders = MAX_CYLINDERS; 
    sstf(requests, n, initial_head);
    return 0;
}
