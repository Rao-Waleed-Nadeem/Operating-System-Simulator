#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void delete_file() {
char name[100];
printf("📁Enter file name: ");
scanf("%s", name);

if (remove(name) == 0)
printf("✅ File '%s' deleted.\n", name);
else
printf("❌ Failed to delete '%s'.\n", name);
}

int main() {
while (1) {
printf("\n[M] Minimize   [C] Close   [O] Delete File\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);

if (ch == 'M' || ch == 'm') {
printf("🔄 Minimizing File Deleter...\n");
raise(SIGTSTP);
} else if (ch == 'C' || ch == 'c') {
printf("🔴 Closing File Deleter...\n");
exit(0);
} else if (ch == 'O' || ch == 'o') {
delete_file();
} else {
printf("❌ Invalid choice.\n");
}
}

return 0;
}

