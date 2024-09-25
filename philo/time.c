/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:47:20 by owatanab          #+#    #+#             */
/*   Updated: 2024/09/25 23:06:55 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	wait_time(t_info *info, t_philo *philo, long long time)
{
	while (1)
	{
		pthread_mutex_lock(&philo->time_mutex);
		if (time <= philo->time)
		{
			info->now = philo->time;
			pthread_mutex_unlock(&philo->time_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->time_mutex);
		pthread_mutex_lock(&philo->print_mutex);
		if (philo->exit)
		{
			pthread_mutex_unlock(&philo->print_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->print_mutex);
		philo_usleep(philo, 500);
	}
}

void	next_time(t_philo *philo, t_info *info)
{
	while (1)
	{
		pthread_mutex_lock(&philo->time_mutex);
		if (info->now != philo->time)
		{
			pthread_mutex_unlock(&philo->time_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->time_mutex);
		pthread_mutex_lock(&philo->print_mutex);
		if (philo->exit)
		{
			pthread_mutex_unlock(&philo->print_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->print_mutex);
		philo_usleep(philo, 500);
	}
	pthread_mutex_lock(&philo->time_mutex);
	info->now = philo->time;
	pthread_mutex_unlock(&philo->time_mutex);
	if (philo->time_die < info->now - info->last_meal)
		print_death(philo, info);
}

long long	timestamp(t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error(philo, "time access");
		return (-1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	philo_usleep(t_philo *philo, int usec)
{
	pthread_mutex_lock(&philo->print_mutex);
	if (philo->exit)
	{
		pthread_mutex_unlock(&philo->print_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->print_mutex);
	if (usleep(usec) == -1)
		print_error(philo, "usleep");
	return (0);
}

void	init_routine(t_philo *philo, t_info *info)
{
	if (info->id % 2 == 0)
	{
		print_fork(philo, info, 2);
		info->fork_count = 2;
	}
	else if (info->id == philo->philo_num)
	{
		print_fork(philo, info, 1);
		info->fork_count = 1;
	}
}
