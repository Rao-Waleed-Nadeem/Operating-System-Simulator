#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void calc_ops() {
int a, b;
char op;

printf("\n🧮===== Calculator =====\n");
printf("Enter expression (e.g., 5 + 3): ");
if (scanf("%d %c %d", &a, &op, &b) != 3) {
printf("❌ Invalid input.\n");
while (getchar() != '\n');
return;
}

switch (op) {
case '+':
printf("✔ Result: %d\n", a + b);
break;
case '-':
printf("✔ Result: %d\n", a - b);
break;
case '*':
printf("✔ Result: %d\n", a * b);
break;
case '/':
if (b != 0)
printf("✔ Result: %d\n", a / b);
else
printf("❌ Division by zero!\n");
break;
default:
printf("❌ Invalid operator.\n");
}
}

int main() {
int ram = 100;
int hdd = 50;

fflush(stdout);

while (1) {
printf("\n[M] Minimize   [C] Close   [O] Operate\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);

if (ch == 'M' || ch == 'm') {
printf("🔄 Minimizing Calculator...\n");
raise(SIGTSTP);
} else if (ch == 'C' || ch == 'c') {
printf("🔴 Closing Calculator...\n");
exit(0);
} else if (ch == 'O' || ch == 'o') {
calc_ops();
} else {
printf("❌ Invalid choice.\n");
}
}

return 0;
}

