#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid > 0) { // Parent process
        // Parent sorts using bubble sort
        printf("Parent process (PID: %d) sorting using Bubble Sort...\n", getpid());
        bubbleSort(arr, n);
        printf("Parent sorted array: ");
        printArray(arr, n);
        
        // Wait for child to prevent it from becoming a zombie
        wait(NULL);
    } else { // Child process
        // Child sorts using selection sort
        printf("Child process (PID: %d) sorting using Selection Sort...\n", getpid());
        selectionSort(arr, n);
        printf("Child sorted array: ");
        printArray(arr, n);
        
        // Simulate an orphan state by making parent terminate before child completes
        sleep(5); // Adjust the sleep to see orphan process in `ps` command
        printf("Child process (PID: %d) exiting.\n", getpid());
    }

    return 0;
}
