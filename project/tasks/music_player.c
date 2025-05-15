#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void beep(int count) {
for (int i = 0; i < count; i++) {
printf("\a");
fflush(stdout);
usleep(300000);
}
}

void play() {
printf("\n🎶=== Playing Music ===🎶\n");
for (int i = 0; i < 5; i++) {
printf("🎵 Playing track %d...\n", i + 1);
beep((i + 1) * 2);
sleep(1);
}
printf("🎶 Music finished. 🎶\n");
}

int main() {
while (1) {
printf("\n[M] Minimize   [C] Close   [P] Play Music\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);
if (ch == 'M' || ch == 'm') {
printf("🔄 Minimizing...\n");
raise(SIGTSTP);
} else if (ch == 'C' || ch == 'c') {
printf("🔴 Closing...\n");
exit(0);
} else if (ch == 'P' || ch == 'p') {
play();
} else {
printf("❌ Invalid choice.\n");
}
}
return 0;
}

