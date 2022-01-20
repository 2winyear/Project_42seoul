/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeukim <byeukim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:15:53 by byeukim           #+#    #+#             */
/*   Updated: 2021/12/02 12:15:53 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_run_redirection(t_deque_node *node)
{
	if (node->prev_node->spt_type == 2)
		append_file(node);
	else if (node->spt_type == 3)
		send_doc(node);
	else if (node->prev_node->spt_type == 4)
		overwrite_file(node);
	else if (node->spt_type == 5)
		send_file(node);
	return (0);
}

void	overwrite_file(t_deque_node *node)
{
	int		fd;
	int		byte;
	char	buf[BUF_SIZE];

	fd = open(node->command[0], O_TRUNC | O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		printf("Open error\n");
		exit(1);
	}
	byte = read(STDIN_FILENO, buf, BUF_SIZE - 1);
	while (byte > 0)
	{
		buf[byte] = '\0';
		if (node->spt_type == 2 || node->spt_type == 4)
			write(STDOUT_FILENO, buf, byte);
		else
			write(fd, buf, byte);
		byte = read(STDIN_FILENO, buf, BUF_SIZE - 1);
	}
	close(fd);
	exit(0);
}

void	append_file(t_deque_node *node)
{
	int		fd;
	int		byte;
	char	buf[BUF_SIZE];

	fd = open(node->command[0], O_APPEND | O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		printf("Open error\n");
		exit(1);
	}
	byte = read(STDIN_FILENO, buf, BUF_SIZE - 1);
	while (byte > 0)
	{
		buf[byte] = '\0';
		if (node->spt_type == 2 || node->spt_type == 4)
			write(STDOUT_FILENO, buf, byte);
		else
			write(fd, buf, byte);
		byte = read(STDIN_FILENO, buf, BUF_SIZE - 1);
	}
	close(fd);
	exit(0);
}

void	send_file(t_deque_node *node)
{
	int		fd;
	int		byte;
	char	buf[BUF_SIZE];

	fd = open(node->command[0], O_RDWR);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directiory\n", node->command[0]);
		exit(1);
	}
	byte = read(fd, buf, BUF_SIZE - 1);
	while (byte > 0)
	{
		buf[byte] = '\0';
		write(STDOUT_FILENO, buf, byte);
		byte = read(fd, buf, BUF_SIZE - 1);
	}
	close(fd);
	exit(0);
}

void	send_doc(t_deque_node *node)
{
	int		byte;
	char	buf[BUF_SIZE];

	byte = read(STDIN_FILENO, buf, BUF_SIZE - 1);
	while (byte > 0)
	{
		buf[byte] = '\0';
		if (!ft_strncmp (buf, node->command[0], ft_strlen (node->command[0])) \
				&& buf[ft_strlen(node->command[0])] == '\n')
			break ;
		write(STDOUT_FILENO, buf, byte);
		byte = read(STDIN_FILENO, buf, BUF_SIZE - 1);
	}
	if (byte == -1)
		printf("File Read Error\n");
	exit(0);
}
