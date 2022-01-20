/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:44:51 by seungyel          #+#    #+#             */
/*   Updated: 2022/01/14 18:20:44 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

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

	philo = (t_philo *)malloc(sizeof(t_philo) * info->number_of_philosophers);
	if (!philo)
		return (NULL);
	return (philo);
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
	set->info->start_time = get_time();
	set->info->fork = sem_open("fork", O_CREAT | O_EXCL, 644, set->info->number_of_philosophers);
	set->info->print = sem_open("print_text", O_CREAT | O_EXCL, 644, 1);
	set->info->active = sem_open("active", O_CREAT | O_EXCL, 644, 1);
	set->info->is_eat = sem_open("is_eat", O_CREAT | O_EXCL, 644, 1);
	set->info->eat_count = 0;
	return (set);
}
