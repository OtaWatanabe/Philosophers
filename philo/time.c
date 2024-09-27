/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:47:20 by owatanab          #+#    #+#             */
/*   Updated: 2024/09/27 09:34:36 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	wait_time(t_philo *philo, long long time)
{
	long long	now;

	now = timestamp(philo);
	while (now < time)
	{
		if (now == -1)
			return ;
		now = timestamp(philo);
		check_usleep(philo, 200);
	}
}

long long	timestamp(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(&philo->exit_mutex);
	if (philo->exit)
	{
		pthread_mutex_unlock(&philo->exit_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->exit_mutex);
	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error(philo, "time access");
		return (-1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
