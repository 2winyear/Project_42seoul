/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 04:16:46 by mgo               #+#    #+#             */
/*   Updated: 2022/08/24 10:10:33 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "packet_protocol.h"

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

/*
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
*/

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
            if (board[i][x] == 'O')
                printf("%s", t1[y]);
            else if (board[i][x] == 'X')
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

void	draw_map(t_server *s_info, t_game *g_info)
{
	// recv_buf to coord
	//get_coord_from_recv_buf(s_info, g_info);
	//set_coord_in_board(g_info);
	//print_board(g_info->board);
}

void	process_input(t_server *s_info, t_game *g_info)
{
	// input coord and draw map
	printf("Input coordinate to put -> ");
	input_coord(&(g_info->y), &(g_info->x));
	if (check_range(g_info->y, g_info->x)) {
		printf("%s", ERR_MSG_RANGE);
	}
	set_proto_in_send_buf(s_info, g_info);
	send_packet(s_info);
	recv_packet(s_info);

	// check recv_packet
	//draw_map()
	draw_map(s_info, g_info);
}

void	process_wait(t_server *s_info, t_game *g_info)
{
	// wait opponent and draw map
	printf("Waiting for opponent...\n");
	recv_packet(s_info);
	//draw_map();
	draw_map(s_info, g_info);
}

void	run_ttt(t_server *s_info, t_game *g_info) {
	while (1)
	{
		if (g_info->turn == TURN_O)
		{
			process_input(s_info, g_info);
			process_wait(s_info, g_info);
		}
		else if (g_info->turn == TURN_X)
		{
			process_wait(s_info, g_info);
			process_input(s_info, g_info);
		}
		else
		{
			printf("unknown turn type...\n");
			exit(1);
		}
	}
}

void	init_game(t_server *s_info, t_game *g_info) {
	// start protocol
	recv_packet(s_info);
	printf("recv_buf: [%s]\n", s_info->recv_buf);
	if (check_recved_proto(s_info, PROTO_START) == true)
	{
		printf("game start!\n");
		ft_print_board(g_info->board);
	}
	else
	{
		printf("no start protocol in buffer...\n");
	}
	// turn protocol
	//clean_buf(s_info->recv_buf);
	if (strlen((char *)(s_info->recv_buf)) == 0)
		recv_packet(s_info);
	if (check_recved_proto(s_info, PROTO_O) == true)
	{
		g_info->turn = TURN_O;
		printf("turn: [O]\n");
	}
	else if (check_recved_proto(s_info, PROTO_X) == true)
	{
		g_info->turn = TURN_X;
		printf("turn: [X]\n");
	}
}

int	main(void)
{
	t_server	s_info;
	t_game		g_info;

	config_network(&s_info);
	init_game(&s_info, &g_info);
	run_ttt(&s_info, &g_info);
	// close
	return (0);
}
