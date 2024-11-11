#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrivalTime[n], burstTime[n], remainingTime[n];
    int completionTime[n], turnaroundTime[n], waitingTime[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrivalTime[i], &burstTime[i]);
        remainingTime[i] = burstTime[i];
    }

    int completed = 0, currentTime = 0, shortest = -1, minBurstTime = INT_MAX;
    int endTime, totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minBurstTime) {
                minBurstTime = remainingTime[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        remainingTime[shortest]--;
        minBurstTime = remainingTime[shortest];
        if (minBurstTime == 0) minBurstTime = INT_MAX;

        if (remainingTime[shortest] == 0) {
            completed++;
            endTime = currentTime + 1;
            completionTime[shortest] = endTime;
            turnaroundTime[shortest] = endTime - arrivalTime[shortest];
            waitingTime[shortest] = turnaroundTime[shortest] - burstTime[shortest];

            totalWaitingTime += waitingTime[shortest];
            totalTurnaroundTime += turnaroundTime[shortest];
        }

        currentTime++;
        shortest = -1;
        minBurstTime = INT_MAX;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }

    printf("\nAverage Turnaround Time = %.2f\n", (float)totalTurnaroundTime / n);
    printf("Average Waiting Time = %.2f\n", (float)totalWaitingTime / n);

    return 0;
}
