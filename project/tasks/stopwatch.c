#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>

volatile bool running = false;
time_t start_time, elapsed_time = 0;

void print_elapsed() {
time_t now;
if (running) {
now = time(NULL);
printf("⏱️  Elapsed Time: %ld seconds\n", elapsed_time + (now - start_time));
} else {
printf("⏱️  Elapsed Time: %ld seconds\n", elapsed_time);
}
}

void handle_start() {
if (!running) {
start_time = time(NULL);
running = true;
printf("▶ Stopwatch started.\n");
} else {
printf("⚠ Stopwatch is already running.\n");
}
}

void handle_stop() {
if (running) {
elapsed_time += time(NULL) - start_time;
running = false;
printf("⏸ Stopwatch stopped.\n");
} else {
printf("⚠ Stopwatch is not running.\n");
}
}

void handle_reset() {
running = false;
elapsed_time = 0;
printf("🔄 Stopwatch reset.\n");
}

int main() {
fflush(stdout);

while (1) {
printf("\n[S] Start   [T] Stop   [R] Reset   [E] Elapsed   [C] Close\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);

switch (ch) {
case 'S':
case 's':
handle_start();
break;
case 'T':
case 't':
handle_stop();
break;
case 'R':
case 'r':
handle_reset();
break;
case 'E':
case 'e':
print_elapsed();
break;
case 'C':
case 'c':
printf("🔴 Closing Stopwatch...\n");
exit(0);
default:
printf("❌ Invalid choice.\n");
}
}

return 0;
}

