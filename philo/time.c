/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:18:36 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/06 16:58:53 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

u_int64_t	timestamp(t_philo *philo, int if_lock)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error(philo, "time access", if_lock);
		return (0);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_till(t_philo *philo, u_int64_t time)
{
	u_int64_t	now;

	now = timestamp(philo, 0);
	while (now < time)
	{
		if (now == 0)
			return ;
		now = timestamp(philo, 0);
		check_usleep(philo, 200);
		if (check_exit(philo))
			return ;
	}
}

void	check_usleep(t_philo *philo, int usec)
{
	if (usleep(usec) == -1)
		print_error(philo, "usleep", 0);
}

int	time_init(t_philo *philo)
{
	int	i;

	philo->start = timestamp(philo, 0);
	if (philo->exit)
	{
		clean_up(philo);
		return (-1);
	}
	i = 0;
	while (i < philo->philo_num)
		philo->last_meal[i++] = philo->start;
	return (0);
}
