/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:24:34 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/26 17:13:03 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	print_action(t_philo *philo, int id, char *action)
{
	long long	time;

	time = timestamp(philo);
	pthread_mutex_lock(&philo->exit_mutex);
	if (philo->exit == 0)
		printf("%lld %d is %s\n", time, id, action);
	pthread_mutex_unlock(&philo->exit_mutex);
}

void	print_death(t_philo *philo, int id)
{
	long long	time;

	time = timestamp(philo);
	pthread_mutex_lock(&philo->exit_mutex);
	if (philo->exit == 0)
	{
		philo->exit = 1;
		printf("%lld %d died\n", time, id);
	}
	pthread_mutex_unlock(&philo->exit_mutex);
}

void	print_fork(t_philo *philo, int id)
{
	long long	time;

	time = timestamp(philo);
	pthread_mutex_lock(&philo->exit_mutex);
	if (philo->exit == 0)
		printf("%lld %d has taken a fork\n", time, id);
	pthread_mutex_unlock(&philo->exit_mutex);
}

void	print_error(t_philo *philo, char *error)
{
	pthread_mutex_lock(&philo->exit_mutex);
	if (philo->exit == 0)
	{
		philo->exit = 1;
		printf("%s error\n", error);
	}
	pthread_mutex_unlock(&philo->exit_mutex);
}
