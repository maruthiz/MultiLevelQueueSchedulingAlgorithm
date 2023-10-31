#include <stdio.h>

// Define maximum number of processes
#define MAX_PROCESSES 100

// Define structure for a process
struct Process {
    int pid;
    int priority;
    int burst_time;
};

// Define structure for a Queue
struct Queue {
    struct Process processes[MAX_PROCESSES];
    int front;
    int rear;
    int count;
};

// Function to create a new Queue
void createQueue(struct Queue* queue, int capacity) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

// Function to check if a Queue is empty
int isEmpty(struct Queue* queue) {
	return queue->count == 0;
}

// Function to check if a Queue is full
int isFull(struct Queue* queue, int capacity) {
	return queue->count == capacity;
}

// Function to enqueue a process into a Queue
void enqueue(struct Queue* queue, struct Process process) {
    if (isFull(queue, MAX_PROCESSES)) {
        printf("Queue is full. Cannot enqueue process.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_PROCESSES;
    queue->processes[queue->rear] = process;
    queue->count++;
}

// Function to dequeue a process from a Queue
struct Process dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue process.\n");
        return (struct Process){-1, -1, -1};
    }
    struct Process process = queue->processes[queue->front];
    queue->front = (queue->front + 1) % MAX_PROCESSES;
    queue->count--;
    return process;
}

// Function to execute Round Robin scheduling algorithm
void roundRobin(struct Queue* queue, int quantum) {
    printf("Executing Round Robin scheduling algorithm...\n");
    int time_executed = 0;
    while (!isEmpty(queue)) {
        struct Process current_process = dequeue(queue);
        printf("Executing process %d for quantum time %d\n", current_process.pid, quantum);
        for (int i = 0; i < quantum && current_process.burst_time > 0; i++) {
            current_process.burst_time--;
            time_executed++;
        }
        if (current_process.burst_time > 0) {
            enqueue(queue, current_process);
        } else {
            printf("Process %d executed completely.\n", current_process.pid);
        }
    }
    printf("Total time executed: %d\n", time_executed);
}

// Function to execute Priority Scheduling algorithm
void priorityScheduling(struct Queue* queue) {
    printf("Executing Priority Scheduling algorithm...\n");
    int current_priority = -1;
    struct Process current_process = {0};
    while (!isEmpty(queue)) {
        if (current_process.pid == 0) {
            current_process = dequeue(queue);
            current_priority = current_process.priority;
            printf("Executing process %d\n", current_process.pid);
        } else {
            int next_priority = !isEmpty(queue) ? queue->processes[queue->front].priority : -1;
            if (current_priority != next_priority) {
                printf("Process %d executed completely.\n", current_process.pid);
                if (isEmpty(queue)) {
                    break;
                }
                current_process = dequeue(queue);
                current_priority = current_process.priority;
                printf("Executing process %d\n", current_process.pid);
            } else {
                struct Process next_process = dequeue(queue);
                printf("Executing process %d\n", next_process.pid);
            }
        }
    }
    if (current_process.pid != 0) {
        printf("Process %d executed completely.\n", current_process.pid);
    }
}



// Function to execute First Come First Serve algorithm
void firstComeFirstServe(struct Queue* queue) {
    printf("Executing First Come First Serve algorithm...\n");
    int time_executed = 0;
    while (!isEmpty(queue)) {
        struct Process current_process = dequeue(queue);
        printf("Executing process %d\n", current_process.pid);
        while (current_process.burst_time > 0) {
            current_process.burst_time--;
            time_executed++;
            if (current_process.burst_time == 0) {
                printf("Process %d executed completely.\n", current_process.pid);
                break;
            }
        }
    }
    printf("Total time executed: %d\n", time_executed);
}

// Main function to execute the program
int main() {
    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    struct Queue queue1, queue2, queue3;
    createQueue(&queue1, num_processes);
    createQueue(&queue2, num_processes);
    createQueue(&queue3, num_processes);
    for (int i = 0; i < num_processes; i++) {
        int pid, priority, burst_time;
        printf("Enter details of process %d:\n", i + 1);
        printf("PID: ");
        scanf("%d", &pid);
        printf("Priority: ");
        scanf("%d", &priority);
        printf("Burst Time: ");
        scanf("%d", &burst_time);
        struct Process new_process = {pid, priority, burst_time};
        if (priority >= 1 && priority <= 3) {
            enqueue(&queue1, new_process);
        } else if (priority >= 4 && priority <= 6) {
            enqueue(&queue2, new_process);
        } else {
            enqueue(&queue3, new_process);
        }
    }
    roundRobin(&queue1, 4);
    priorityScheduling(&queue2);
    firstComeFirstServe(&queue3);
    return 0;
}