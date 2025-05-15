#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

void show_time() {
time_t now = time(NULL);
struct tm* t = localtime(&now);
printf("🕒 Current Time: %02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);
}

int main() {
while (1) {
printf("\n[M] Minimize   [C] Close   [T] Show Time\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);

if (ch == 'M' || ch == 'm') {
printf("🔄 Minimizing Clock...\n");
raise(SIGTSTP);
} else if (ch == 'C' || ch == 'c') {
printf("🔴 Closing Clock...\n");
exit(0);
} else if (ch == 'T' || ch == 't') {
show_time();
} else {
printf("❌ Invalid choice.\n");
}
}

return 0;
}

