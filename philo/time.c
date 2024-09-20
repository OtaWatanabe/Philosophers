/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:47:20 by owatanab          #+#    #+#             */
/*   Updated: 2024/09/20 17:47:23 by owatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	wait_mseconds(t_info *info, t_philo *philo, int msec)
{
	while (msec-- && philo->exit == 0)
		next_time(philo, info);
}

void	next_time(t_philo *philo, t_info *info)
{
	long long	now;

	if (philo->exit)
		return ;
	now = timestamp(philo);
	while (philo->exit == 0 && now == timestamp(philo))
		philo_usleep(philo, 100);
	if (philo->exit == 0 && info != NULL)
	{
		info->now = now + 1;
		if (philo->time_die == info->now - info->last_meal)
		{
			philo->exit = 1;
			printf("%lld %d died\n", info->now, info->id);
		}
	}
}

long long	timestamp(t_philo *philo)
{
	struct timeval	tv;

	if (philo->exit)
		return (-1);
	if (gettimeofday(&tv, NULL) == -1)
	{
		philo->exit = 1;
		printf("time access error\n");
		return (-1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philo_usleep(t_philo *philo, int usec)
{
	if (philo->exit)
		return ;
	if (usleep(usec) == -1)
	{
		philo->exit = 1;
		printf("usleep error\n");
	}
}
