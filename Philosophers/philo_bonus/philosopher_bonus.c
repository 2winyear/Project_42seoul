/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:34:39 by seungyel          #+#    #+#             */
/*   Updated: 2022/01/14 18:17:06 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	*monitor(void *p)
{
	bool		flag;
	long long	time;
	t_philo		*philo;

	flag = true;
	philo = (t_philo *)p;
	time = get_time();
	if (time == ERROR || !t_usleep(time, philo->info->time_to_die - 10))
		flag = false;
	while (flag)
	{
		time = get_time();
		if (time == ERROR)
			break ;
		if (time - philo->last_time > (long long)(philo->info->time_to_die))
		{
			print_text(DEAD, time - philo->info->start_time, philo->id);
			break ;
		}
	}
	sem_post(philo->info->active);
	return (NULL);
}

void	*routine(void *p)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)p;
	i = -1;
	philo->last_time = get_time();
	if (philo->last_time == ERROR)
		philo->info->flag = false;
	if (pthread_create(&philo->tid, NULL, monitor, (void*)philo)
	|| pthread_detach(philo->tid))
	if (philo->id % 2 == 0)
		usleep(philo->info->time_to_eat * 1000);
	sem_wait(philo->info->is_eat);
	while (philo->info->flag)
	{
		if (!time_to_eat(philo)
			|| !time_to_sleep(philo)
			|| !time_to_think(philo))
			break ;
	}
	if (sem_post(philo->info->active) == ERROR)
		return (false);
	return (NULL);
}

void*	is_full(void* ph)
{
	int	idx;
	t_philo *philo;
	
	philo = ph;
	idx = -1;
	while (true)
	{
		sem_wait(philo->info->is_eat);
		if (++idx && idx == philo->info->number_of_philosophers)
		{
			printf("idx: %d\n", idx);
			printf("active full 철학자 배부름.\n");
			philo->info->fully_philo++;
			sem_post(philo->info->active);
		}
	}
	return (NULL);
}

bool	create_philo_main(t_set *set)
{
	int	idx;

	idx = -1;
	sem_wait(set->info->active);
	while (++idx < set->info->number_of_philosophers)
	{
		set->philo[idx].id = idx + 1;
		set->philo[idx].info = set->info;
		set->philo[idx].pid = fork();
		if (set->philo[idx].pid > 0)
		{
			routine(&(set->philo[idx]));
			exit(0);
		}
		else if (set->philo[idx].pid == ERROR)
			return(false);
	}
	if (pthread_create(&set->philo->tid, NULL, is_full, (void*)set->philo)
	|| pthread_detach(set->philo->tid))
		return (false);
	return (true);
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
	if (create_philo_main(set) == false)
		printf("error: create_philo_main\n");
	return (free_set(set, 0));
}
