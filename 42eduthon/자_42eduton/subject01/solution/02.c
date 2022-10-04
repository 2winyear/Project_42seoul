#include <stdio.h>
#include <unistd.h>

int n, m;
char ans[8];
void sol(int depth, int idx) {
  if (depth == m) {
    write(1, ans, m + 1);
    return;
  }

  for (int i = idx; i <= n; ++i) {
    ans[depth] = '0' + i;
    sol(depth + 1, i + 1);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  ans[m] = '\n';
  sol(0, 1);
}