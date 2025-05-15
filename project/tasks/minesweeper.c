#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define SIZE 5
#define BOMBS 5

char board[SIZE][SIZE];
int revealed[SIZE][SIZE];

void initialize_board() {
for (int i = 0; i < SIZE; i++) {
for (int j = 0; j < SIZE; j++) {
board[i][j] = '0';
revealed[i][j] = 0;
}
}

int bombs_placed = 0;
while (bombs_placed < BOMBS) {
int x = rand() % SIZE;
int y = rand() % SIZE;
if (board[x][y] != '*') {
board[x][y] = '*';
bombs_placed++;
}
}

for (int i = 0; i < SIZE; i++) {
for (int j = 0; j < SIZE; j++) {
if (board[i][j] == '*') continue;
int count = 0;
for (int dx = -1; dx <= 1; dx++) {
for (int dy = -1; dy <= 1; dy++) {
int nx = i + dx;
int ny = j + dy;
if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == '*') {
count++;
}
}
}
board[i][j] = '0' + count;
}
}
}

void print_board() {
printf("\n     ");
for (int i = 0; i < SIZE; i++) {
printf("%2d ", i);
}
printf("\n    ");
for (int i = 0; i < SIZE; i++) {
printf("---");
}
printf("\n");

for (int i = 0; i < SIZE; i++) {
printf("%2d | ", i);
for (int j = 0; j < SIZE; j++) {
if (revealed[i][j]) {
if (board[i][j] == '*') {
printf("\033[1;31m*\033[0m  "); // Red bomb
} else if (board[i][j] == '0') {
printf("   "); // Empty space for 0
} else {
printf("\033[1;32m%c\033[0m  ", board[i][j]); // Green numbers
}
} else {
printf(".  ");
}
}
printf("\n");
}
}

void play_minesweeper() {
initialize_board();

int moves = 0;
int total_safe = SIZE * SIZE - BOMBS;

while (1) {
print_board();
int x, y;
printf("\n🔍 Enter coordinates to reveal (row col): ");
scanf("%d %d", &x, &y);

if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
printf("❌ Invalid coordinates! Try again.\n");
continue;
}

if (revealed[x][y]) {
printf("❗ Already revealed! Pick another.\n");
continue;
}

revealed[x][y] = 1;

if (board[x][y] == '*') {
printf("\n💥 Boom! You hit a bomb! Game over. 😞\n");
print_board();
break;
}

moves++;

if (moves == total_safe) {
printf("\n🎉 Congratulations! You cleared all safe spots! 😄\n");
print_board();
break;
}
}
}

int main() {
srand(time(NULL)); // Randomize bomb placement

while (1) {
printf("\n[M] Minimize   [C] Close   [O] Play Minesweeper\n");
printf("Enter choice (M/C/O): ");
char choice;
scanf(" %c", &choice);

if (choice == 'M' || choice == 'm') {
printf("🔄 Minimizing Minesweeper...\n");
raise(SIGTSTP); // Suspend process
} else if (choice == 'C' || choice == 'c') {
printf("🔴 Closing Minesweeper...\n");
exit(0);
} else if (choice == 'O' || choice == 'o') {
play_minesweeper();
} else {
printf("❌ Invalid choice. Try again.\n");
}
}

return 0;
}

