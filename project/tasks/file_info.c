#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#define RAM 10
#define HDD 0

void info_file() {
char name[100];
printf("📄 Enter file name: ");
scanf("%s", name);

struct stat st;
if (stat(name, &st) < 0) {
perror("❌ Error");
return;
}

printf("\n🧾 File: '%s'\n", name);
printf("📦 Size: %ld bytes\n", st.st_size);
printf("🔐 Permissions: %o\n", st.st_mode & 0777);

char tbuf[80];
struct tm *t = localtime(&st.st_mtime);
strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", t);
printf("🕓 Last Modified: %s\n", tbuf);
}

int main() {
printf("%d %d\n", RAM, HDD);
fflush(stdout);

while (1) {
printf("\n[M] Minimize   [C] Close   [F] File Info\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);

if (ch == 'M' || ch == 'm') {
printf("🔄 Minimizing File Info...\n");
raise(SIGTSTP);
} else if (ch == 'C' || ch == 'c') {
printf("🔴 Closing File Info...\n");
exit(0);
} else if (ch == 'F' || ch == 'f') {
info_file();
} else {
printf("❌ Invalid choice.\n");
}
}

return 0;
}

