/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:31:06 by seungyel          #+#    #+#             */
/*   Updated: 2022/01/14 17:43:37 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	t_usleep(long long begin, long long time)
{
	long long	cur;

	while (true)
	{
		cur = get_time();
		if (cur == ERROR)
			return (FAIL);
		if (cur - begin > time)
			break ;
		if (usleep(100) == ERROR)
			return (FAIL);
	}
	return (SUCCESS);
}

void	free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	free_set(t_set *set, int r)
{
	int	i;

	i = -1;
	sem_close((set->info->active));
	sem_close((set->info->print));
	sem_close((set->info->is_eat));
	sem_close((set->info->fork));
	free_ptr((void **)(&(set->philo)));
	free_ptr((void **)(&(set->info)));
	free_ptr((void **)(&(set)));
	if (r == ERROR)
		printf("init error\n");
	return (r);
}
