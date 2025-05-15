#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <signal.h>

void print_menu() {
printf("\n[M] Minimize   [C] Close   [D] Display System Info\n");
printf("Enter choice: ");
}

int main() {
struct utsname sys_info;

if (uname(&sys_info) < 0) {
perror("❌ Error fetching system information");
exit(EXIT_FAILURE);
}

while (1) {
print_menu();

char choice;
scanf(" %c", &choice);

if (choice == 'M' || choice == 'm') {
printf("🔄 Minimizing System Info Viewer...\n");
raise(SIGTSTP);
} else if (choice == 'C' || choice == 'c') {
printf("🔴 Closing System Info Viewer...\n");
exit(0);
} else if (choice == 'D' || choice == 'd') {
printf("\n💻=== System Information ===💻\n");
printf("🖥️ System Name: %s\n", sys_info.sysname);
printf("🌐 Node Name: %s\n", sys_info.nodename);
printf("🔧 Release: %s\n", sys_info.release);
printf("📝 Version: %s\n", sys_info.version);
printf("🔩 Machine: %s\n", sys_info.machine);
} else {
printf("❌ Invalid choice. Try again.\n");
}
}

return 0;
}

