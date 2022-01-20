/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:58:43 by seungyel          #+#    #+#             */
/*   Updated: 2021/07/07 15:27:05 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define BITMAPFILEHEADER 14
#define BITMAPINFOHEADER 40

static void	bmp_header(int fd)
{
	int		tmp;
	char	header[BITMAPFILEHEADER];
	char	info[BITMAPINFOHEADER];

	ft_memset(&header, 0, BITMAPFILEHEADER);
	ft_memset(&info, 0, BITMAPINFOHEADER);
	ft_memmove(&header[0], "BM", 2);
	tmp = BITMAPFILEHEADER + BITMAPINFOHEADER +
		(g_model.bpp / 8) * g_model.width * g_model.height;
	ft_memmove(&header[2], &tmp, 4);
	tmp = BITMAPFILEHEADER + BITMAPINFOHEADER;
	ft_memmove(&header[10], &tmp, 4);
	write(fd, header, BITMAPFILEHEADER);
	tmp = BITMAPINFOHEADER;
	ft_memmove(&info[0], &tmp, 4);
	ft_memmove(&info[4], &g_model.width, 4);
	ft_memmove(&info[8], &g_model.height, 4);
	tmp = 1;
	ft_memmove(&info[12], &tmp, 2);
	ft_memmove(&info[14], &g_model.bpp, 2);
	write(fd, info, BITMAPINFOHEADER);
}

static void	bmp_data(t_info *info, int fd)
{
	int		x;
	int		y;

	y = g_model.height;
	while (y-- > 0)
	{
		x = -1;
		while (++x < g_model.width)
			write(fd, &info->data1[y * g_model.width + x], (g_model.bpp / 8));
	}
}

int			save_bmp(t_info *info)
{
	int		fd;

	if ((fd = open("./image.bmp", O_CREAT | O_RDWR)) == -1)
		ft_exit(0, 1);
	main_loop(info);
	bmp_header(fd);
	bmp_data(info, fd);
	close(fd);
	return (0);
}
