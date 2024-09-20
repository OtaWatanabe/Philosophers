/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:36:05 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/19 17:48:17 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("time access error\n");
		return (-1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	get_fork(t_philo *philo, t_info *info)
{
	if (philo->fork_status[info->id - 1] == 0)
	{
		printf("%lld %d has taken a fork\n", info->now, info->id);
		philo->fork_status[info->id - 1] = info->id;
	}
	if (philo->fork_status[info->id - 1] != info->id)
		return (0);
	if (info->id == philo->philo_num && philo->fork_status[0] == 0)
		return (1);
}

int	put_down_fork(t_philo *philo, int id)
{
	if (id == philo->philo_num && philo->fork_status[0] == id)
		philo->fork_status[0] = 0;
	else if (id < philo->philo_num && philo->fork_status[id] == id)
		philo->fork_status[id] = 0;
	if (philo->fork_status[id - 1] == id)
		philo->fork_status[id - 1] = 0;
}

int	next_time(t_philo *philo)
{
	struct timeval	tv;
	suseconds_t		usec;

	if (philo->exit)
		return (-1);
	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("gettimeofday error\n");
		philo->exit = 1;
		return (-1);
	}
	usec = tv.tv_usec;
	while (tv.tv_usec / 1000 == usec / 1000)
	{
		usleep(100);
		if (gettimeofday(&tv, NULL) == -1)
		{
			philo->exit = 1;
			printf("gettimeofday error\n");
			return (-1);
		}
	}
	return (0);
}

int	load_status(t_info *info, t_philo *philo)
{
	if (info->status == 0)
	{
		
	}
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	t_info			info;
	int				status;

	info.status = 0;
	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->mutex);
	info.id = ++philo->id;
	pthread_mutex_unlock(&philo->mutex);
	if (info.id % 2)
		usleep(100);
	while (philo->exit == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		status = get_fork(philo, info.id);
		pthread_mutex_unlock(&philo->mutex);
		if (status != info.status)
		{
			info.status = status;
			if (load_status(&info, philo) == -1)
				return (NULL);
		}
		else if (next_time(&philo) == -1)
			return (NULL);
	}
	return (NULL);
}
