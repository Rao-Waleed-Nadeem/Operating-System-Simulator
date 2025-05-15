#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void move_file() {
char src[100], dst[100];
printf("📁 Enter source file name: ");
scanf("%s", src);
printf("📂 Enter destination file name: ");
scanf("%s", dst);

FILE *f1 = fopen(src, "r");
if (!f1) {
printf("❌ Cannot open source file!\n");
return;
}

FILE *f2 = fopen(dst, "w");
if (!f2) {
printf("❌ Cannot create destination file!\n");
fclose(f1);
return;
}

char c;
while ((c = fgetc(f1)) != EOF) {
fputc(c, f2);
}

fclose(f1);
fclose(f2);

if (remove(src) == 0) {
printf("✅ File moved successfully!\n");
} else {
printf("⚠️  Copied, but failed to delete original.\n");
}
}

int main() {
while (1) {
printf("\n[M] Minimize   [C] Close   [O] Move File\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);

if (ch == 'M' || ch == 'm') {
printf("🔄 Minimizing File Mover...\n");
raise(SIGTSTP);
} else if (ch == 'C' || ch == 'c') {
printf("🔴 Closing File Mover...\n");
exit(0);
} else if (ch == 'O' || ch == 'o') {
move_file();
} else {
printf("❌ Invalid choice.\n");
}
}

return 0;
}

