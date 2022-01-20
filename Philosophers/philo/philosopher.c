/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:34:39 by seungyel          #+#    #+#             */
/*   Updated: 2022/01/16 16:30:15 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*monitor(void *p)
{
	long long	time;
	t_philo		*philo;

	philo = (t_philo *)p;
	time = get_time();
	if (time == ERROR || !t_usleep(time, philo->info->time_to_die - 10))
		philo->info->flag = false;
	while (philo->info->flag)
	{
		if (time == ERROR)
			break ;
		if (time - philo->last_time > (long long)(philo->info->time_to_die))
		{
			print_text(philo, DEAD, time - philo->info->start_time, philo->id);
			break ;
		}
	}
	pthread_mutex_unlock(&(philo->info->active));
	return (NULL);
}

void	*thread_function(void *p)
{
	int		i;
	long long time;
	t_philo	*philo;

	philo = (t_philo *)p;
	i = -1;
	time = get_time();
	philo->last_time = get_time();
	if (philo->last_time == ERROR)
		philo->info->flag = false;
	if (philo->id % 2 == 0)
		t_usleep(time, philo->info->time_to_eat * 1000);
	while (philo->info->flag)
	{
		if (!time_to_eat(philo)
			|| !time_to_sleep(philo)
			|| !time_to_think(philo))
			break ;
	}
	pthread_mutex_unlock(&(philo->info->active));
	return (NULL);
}

void	create_philo_main(t_set *set)
{
	pthread_t	tid;
	int			idx;

	idx = -1;
	pthread_mutex_lock(&(set->info->active));
	while (++idx < set->info->number_of_philosophers)
	{
		if (pthread_create(&tid, NULL, thread_function, &set->philo[idx]) < 0
			|| pthread_detach(tid) < 0
			|| pthread_create(&tid, NULL, monitor, &set->philo[idx]) < 0
			|| pthread_detach(tid) < 0)
		{
			pthread_mutex_unlock(&(set->info->active));
			break ;
		}
	}
	pthread_mutex_lock(&(set->info->active));
}

int	main(int argc, char **argv)
{
	t_set	*set;

	if (!(argc >= 5 && argc <= 6))
	{
		printf("command argument error");
		return (0);
	}
	set = init(argc, argv);
	if (set == NULL)
		return (free_set(set, ERROR));
	set->info->start_time = get_time();
	create_philo_main(set);
	return (free_set(set, 0));
}
