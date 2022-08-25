/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:18:21 by alee              #+#    #+#             */
/*   Updated: 2022/08/24 04:20:01 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# define CLIENT_MAX 2
# include <netinet/in.h>
# include "client_session.h"

typedef int SOCKET;

typedef enum e_status
{
	START = 0,
	PLAY,
	END,
}			t_status;

typedef struct s_server
{
	//server data
	char				s_ip[128];
	unsigned short		s_port;
	SOCKET				s_listen_sock;
	struct sockaddr_in	s_addr_in;
	t_status			s_status;

    //client data
	t_client_session	c_session[CLIENT_MAX];
    int                 current_client;
}		t_server;

void	accept_client(t_server *p_server);
void	ft_network(t_server *p_server);
SOCKET	getMaxFD(t_server *p_server);
void	recvPacket(SOCKET c_sock, int sock_idx, t_server *p_server);
void	sendPacket(SOCKET c_sock, int sock_idx, t_server *p_server);
void	ft_tictactoe(t_server *p_server);
void	ft_disconnect(t_server *p_server);
void	disconnect(SOCKET c_sock, int sock_idx, t_server *p_server);

void	insertPacket(unsigned char *buf, const char *packet_type);
void	buildPacket(const char *packet_type, int sock_idx, t_server *p_server);
void	broadcast(t_server *p_server);

#endif