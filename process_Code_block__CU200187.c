#include <stdio.h>
#include <stdlib.h>

struct pcb {
    int pid;                // Process ID
    int arrival_time;       // Arrival Time
    int burst_time;         // Burst Time
    int priority;           // Priority of the process
    int completion_time;    // Completion Time
    int turnaround_time;    // Turnaround Time
    int waiting_time;       // Waiting Time
    int remaining_time;     // Remaining Time
};

int main() {
    int n, i, j, total_waiting_time = 0, total_turnaround_time = 0;
    float average_waiting_time, average_turnaround_time;
    struct pcb process[10], temp;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for(i=0; i<n; i++) {
        process[i].pid = i+1;
        printf("Enter the Arrival Time for process %d: ", process[i].pid);
        scanf("%d", &process[i].arrival_time);
        printf("Enter the Burst Time for process %d: ", process[i].pid);
        scanf("%d", &process[i].burst_time);
        printf("Enter the Priority for process %d: ", process[i].pid);
        scanf("%d", &process[i].priority);
        process[i].remaining_time = process[i].burst_time;
    }

    // Sort the processes based on arrival time
    for(i=0; i<n-1; i++) {
        for(j=i+1; j<n; j++) {
            if(process[i].arrival_time > process[j].arrival_time) {
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    int current_time = 0, completed_processes = 0;
    while(completed_processes < n) {
        int min_priority = 9999, index = -1;
        for(i=0; i<n; i++) {
            if(process[i].arrival_time <= current_time && process[i].priority < min_priority && process[i].remaining_time > 0) {
                min_priority = process[i].priority;
                index = i;
            }
        }

        if(index == -1) {
            current_time++;
        } else {
            process[index].remaining_time--;
            current_time++;

            if(process[index].remaining_time == 0) {
                process[index].completion_time = current_time;
                process[index].turnaround_time = process[index].completion_time - process[index].arrival_time;
                process[index].waiting_time = process[index].turnaround_time - process[index].burst_time;
                total_waiting_time += process[index].waiting_time;
                total_turnaround_time += process[index].turnaround_time;
                completed_processes++;
            }
        }
    }

    average_waiting_time = (float) total_waiting_time / n;
    average_turnaround_time = (float) total_turnaround_time / n;

    // Output process details
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for(i=0; i<n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n", process[i].pid, process[i].arrival_time, process[i].burst_time, process[i].priority, process[i].completion_time, process[i].turnaround_time, process[i].waiting_time);
    }
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
    return 0;
   
