#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void make_file() {
char name[100];
printf("📄 Enter file name: ");
scanf("%s", name);

FILE* f = fopen(name, "w");
if (!f) {
printf("❌ Failed to create file.\n");
return;
}

printf("✅ File '%s' created.\n", name);
fclose(f);
}

int main() {
while (1) {
printf("\n[M] Minimize   [C] Close   [O] Create File\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);

if (ch == 'M' || ch == 'm') {
printf("🔄 Minimizing File Creator...\n");
raise(SIGTSTP);
} else if (ch == 'C' || ch == 'c') {
printf("🔴 Closing File Creator...\n");
exit(0);
} else if (ch == 'O' || ch == 'o') {
make_file();
} else {
printf("❌ Invalid choice.\n");
}
}

return 0;
}

