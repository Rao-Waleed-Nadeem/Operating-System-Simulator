#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define WHITE   "\033[0;37m"
#define RESET   "\033[0m"

int days_in_month(int m, int y) {
if (m == 2) {
if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
return 29;
else
return 28;
}
if (m == 4 || m == 6 || m == 9 || m == 11)
return 30;
return 31;
}

void show_calendar(int m, int y) {
const char* names[] = {
"", "January", "February", "March", "April", "May", "June",
"July", "August", "September", "October", "November", "December"
};

printf("\n📅===== %s %d =====\n", names[m], y);
printf("Sun Mon Tue Wed Thu Fri Sat\n");

struct tm t = {0};
t.tm_mday = 1;
t.tm_mon = m - 1;
t.tm_year = y - 1900;
mktime(&t);

int start = t.tm_wday;
int days = days_in_month(m, y);

for (int i = 0; i < start; i++)
printf("    ");

for (int d = 1; d <= days; d++) {
int wd = (start + d - 1) % 7;
if (wd == 0)
printf(RED);
else if (wd == 6)
printf(BLUE);
else
printf(WHITE);

printf("%3d ", d);

if ((d + start) % 7 == 0)
printf(RESET "\n");
}

printf(RESET "\n");
}

int main() {
while (1) {
printf("\n[C] Current Month   [S] Select Date   [M] Minimize   [X] Exit\n");
printf("Enter choice: ");
char ch;
scanf(" %c", &ch);

if (ch == 'C' || ch == 'c') {
time_t now = time(NULL);
struct tm* t = localtime(&now);
show_calendar(t->tm_mon + 1, t->tm_year + 1900);
} else if (ch == 'S' || ch == 's') {
int m, y;
printf("Month (1-12): ");
scanf("%d", &m);
printf("Year: ");
scanf("%d", &y);
if (m >= 1 && m <= 12 && y >= 1900)
show_calendar(m, y);
else
printf("❌ Invalid input.\n");
} else if (ch == 'M' || ch == 'm') {
printf("🔄 Minimizing Calendar...\n");
raise(SIGTSTP);
} else if (ch == 'X' || ch == 'x') {
printf("🔴 Closing Calendar...\n");
exit(0);
} else {
printf("❌ Invalid choice.\n");
}
}

return 0;
}

