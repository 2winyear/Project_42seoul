/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:52:50 by seungyel          #+#    #+#             */
/*   Updated: 2022/01/14 17:55:06 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	print_text(t_cond cond, long long time, int id)
{
	sem_t *sem_print;

	sem_print = sem_open("print", O_CREAT | O_EXCL, 644, 1);
	if (cond == SLEEPING)
		printf("%lldms %d is sleeping\n", time, id);
	if (cond == EATING)
		printf("%lldms %d is eating\n", time, id);
	if (cond == THINKING)
		printf("%lldms %d is thinking\n", time, id);
	if (cond == TAKE_FORK)
		printf("%lldms %d has taken a fork\n", time, id);
	if (cond == PUT_FORK)
		printf("%lldms %d has put a fork\n", time, id);
	if (cond == FULL)
		printf("%lldms %d is FULL.\n", time, id);
	if (cond == DEAD || cond == FULL)
	{
		printf("%lldms %dis died\n", time, id);
		return ;
	}
	sem_post(sem_print);
}

int	time_to_eat(t_philo *p)
{
	long long	time;
	
	time = get_time();
	if (time == ERROR)
		return (FAIL);
	sem_wait(p->info->fork);
	print_text(TAKE_FORK, time - p->info->start_time, p->id);
	sem_wait(p->info->fork);
	print_text(TAKE_FORK, time - p->info->start_time, p->id);
	print_text(EATING, time - p->info->start_time, p->id);
	p->info->eat_count++;
	if (!t_usleep(time, p->info->time_to_eat))
		return (FAIL);
	sem_post(p->info->fork);
	print_text(PUT_FORK, time - p->info->start_time, p->id);
	sem_post(p->info->fork);
	print_text(PUT_FORK, time - p->info->start_time, p->id);
	p->last_time = time;
	if (p->info->eat_count == p->info->count_to_eat)
		sem_post(p->info->is_eat);
	if ((p->last_time == ERROR) || (p->info->count_to_eat != -1))
		return (FAIL);
	return (SUCCESS);
}

int	time_to_sleep(t_philo *philo)
{
	long long	time;

	time = get_time();
	if (time == ERROR)
		return (FAIL);
	print_text(SLEEPING, time - philo->info->start_time, philo->id);
	if (!t_usleep(time, philo->info->time_to_sleep))
		return (FAIL);
	return (SUCCESS);
}

int	time_to_think(t_philo *philo)
{
	long long	time;

	time = get_time();
	if (time == ERROR)
		return (FAIL);
	print_text(THINKING, time - philo->info->start_time, philo->id);
	return (SUCCESS);
}
