/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_session.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:18:50 by alee              #+#    #+#             */
/*   Updated: 2022/08/24 02:37:41 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_SESSION_H
# define CLIENT_SESSION_H

typedef int SOCKET;

typedef enum e_packet
{
    PACKET_MAX = 1024,
}           t_packet;

typedef struct s_client_session
{
	SOCKET				c_sock;
	struct sockaddr_in	c_addr_in;
	unsigned short		c_port;
    unsigned char       s_buf[PACKET_MAX];
    unsigned char       r_buf[PACKET_MAX];
    unsigned char       disconnect_flag;
}	t_client_session;

#endif