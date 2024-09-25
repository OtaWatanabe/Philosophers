/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:47:20 by owatanab          #+#    #+#             */
/*   Updated: 2024/09/25 10:59:59 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	wait_mseconds(t_info *info, t_philo *philo, int msec)
{
	if (philo->exit)
		return ;
	while (msec-- && philo->exit == 0)
		next_time(philo, info);
}

void	next_time(t_philo *philo, t_info *info)
{
	long long	now;

	now = info->now;
	while (philo->exit == 0 && now == timestamp(philo))
		philo_usleep(philo, 50);
	if (philo->exit == 0)
	{
		info->now = now + 1;
		if (philo->time_die < info->now - info->last_meal)
			print_death(philo, info);
	}
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

void	philo_usleep(t_philo *philo, int usec)
{
	if (philo->exit)
		return ;
	if (usleep(usec) == -1)
		print_error(philo, "usleep");
}

void	wait_start(t_philo *philo, int id)
{
	if (philo->exit)
		return ;
	while (timestamp(philo) < philo->start && philo->exit == 0)
		philo_usleep(philo, 50);
	if (id % 2)
		philo_usleep(philo, 1000);
}

void	init_routine(t_philo *philo, t_info *info)
{
	if (philo->exit)
		return ;
	info->fork_count = 0;
	info->after_sleep = 0;
	while (timestamp(philo) < philo->start && philo->exit == 0)
		philo_usleep(philo, 50);
	if(info->id % 2 == 0)
	{
		philo->fork_count[info->id - 1] = 2;
	}
	else if (info->id == philo->philo_num)
	{
		philo->fork_count[info->id - 1] = 1;
		print_fork(philo, info, 1);
		philo_usleep(philo, 500);
		info->fork_count = 1;
	}
	else
		philo_usleep(philo, 500);
}
