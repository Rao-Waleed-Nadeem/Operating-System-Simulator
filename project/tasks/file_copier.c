#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void copy_file() {
char src[100], dest[100];

printf("📂 Enter source file: ");
scanf("%s", src);
printf("📁 Enter destination file: ");
scanf("%s", dest);

FILE* f1 = fopen(src, "r");
if (!f1) {
printf("❌ Cannot open source file.\n");
return;
}

FILE* f2 = fopen(dest, "w");
if (!f2) {
printf("❌ Cannot create destination file.\n");
fclose(f1);
return;
}

char ch;
while ((ch = fgetc(f1)) != EOF)
fputc(ch, f2);

fclose(f1);
fclose(f2);

printf("✅ File copied successfully!\n");
}

int main() {
while (1) {
printf("\n[M] Minimize   [C] Close   [O] Copy File\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);

if (ch == 'M' || ch == 'm') {
printf("🔄 Minimizing File Copier...\n");
raise(SIGTSTP);
} else if (ch == 'C' || ch == 'c') {
printf("🔴 Closing File Copier...\n");
exit(0);
} else if (ch == 'O' || ch == 'o') {
copy_file();
} else {
printf("❌ Invalid choice.\n");
}
}

return 0;
}

