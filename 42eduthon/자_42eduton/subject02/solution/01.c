#include <stdio.h>
int n, m;
char board[101][101];
int dp[101][101];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int safe(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < m && board[x][y] == '1';
}

void sol(int cx, int cy) {
  for (int i = 0; i < 4; ++i) {
    int nx = cx + dx[i];
    int ny = cy + dy[i];
    if (safe(nx, ny) && (!dp[nx][ny] || dp[nx][ny] > dp[cx][cy] + 1)) {
      dp[nx][ny] = dp[cx][cy] + 1;
      sol(nx, ny);
    }
  }
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%s", board[i]);
  dp[0][0] = 1;
  sol(0, 0);

  printf("%d\n", dp[n - 1][m - 1]);
}