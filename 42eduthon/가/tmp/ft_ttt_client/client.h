/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 02:38:28 by mgo               #+#    #+#             */
/*   Updated: 2022/08/24 02:38:30 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define ERR_MSG_RANGE "not in range (1 ~ 3)\n"
#define ERR_MSG_ALRDY "already in board\n"

typedef int SOCKET;

typedef enum e_packet
{
    PACKET_MAX = 1024,
}           t_packet;

typedef struct s_server {
	char				ip[128];
	unsigned short		port;
	struct sockaddr_in	addr_in;
	SOCKET				sock;
	unsigned char	send_buf[PACKET_MAX];
	unsigned char	recv_buf[PACKET_MAX];
}				t_server;

enum e_turn {
	TURN_O,
	TURN_X,
};

typedef struct s_game {
	enum e_turn	turn;
	char		board[3][3];
	//int			visited[3][3];
	int			x;
	int			y;
}		t_game;

void	clean_infos(t_server *s_info, t_game *g_info);
void	config_network(t_server *s_info);


void	recv_packet(t_server *s_info);
bool	check_recved_proto(t_server *s_info, char *proto);
void	send_packet(t_server *s_info);
void	set_proto_in_send_buf(t_server *s_info, t_game *g_info);
void	clean_buf(unsigned char *buf);


void	print_board(char board[][3]);
void	input_coord(int *posy, int *posx);
int		check_range(int ny, int nx);


#endif
