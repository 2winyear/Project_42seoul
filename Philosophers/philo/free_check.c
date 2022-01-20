/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:31:06 by seungyel          #+#    #+#             */
/*   Updated: 2022/01/16 16:05:51 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
	while (++i < set->info->number_of_philosophers)
		pthread_mutex_destroy(&(set->fork[i].fork));
	pthread_mutex_destroy(&(set->info->active));
	free_ptr((void **)(&(set->fork)));
	free_ptr((void **)(&(set->philo)));
	free_ptr((void **)(&(set->info)));
	free_ptr((void **)(&(set)));
	if (r == ERROR)
		printf("init error\n");
	return (r);
}
