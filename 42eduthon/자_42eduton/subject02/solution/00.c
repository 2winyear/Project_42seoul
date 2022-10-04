#include <stdio.h>

char board[101][101];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int n;

int safe(int x, int y) { return x >= 0 && x < n && y >= 0 && y < n; }

void sol(int x, int y) {
  if (!safe(x, y) || board[x][y] == '0') return;
  board[x][y] = '0';
  for (int direction = 0; direction < 4; ++direction) {
    int next_x = x + dx[direction];
    int next_y = y + dy[direction];
    sol(next_x, next_y);
  }
}

int main() {
  int ans = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%s", board[i]);

  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      if (board[x][y] == '1') {
        sol(x, y);
        ans++;
      }
    }
  }

  printf("%d\n", ans);
}
