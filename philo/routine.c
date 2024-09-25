/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:36:05 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/25 23:14:40 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	get_fork(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&philo->fork_mutex[info->id - 1]);
	if (philo->fork_available[info->id - 1] <= info->now)
	{
		print_fork(philo, info, 1);
		philo->fork_available[info->id - 1] = LLONG_MAX;
		++info->fork_count;
	}
	pthread_mutex_unlock(&philo->fork_mutex[info->id - 1]);
	pthread_mutex_lock(&philo->fork_mutex[info->id % philo->philo_num]);
	if (philo->fork_available[info->id % philo->philo_num] <= info->now)
	{
		print_fork(philo, info, 1);
		philo->fork_available[info->id % philo->philo_num] = LLONG_MAX;
		++info->fork_count;
	}
	pthread_mutex_unlock(&philo->fork_mutex[info->id % philo->philo_num]);
}

void	philo_eat(t_info *info, t_philo *philo)
{
	print_action(philo, info, "eating");
	pthread_mutex_lock(&philo->time_mutex);
	info->last_meal = philo->time;
	info->now = philo->time;
	pthread_mutex_unlock(&philo->time_mutex);
	pthread_mutex_lock(&philo->fork_mutex[info->id - 1]);
	philo->fork_available[info->id - 1] = info->now + philo->time_eat;
	pthread_mutex_unlock(&philo->fork_mutex[info->id - 1]);
	pthread_mutex_lock(&philo->fork_mutex[info->id % philo->philo_num]);
	philo->fork_available[info->id % philo->philo_num] 
		= info->now + philo->time_eat;
	pthread_mutex_unlock(&philo->fork_mutex[info->id % philo->philo_num]);
	wait_time(info, philo, info->now + philo->time_eat);
	if (philo->must_eat == ++info->eat_count)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		if (philo->philo_num == ++philo->finish_eat)
		{
			pthread_mutex_lock(&philo->print_mutex);
			philo->exit = 1;
			pthread_mutex_unlock(&philo->print_mutex);
		}
		pthread_mutex_unlock(&philo->eat_mutex);
	}
}

void	load_status(t_info *info, t_philo *philo)
{
	if (info->fork_count < 2)
	{
		info->after_sleep = 0;
		print_action(philo, info, "thinking");
		return ;
	}
	philo_eat(info, philo);
	print_action(philo, info, "sleeping");
	info->fork_count = 0;
	wait_time(info, philo, info->now + philo->time_sleep);
	info->after_sleep = 1;
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->id_mutex);
	info.id = ++philo->id;
	pthread_mutex_unlock(&philo->id_mutex);
	pthread_mutex_lock(&philo->time_mutex);
	info.now = philo->time;
	pthread_mutex_unlock(&philo->time_mutex);
	info.last_meal = info.now;
	init_routine(philo, &info);
	while (1)
	{
		if (!info.after_sleep && philo_usleep(philo, 300) == -1)
			return (NULL);
		get_fork(philo, &info);
		if (info.fork_count == 2 || info.after_sleep)
			load_status(&info, philo);
		if (!info.after_sleep)
			next_time(philo, &info);
	}
	return (NULL);
}
