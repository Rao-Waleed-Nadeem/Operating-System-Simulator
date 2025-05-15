#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

void beep(int n) {
for (int i = 0; i < n; i++) {
printf("\a");
fflush(stdout);
usleep(300000);
}
}

void alarm_on() {
for (int i = 0; i < 5; i++) {
beep(i);
sleep(1);
}
}

int main() {
int h, m, s;
printf("\n⏰===== Alarm Clock =====\n");
printf("Set alarm time (HH MM SS): ");
scanf("%d %d %d", &h, &m, &s);

while (1) {
printf("\n[M] Minimize   [C] Close   [A] Activate Alarm\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);

if (ch == 'M' || ch == 'm') {
printf("🔄 Minimizing Alarm...\n");
raise(SIGTSTP);
} else if (ch == 'C' || ch == 'c') {
printf("🔴 Closing Alarm...\n");
exit(0);
} else if (ch == 'A' || ch == 'a') {
while (1) {
time_t now = time(NULL);
struct tm* t = localtime(&now);

if (t->tm_hour == h && t->tm_min == m && t->tm_sec == s) {
printf("\n⏰ Alarm! Time's up!\n");
alarm_on();
break;
}

printf("\r🕒 Current time: %02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
fflush(stdout);
sleep(1);
}
printf("\n✅ Alarm finished.\n");
break;
} else {
printf("❌ Invalid choice.\n");
}
}

return 0;
}

