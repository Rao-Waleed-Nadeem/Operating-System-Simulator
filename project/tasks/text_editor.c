#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MAX_TEXT_SIZE 1000

void print_menu() {
printf("\n[M] Minimize   [C] Close   [S] Save   [E] Edit Text\n");
printf("Enter choice: ");
}

int main() {
char filename[100];
char text[MAX_TEXT_SIZE];
FILE *fp;

printf("📝=== Text Editor ===📝\n");
printf("Enter filename to create or open: ");
scanf("%s", filename);

fp = fopen(filename, "a+");
if (fp == NULL) {
perror("❌ Error opening file");
exit(EXIT_FAILURE);
}

while (1) {
print_menu();

char choice;
scanf(" %c", &choice);

if (choice == 'M' || choice == 'm') {
printf("🔄 Minimizing Text Editor...\n");
raise(SIGTSTP);
} else if (choice == 'C' || choice == 'c') {
printf("🔴 Closing Text Editor...\n");
fclose(fp);
exit(0);
} else if (choice == 'S' || choice == 's') {
printf("💾 Saving the file...\n");
fclose(fp);
fp = fopen(filename, "a+");
if (fp == NULL) {
perror("❌ Error opening file");
exit(EXIT_FAILURE);
}
} else if (choice == 'E' || choice == 'e') {
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
} else {
printf("❌ Invalid choice. Try again.\n");
}
}

return 0;
}

