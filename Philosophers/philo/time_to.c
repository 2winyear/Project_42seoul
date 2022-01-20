/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:52:50 by seungyel          #+#    #+#             */
/*   Updated: 2021/12/13 10:47:06 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_text(t_philo *philo, t_cond cond, long long time, int id)
{
	pthread_mutex_lock(&(philo->info->print));
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
	pthread_mutex_unlock(&(philo->info->print));
}

int	eat_check(t_philo *philo)
{
	if (philo->eat_count == philo->info->count_to_eat)
	{
		philo->info->total_eat_count++;
		if (philo->info->total_eat_count >= philo->info->number_of_philosophers)
			return (SUCCESS);
	}
	return (FAIL);
}

int	time_to_eat(t_philo *p)
{
	long long	time;

	if (pthread_mutex_lock(&(p->info->fork[p->l_fork].fork)) == ERROR
		|| pthread_mutex_lock(&(p->info->fork[p->r_fork].fork)) == ERROR)
		return (FAIL);
	time = get_time();
	if (time == ERROR)
		return (FAIL);
	print_text(p, TAKE_FORK, time - p->info->start_time, p->id);
	print_text(p, EATING, time - p->info->start_time, p->id);
	if (pthread_mutex_unlock(&(p->info->fork[p->l_fork].fork)) == ERROR
		|| pthread_mutex_unlock(&(p->info->fork[p->r_fork].fork)) == ERROR)
		return (FAIL);
	print_text(p, PUT_FORK, time - p->info->start_time, p->id);
	if (!t_usleep(time, p->info->time_to_eat))
		return (FAIL);
	p->eat_count += 1;
	p->last_time = time;
	if ((p->last_time == ERROR)
		|| (p->info->count_to_eat != -1 && eat_check(p)))
		return (FAIL);
	return (SUCCESS);
}

int	time_to_sleep(t_philo *philo)
{
	long long	time;

	time = get_time();
	if (time == ERROR)
		return (FAIL);
	print_text(philo, SLEEPING, time - philo->info->start_time, philo->id);
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
	print_text(philo, THINKING, time - philo->info->start_time, philo->id);
	return (SUCCESS);
}
