#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>

#define TASKS 18
#define MAX_PROCS 50
#define QSIZE MAX_PROCS
#define PRIORITY_LEVELS 2

int ram_total, hdd_total, cpu_cores;
int ram_used = 0, hdd_used = 0;
int kernel_mode = 0;
int show_context = 0;

sem_t resource_lock;

typedef struct {
    int pid;
    char name[50];
    int ram, hdd;
    int active;
    int kernel;
} Process;

Process process_table[MAX_PROCS];
int process_count = 0;

// List of task names shown in the OS menu
const char* task_names[TASKS] = {
    "Calculator", "Notepad", "Clock", "Calendar", "File Creator",
    "File Deleter", "File Copier", "File Mover", "File Info",
    "Game", "Music Player", "Timer", "Alarm", "Text Editor",
    "System Info", "Exit OS",
    "Guess Game", "Stopwatch"
};

// Paths to the executables for each task
const char* task_execs[TASKS] = {
    "./tasks/calculator", "./tasks/notepad", "./tasks/clock", "./tasks/calendar", "./tasks/file_creator",
    "./tasks/file_deleter", "./tasks/file_copier", "./tasks/file_mover", "./tasks/file_info",
    "./tasks/minesweeper", "./tasks/music_player", "./tasks/timer", "./tasks/alarm_clock",
    "./tasks/text_editor", "./tasks/system_info", NULL,
    "./tasks/guess_game", "./tasks/stopwatch"
};

// RAM requirements for each task
const int task_ram[TASKS] = {
    50, 40, 30, 35, 45,
    40, 60, 55, 50,
    70, 60, 30, 35,
    45, 30, 0,
    35, 30
};

// HDD requirements for each task
const int task_hdd[TASKS] = {
    10, 5, 5, 5, 10,
    10, 20, 15, 10,
    25, 20, 5, 5,
    10, 5, 0,
    5, 5
};

typedef struct {
    Process* queue[QSIZE];
    int front, rear;
} ReadyQueue;

ReadyQueue queues[PRIORITY_LEVELS];

/// Adds a process to the ready queue based on its priority level
void enqueue(int level, Process* proc) {
    if ((queues[level].rear + 1) % QSIZE == queues[level].front) return;
    queues[level].queue[queues[level].rear] = proc;
    queues[level].rear = (queues[level].rear + 1) % QSIZE;
}

/// Removes and returns the next process from the queue
Process* dequeue(int level) {
    if (queues[level].front == queues[level].rear) return NULL;
    Process* proc = queues[level].queue[queues[level].front];
    queues[level].front = (queues[level].front + 1) % QSIZE;
    return proc;
}

/// Tries to allocate RAM and HDD for a new process; returns 1 if successful
int allocate(int ram, int hdd) {
    sem_wait(&resource_lock);
    if (ram_used + ram <= ram_total && hdd_used + hdd <= hdd_total) {
        ram_used += ram;
        hdd_used += hdd;
        sem_post(&resource_lock);
        return 1;
    }
    sem_post(&resource_lock);
    printf("❌ Not enough resources. Available: %dMB RAM, %dGB HDD\n", ram_total - ram_used, hdd_total - hdd_used);
    return 0;
}

/// Releases the RAM and HDD used by a process when it ends
void release(int ram, int hdd) {
    sem_wait(&resource_lock);
    ram_used -= ram;
    hdd_used -= hdd;
    sem_post(&resource_lock);
}

/// Displays the main task selection menu
void show_menu() {
    printf("➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖\n");
    printf("\n📋 Available Tasks:\n");
    for (int i = 0; i < TASKS; i++) {
        printf("[%d] %s\n", i + 1, task_names[i]);
    }
    printf("[K] Switch Mode (%s)\n", kernel_mode ? "Kernel" : "User");
    printf("[C] Toggle Context View (%s)\n", show_context ? "ON" : "OFF");
    if (kernel_mode) printf("[D] Kill a Process\n");
    printf("[Q] Quit OS\n");
}

/// Continuously runs the scheduler to give CPU time to processes
void* scheduler(void* arg) {
    while (1) {
        Process* current = dequeue(0);  // Kernel queue
        if (!current) current = dequeue(1);  // User queue

        if (current && current->active) {
            if (show_context)
                printf("🔁 Switching to PID %d (%s)\n", current->pid, current->name);
            kill(current->pid, SIGCONT);
            sleep(2);
            kill(current->pid, SIGSTOP);
            if (show_context)
                printf("⏸️  Paused PID %d\n", current->pid);

            enqueue(current->kernel ? 0 : 1, current);
        } else {
            sleep(1);
        }
    }
    return NULL;
}

/// Monitors child processes and updates their status when they exit
void* monitor_processes(void* arg) {
    while (1) {
        int status;
        pid_t pid = waitpid(-1, &status, WNOHANG);
        if (pid > 0) {
            for (int i = 0; i < process_count; i++) {
                if (process_table[i].pid == pid && process_table[i].active) {
                    printf("❌ Process %d (%s) exited.\n", pid, process_table[i].name);
                    process_table[i].active = 0;
                    release(process_table[i].ram, process_table[i].hdd);
                    break;
                }
            }
        }
        usleep(500000);
    }
    return NULL;
}

/// Starts a new task by forking and launching it in an xterm window
void start_task(int index) {
    int ram = task_ram[index];
    int hdd = task_hdd[index];

    if (!allocate(ram, hdd)) return;

    pid_t pid = fork();
    if (pid == 0) {
        setpgid(0, 0);
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "xterm -e %s", task_execs[index]);
        kill(getpid(), SIGSTOP);
        execl("/bin/sh", "sh", "-c", cmd, NULL);
        perror("exec failed");
        exit(1);
    } else {
        Process p = {
            .pid = pid,
            .ram = ram,
            .hdd = hdd,
            .active = 1,
            .kernel = kernel_mode
        };
        strncpy(p.name, task_names[index], sizeof(p.name));
        process_table[process_count++] = p;
        printf("✅ Started [%s] in PID %d\n", p.name, pid);

        enqueue(kernel_mode ? 0 : 1, &process_table[process_count - 1]);
    }
}

/// Lets the user kill a process manually (only in kernel mode)
void kill_task() {
    if (!kernel_mode) {
        printf("❌ Only in Kernel Mode.\n");
        return;
    }

    printf("🛑 Running Processes:\n");
    for (int i = 0; i < process_count; i++) {
        if (process_table[i].active)
            printf("PID %d: %s\n", process_table[i].pid, process_table[i].name);
    }

    int pid;
    printf("Enter PID to kill: ");
    scanf("%d", &pid);

    for (int i = 0; i < process_count; i++) {
        if (process_table[i].pid == pid && process_table[i].active) {
            kill(-pid, SIGKILL);
            process_table[i].active = 0;
            release(process_table[i].ram, process_table[i].hdd);
            printf("🛑 Process %d (%s) killed.\n", pid, process_table[i].name);
            return;
        }
    }
    printf("❌ PID not found.\n");
}

/// The main function: sets up the OS, spawns the scheduler, and handles user interaction
int main() {
    printf("🛠 System Setup\n");
    do {
        printf("Enter RAM (512–4096 MB): ");
        scanf("%d", &ram_total);
    } while (ram_total < 512 || ram_total > 4096);

    do {
        printf("Enter HDD (10–100 GB): ");
        scanf("%d", &hdd_total);
    } while (hdd_total < 10 || hdd_total > 100);

    do {
        printf("Enter CPU Cores (1–4): ");
        scanf("%d", &cpu_cores);
    } while (cpu_cores < 1 || cpu_cores > 4);

    sem_init(&resource_lock, 0, 1);

    pthread_t sched, monitor;
    pthread_create(&sched, NULL, scheduler, NULL);
    pthread_create(&monitor, NULL, monitor_processes, NULL);

    printf("⭐⭐⭐⭐⭐ Welcome to MilkyWay OS ⭐⭐⭐⭐⭐\n\t\t⏳ Booting...\n");
    sleep(2);

    // Auto-start: Clock and Calendar
    start_task(2);
    start_task(3);

    while (1) {
        show_menu();
        printf("\nYour choice: ");
        char input[5];
        scanf("%s", input);

        if (!strcmp(input, "Q") || !strcmp(input, "q")) break;
        else if (!strcmp(input, "K") || !strcmp(input, "k")) {
            kernel_mode = !kernel_mode;
            printf("🔁 Mode: %s\n", kernel_mode ? "Kernel" : "User");
        } else if (!strcmp(input, "C") || !strcmp(input, "c")) {
            show_context = !show_context;
            printf("Context Switch: %s\n", show_context ? "ON" : "OFF");
        } else if (kernel_mode && (!strcmp(input, "D") || !strcmp(input, "d"))) {
            kill_task();
        } else {
            int task_index = atoi(input) - 1;
            if (task_index >= 0 && task_index < TASKS) {
                start_task(task_index);
            } else {
                printf("❌ Invalid option.\n");
            }
        }
    }

    printf("⭐⭐⭐⭐⭐ Goodbye! ⭐⭐⭐⭐⭐ \n");
    printf("🔴 Shutting down MilkyWay OS...\n");

    for (int i = 0; i < process_count; i++) {
        if (process_table[i].active) {
            kill(-process_table[i].pid, SIGKILL);
        }
    }

    sem_destroy(&resource_lock);
    return 0;
}

