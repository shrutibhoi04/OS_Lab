Parent.c (main program)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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

int main(int argc, char *argv[]) {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array
    bubbleSort(arr, n);
    printf("Parent process (PID: %d) sorted array: ", getpid());
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Fork to create a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) { // Child process
        printf("Child process (PID: %d) created by parent (PID: %d)\n", getpid(), getppid());

        // Prepare arguments for execve
        char *args[n + 2]; // +2 for program name and NULL terminator
        args[0] = "./child_program"; // Child program to execute

        // Convert sorted array elements to strings and add to args
        for (int i = 0; i < n; i++) {
            char *num_str = malloc(10); // Allocate space for number as string
            sprintf(num_str, "%d", arr[i]);
            args[i + 1] = num_str;
        }
        args[n + 1] = NULL; // Null terminate the args array

        // Execute child program with execve
        if (execve(args[0], args, NULL) == -1) {
            perror("execve failed");
            exit(1);
        }
    } else { // Parent process
        wait(NULL); // Wait for child process to finish
        printf("Parent process (PID: %d) finished waiting for child.\n", getpid());
    }

    return 0;
}


child.c

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Child process (PID: %d) received array in reverse order: ", getpid());
    for (int i = argc - 1; i > 0; i--) { // Start from argc - 1 to skip the program name
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}

//gcc main_program.c -o main_program
//gcc child_program.c -o child_program
//./main_program
