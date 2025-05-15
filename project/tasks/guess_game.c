#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

void play_game() {
int number, guess, attempts = 0;
srand(time(NULL));
number = rand() % 10 + 1;

printf("\n🎯===== Guessing Game =====\n");
printf("Guess the number (1–10):\n");

while (1) {
printf("Enter guess: ");
if (scanf("%d", &guess) != 1) {
printf("❌ Invalid input.\n");
while (getchar() != '\n');
continue;
}

attempts++;
if (guess < number) {
printf("📉 Too low!\n");
} else if (guess > number) {
printf("📈 Too high!\n");
} else {
printf("🎉 Correct! It took you %d tries.\n", attempts);
break;
}
}
}

int main() {
int ram = 50;
int hdd = 20;

fflush(stdout);

while (1) {
printf("\n[M] Minimize   [C] Close   [O] Operate\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);

if (ch == 'M' || ch == 'm') {
printf("🔄 Minimizing Guessing Game...\n");
raise(SIGTSTP);
} else if (ch == 'C' || ch == 'c') {
printf("🔴 Closing Guessing Game...\n");
exit(0);
} else if (ch == 'O' || ch == 'o') {
play_game();
} else {
printf("❌ Invalid choice.\n");
}
}

return 0;
}

