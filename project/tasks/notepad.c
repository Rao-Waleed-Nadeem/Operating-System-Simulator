#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void run_notepad() {
char filename[100], text[1000];
FILE *fp;

printf("📝=== Notepad ===📝\n");
printf("Enter filename to create: ");
scanf("%s", filename);

fp = fopen(filename, "w");
if (fp == NULL) {
perror("❌ Error creating file");
return;
}

printf("Start typing your text (end with '~' on a new line):\n");
getchar();

while (1) {
fgets(text, sizeof(text), stdin);
if (text[0] == '~') {
break;
}
fprintf(fp, "%s", text);
fflush(fp);
}

fclose(fp);
printf("✅ File '%s' saved successfully.\n", filename);
}

int main() {
while (1) {
printf("\n[M] Minimize   [C] Close   [O] Open Notepad\n");
printf("Enter choice: ");
char choice;
scanf(" %c", &choice);

if (choice == 'M' || choice == 'm') {
printf("🔄 Minimizing Notepad...\n");
raise(SIGTSTP);
} else if (choice == 'C' || choice == 'c') {
printf("🔴 Closing Notepad...\n");
exit(0);
} else if (choice == 'O' || choice == 'o') {
run_notepad();
} else {
printf("❌ Invalid input. Try again.\n");
}
}

return 0;
}

