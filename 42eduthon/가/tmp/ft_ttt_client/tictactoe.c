#include <stdio.h>
#include <unistd.h>
#include <string.h>


int visited[3][3];
char board[3][3];

// default print
// void print_board(char board[][3])
// {
//     for (int i = 0; i < 3; ++i)
//     {
//         for (int j = 0; j < 3; ++j)
//         {
//             if (!board[i][j])
//                 printf("@");
//             else
//                 printf("%c", board[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }


const char * t1[] = 
{
    "\x1b[34m       000000       ",
    "\x1b[34m    000      000    ",
    "\x1b[34m  00            00  ",
    "\x1b[34m 00              00 ",
    "\x1b[34m00                00",
    "\x1b[34m0                  0",
    "\x1b[34m0                  0",
    "\x1b[34m00                00",
    "\x1b[34m 00              00 ",
    "\x1b[34m  00            00  ",
    "\x1b[34m    000      000    ",
    "\x1b[34m       000000       ",
};

const char * t2[] = 
{
    "\x1b[31m                    ",
    "\x1b[31m  0              0  ",
    "\x1b[31m    0          0    ",
    "\x1b[31m      0      0      ",
    "\x1b[31m        0  0        ",
    "\x1b[31m         00         ",
    "\x1b[31m         00         ",
    "\x1b[31m        0  0        ",
    "\x1b[31m      0      0      ",
    "\x1b[31m    0          0    ",
    "\x1b[31m  0              0  ",
    "\x1b[31m                    ",
};

const char * t3[] = 
{
    "                    ",
    "                    ",
    "                    ",
    "                    ",
    "                    ",
    "                    ",
    "                    ",
    "                    ",
    "                    ",
    "                    ",
    "                    ",
    "                    ",
};

const char * state[9][12] = 
{
    {
        "                    ",
        "                    ",
        "                    ",
        "      0       0     ",
        "     00      00     ",
        "      0       0     ",
        "      0       0     ",
        "      0       0     ",
        "      0       0     ",
        "     000 ,   000    ",
        "                    ",
        "                    ",
    },
    {
        "                    ",
        "                    ",
        "                    ",
        "      0      00     ",
        "     00     0  0    ",
        "      0        0    ",
        "      0       0     ",
        "      0      0      ",
        "      0     0       ",
        "     000 ,  0000    ",
        "                    ",
        "                    "
    },
    {
        "                    ",
        "                    ",
        "                    ",
        "      0      00     ",
        "     00     0  0    ",
        "      0        0    ",
        "      0      00     ",
        "      0        0    ",
        "      0     0  0    ",
        "     000  ,  00     ",
        "                    ",
        "                    "
    },
    {
        "                    ",
        "                    ",
        "                    ",
        "     00       0     ",
        "    0  0     00     ",
        "       0      0     ",
        "      0       0     ",
        "     0        0     ",
        "    0         0     ",
        "    0000 ,   000    ",
        "                    ",
        "                    "
    },
    {
        "                    ",
        "                    ",
        "                    ",
        "     00      00     ",
        "    0  0    0  0    ",
        "       0       0    ",
        "      0       0     ",
        "     0       0      ",
        "    0       0       ",
        "    0000 ,  0000    ",
        "                    ",
        "                    "
    },
    {
        "                    ",
        "                    ",
        "                    ",
        "     00      00     ",
        "    0  0    0  0    ",
        "       0       0    ",
        "      0      00     ",
        "     0         0    ",
        "    0       0  0    ",
        "    0000 ,   00     ",
        "                    ",
        "                    "
    },
    {
        "                    ",
        "                    ",
        "                    ",
        "     00       0     ",
        "    0  0     00     ",
        "       0      0     ",
        "     00       0     ",
        "       0      0     ",
        "    0  0      0     ",
        "     00  ,   000    ",
        "                    ",
        "                    "
    },
    {
        "                    ",
        "                    ",
        "                    ",
        "     00      00     ",
        "    0  0    0  0    ",
        "       0       0    ",
        "     00       0     ",
        "       0     0      ",
        "    0  0    0       ",
        "     00  ,  0000    ",
        "                    ",
        "                    "
    },
    {
        "                    ",
        "                    ",
        "                    ",
        "     00      00     ",
        "    0  0    0  0    ",
        "       0       0    ",
        "     00      00     ",
        "       0       0    ",
        "    0  0    0  0    ",
        "     00  ,   00     ",
        "                    ",
        "                    "
    }
};

enum type
{
    type1 = (int)'O',
    type2 = (int)'X'
};

enum state
{
    P1_WIN = 0,
    P2_WIN = 1,
    DRAW = 2,
    NOT_END = 3
};


void ft_print_first()
{
    for (int i = 0; i < 3; ++i)
    {
        
        printf("\x1b[0m -------------------- -------------------- --------------------\n");
        for (int y = 0 ; y < 12; ++y)
        {
            printf("\x1b[0m|");
            for (int x = 0 ; x < 3 ; ++x)
            {
                printf("%s", state[3 *i + x][y]);
                printf("\x1b[0m|");
            }
            printf("\n");
        }
    }
    printf("\x1b[0m -------------------- -------------------- --------------------\n");
}

void print_board(char board[][3])
{
    for (int i = 0; i < 3; ++i)
    {
        
        printf("\x1b[0m -------------------- -------------------- --------------------\n");
        for (int y = 0 ; y < 12; ++y)
        {
            printf("\x1b[0m|");
            for (int x = 0 ; x < 3 ; ++x)
            {
            if (board[i][x] == type1)
                printf("%s", t1[y]);
            else if (board[i][x] == type2)
                printf("%s", t2[y]);
            else
                printf("%s", state[3 * i + x][y]);
            printf("\x1b[0m|");
            }
            printf("\n");
        }
    }
    printf("\x1b[0m -------------------- -------------------- --------------------\n");
}

// upgrade print

// check board
int check_already_board(int visited[][3], int y, int x)
{
    if (visited[y - 1][x - 1])
        return (1);
    return (0);
}



const char * errorMessage[2] = {
    "not in range (1 ~ 3)\n",
    "already in board\n"
};

int dy[] = {0, 1, 1, 1};
int dx[] = {1, 1, 0, -1};

int check_range(int ny, int nx)
{
    if (ny < 0 || ny >= 3 || nx < 0 || nx >= 3)
        return (1);
    return (0);
}

int check_game_state(bool stone, int count)
{
    char now;
    stone == 0 ? now = type1 : now = type2;

    printf("now :%c\n", now);
    for (int i = 0 ; i < 3 ; ++i)
    {
        for (int j = 0 ; j < 3 ; ++j)
        {
            // cout << "here is now " << ' ' << i << ' ' << j  << '\n'; 
            if ((i == 0 || j == 0) && board[i][j] == now)
            {
                // cout << "in \n";
                int cnt = 1;
                for (int d = 0 ; d < 4 ; ++d)
                {
                    int ny = i + dy[d];
                    int nx = j + dx[d];
                    
                    // cout << ny << ' ' << nx << '\n';
                    if (check_range(ny, nx) || board[ny][nx] != now)
                        continue ;
                    ny += dy[d];
                    nx += dx[d];
                    if (check_range(ny, nx) || board[ny][nx] != now)
                        continue ;
                    // cout << ny << ' ' << nx << '\n';
                    if (board[ny][nx] != now)
                        continue;
                    else
                    {
                        if (!stone)
                            return P1_WIN;
                        else
                            return P2_WIN;
                    }
                }
            }
        }
    }
    if (count == 9)
        return DRAW;
    return NOT_END;
}

void input_coord(int *posy, int *posx)
{
    int y, x;
    scanf("%d %d", &y, &x);
    *posy = y;
    *posx = x;
}

const char * message1[3] = {
    "P1 Win\n",
    "P2 Win\n",
    "DRAW\n",
};

const char * message2[3] = {
    "P1 Lose\n",
    "P2 Lose\n",
    "DRAW\n",
};

int main()
{
    bool stone = 0;
    int count = 0;
    int flag;
    int y, x;

    ft_print_first();
    while (true)
    {
        // Input
        Input(&y, &x);
        
        // check valid Input
        if (check_range(y - 1, x - 1))
            printf("%s", errorMessage[0]);
        // Valid input case
        else
        {
            // Check if the stone already exists
            if (check_already_board(visited, y, x))
                printf("%s", errorMessage[1]);
            else
            {
                count++;
                stone == 0 ? board[y - 1][x - 1] = type1 : board[y - 1][x - 1] = type2;
                visited[y - 1][x - 1] = 1;
                print_board(board);

                // Check game state
                int ret = check_game_state(stone, count);
                printf("Game State is: %d\n", ret);
                if (ret !=  NOT_END)
                {
                    flag = ret;
                    break;
                }

                // turn change ex) O -> X -> O
                stone = !stone;
            }
        }
    }

    if (flag == P1_WIN)
        printf("%s",message1[flag]);
    else if (flag == P2_WIN)
        printf("%s",message1[flag]);
    else
        printf("%s",message1[flag]);
}