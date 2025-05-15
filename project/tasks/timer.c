#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void start_timer() {
int seconds;
printf("\n⏳=== Timer ===⏳\n");
printf("Enter number of seconds: ");
scanf("%d", &seconds);

printf("⏱️ Timer started for %d seconds...\n", seconds);
sleep(seconds);
printf("\n⏰ Time's up!\n");
}

int main() {
while (1) {
printf("\n[M] Minimize   [C] Close   [O] Start Timer\n");
printf("Enter choice: ");
char choice;
scanf(" %c", &choice);

if (choice == 'M' || choice == 'm') {
printf("🔄 Minimizing Timer...\n");
raise(SIGTSTP);
} else if (choice == 'C' || choice == 'c') {
printf("🔴 Closing Timer...\n");
exit(0);
} else if (choice == 'O' || choice == 'o') {
start_timer();
} else {
printf("❌ Invalid input. Try again.\n");
}
}

return 0;
}

