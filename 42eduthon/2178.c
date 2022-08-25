#include <stdio.h>
#include <unistd.h>

char board[101][101];
int N, M;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int answer = 100 * 100;

int safeGuard(int x, int y) {
    if (x >= 0 && x < N && y >= 0 && y < M)
        return 1;
    return 0;
}

void sol(int x, int y, int depth)
{
    int newX, newY;
    int ret = 1;
    
    if (safeGuard(x,y) == 0 || board[x][y] != '1')
        return ;
    if (x == N - 1 && y == M - 1) {
        if (answer > depth)
            answer = depth;
        return ;
    }
    
    // puts("11");

    board[x][y] = '*';
    for (int k = 0; k < 4; k++) {
        newX = x + dx[k];
        newY = y + dy[k];

        sol(newX, newY, depth++);
    }
    board[x][y] = '1';
    return ;
}

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%s", board[i]);
    }
    puts("----------");
    sol(0, 0, 1);
    printf("%d\n", answer);

    return 0;
}