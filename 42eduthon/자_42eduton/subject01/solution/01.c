#include <stdio.h>
#include <unistd.h>

int n, m;
char ans[8];

void sol(int depth) {
  if (depth == m) {
    write(1, ans, m + 1);
    return;
  }

  for (int i = 1; i <= n; ++i) {
    ans[depth] = '0' + i;
    sol(depth + 1);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  ans[m] = '\n';
  sol(0);
}