/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:48:47 by alee              #+#    #+#             */
/*   Updated: 2022/08/24 15:38:20 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"
#include "client_session.h"
#include <stdlib.h>
#include <fcntl.h>

int	main(void)
{
	t_server	server;	//서버에서 관리하는 구조체, 소켓 통신, 클라이언트의 정보가 정의되어 있다.

	bzero(&server, sizeof(server));
	//input ip, port
	printf("input IP (-1 : 127.0.0.1) : ");
	scanf("%s", server.s_ip);
	if (strcmp(server.s_ip, "-1") == 0)
		strlcpy(server.s_ip, "127.0.0.1", sizeof(server.s_ip));
	printf("input Port : ");
	scanf("%hd", &server.s_port);

	//socket(...)
	server.s_listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //소켓을 생성, 어떤 프로토콜을 사용할 것인지에 대해 설정
	if (server.s_listen_sock == -1)
	{
		printf("Err : socket(...) \n");
		exit(1);
	}

	printf("listen sock : %d \n", server.s_listen_sock);//서버에 대한 리슨 소켓 출력

	//set listen socket nonblock opt
	fcntl(server.s_listen_sock, F_SETFL, O_NONBLOCK);//서버에 대한 리슨 소켓을 논블럭 소켓으로 설정 변경 (기본 블럭 소켓)	

	//set listen socket SO_REUSEADDR
	int optval = 1;
	int	retval = setsockopt(server.s_listen_sock, SOL_SOCKET, SO_REUSEADDR,
		&optval, sizeof(optval));//프로세스 종료 후, 수신되지 못한 패킷의 처리를 위해 해당 포트가 일정 시간 대기상태
	if (retval == -1)
	{
		printf("Err : setsockopt(...) \n");
		exit(1);
	}
	
	//bind(...)
	memset(&server.s_addr_in, 0x00, sizeof(server.s_addr_in));
	server.s_addr_in.sin_family = AF_INET;
	server.s_addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	server.s_addr_in.sin_port = htons(server.s_port);
	socklen_t	s_addr_len = sizeof(server.s_addr_in);
	int bind_result = bind(server.s_listen_sock, (const struct sockaddr *)&server.s_addr_in, s_addr_len);//서버에서 어떤 포트와 프로토콜을 사용하여 서버에 사용할 것인지를 설정
	if (bind_result == -1)
	{
		printf("Err : bind(...) \n");
		exit(1);
	}

	//listen(...)
	int	listen_result = listen(server.s_listen_sock, SOMAXCONN);//서버의 상태를 LISTEN으로 변경, 클라이언트의 접속 가능
	if (listen_result == -1)
	{
		printf("Err : listen(...) \n");
		exit(1);
	}
	printf("server ip : %s, port : %d \n", server.s_ip, server.s_port);//서버의 아이피, 포트 출력
	printf("run \n");
	while (1)
	{
		ft_network(&server);//네트워크 처리 부분
		ft_tictactoe(&server);//게임 로직 처리 부분
		ft_disconnect(&server);//접속 종료 클라이언트 처리 부분
	}
	return (0);
}