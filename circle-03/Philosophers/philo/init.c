/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:44:51 by seungyel          #+#    #+#             */
/*   Updated: 2021/12/13 15:01:03 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	get_time(void)
{
	struct timeval	mytime;

	if (gettimeofday(&mytime, NULL) == ERROR)
		return (ERROR);
	return ((mytime.tv_sec * 1000) + (mytime.tv_usec / 1000));
}

t_info	*init_info(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	pthread_mutex_init(&(info->print), NULL);
	pthread_mutex_init(&(info->active), NULL);
	info->flag = true;
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->count_to_eat = -1;
	if (argc == 6)
		info->count_to_eat = ft_atoi(argv[5]);
	return (info);
}

t_philo	*init_philo(t_info *info)
{
	t_philo	*philo;
	int		idx;

	philo = (t_philo *)malloc(sizeof(t_philo) * info->number_of_philosophers);
	if (!philo)
		return (NULL);
	idx = -1;
	while (++idx < info->number_of_philosophers)
	{
		philo[idx].id = idx + 1;
		philo[idx].l_fork = philo[idx].id - 1;
		philo[idx].r_fork = (philo[idx].id) % info->number_of_philosophers;
		philo[idx].eat_count = 0;
		philo[idx].info = info;
	}
	return (philo);
}

t_fork	*init_fork(t_info *info)
{
	t_fork	*fork;
	int		idx;

	fork = (t_fork *)malloc(sizeof(t_fork) * info->number_of_philosophers);
	if (!fork)
		return (NULL);
	idx = -1;
	while (++idx < info->number_of_philosophers)
	{
		pthread_mutex_init(&(fork[idx].fork), NULL);
		fork[idx].id = idx;
	}
	info->fork = fork;
	return (fork);
}

t_set	*init(int argc, char **argv)
{
	t_set	*set;

	if (!(argc >= 5 && argc <= 6))
		return (NULL);
	set = (t_set *)malloc(sizeof(t_set));
	if (!set)
		return (NULL);
	set->info = init_info(argc, argv);
	if (!set->info)
		return (NULL);
	set->philo = init_philo(set->info);
	if (!set->philo)
		return (NULL);
	set->fork = init_fork(set->info);
	if (!set->fork)
		return (NULL);
	return (set);
}
