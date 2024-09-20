/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:36:05 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/20 17:50:49 by owatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	get_fork(t_philo *philo, t_info *info)
{
	int	ret;

	if (philo->exit)
		return (-1);
	if (philo->fork_status[info->id - 1] == 0)
	{
		printf("%lld %d has taken a fork\n", info->now, info->id);
		philo->fork_status[info->id - 1] = info->id;
	}
	if (info->id == philo->philo_num && philo->fork_status[0] == 0)
	{
		printf("%lld %d has taken a fork\n", info->now, info->id);
		philo->fork_status[0] = info->id;
	}
	else if (info->id != philo->philo_num && philo->fork_status[info->id] == 0)
	{
		printf("%lld %d has taken a fork\n", info->now, info->id);
		philo->fork_status[0] = info->id;
	}
	ret = 0;
	if (philo->fork_status[info->id - 1] == info->id - 1)
		++ret;
	if ((info->id == philo->philo_num && philo->fork_status[0] == info->id)
		|| (info->id < philo->philo_num && philo->fork_status[info->id] == info->id))
		++ret;
	return (ret);
}

void	put_down_fork(t_philo *philo, int id)
{
	if (id == philo->philo_num)
		philo->fork_status[0] = 0;
	else
		philo->fork_status[id] = 0;
	philo->fork_status[id - 1] = 0;
}

void	load_status(t_info *info, t_philo *philo, int fork_num)
{
	if (philo->exit)
		return ;
	if (fork_num < 2)
	{
		printf("%lld %d is thinking\n", info->now, info->id);
		return ;
	}
	printf("%lld %d is eating\n", info->now, info->id);
	wait_mseconds(info, philo, philo->time_die);
	if (philo->exit)
		return ;
	printf("%lld %d is sleeping\n", info->now, info->id);
	pthread_mutex_lock(&philo->mutex);
	put_down_fork(philo, info->id);
	pthread_mutex_unlock(&philo->mutex);
	wait_mseconds(info, philo, philo->time_die);
	info->after_sleep = 1;
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	t_info			info;
	int				fork_num;

	info.after_sleep = 0;
	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->mutex);
	info.id = ++philo->id;
	pthread_mutex_unlock(&philo->mutex);
	info.now = timestamp(philo);
	info.last_meal = info.now;
	if (info.id % 2)
		philo_usleep(philo, 100);
	while (philo->exit == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		fork_num = get_fork(philo, &info);
		pthread_mutex_unlock(&philo->mutex);
		if (info.after_sleep || fork_num == 2)
		{
			info.after_sleep = 0;
			load_status(&info, philo, fork_num);
		}
		if (!info.after_sleep)
			next_time(philo, &info);
	}
	return (NULL);
}
