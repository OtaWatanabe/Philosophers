/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:17:08 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/02 13:22:24 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	check_exit(t_philo *philo)
{
	pthread_mutex_lock(&philo->exit_mutex);
	if (philo->exit)
	{
		pthread_mutex_unlock(&philo->exit_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->exit_mutex);
	return (0);
}

void	assign_exit(t_philo *philo)
{
	pthread_mutex_lock(&philo->exit_mutex);
	philo->exit = 1;
	pthread_mutex_unlock(&philo->exit_mutex);
}

void	check_die_update(t_philo *philo, int id, int if_time_update)
{
	pthread_mutex_lock(philo->time_mutex + id - 1);
	if ((u_int64_t)philo->time_die
		< timestamp(philo, 0) - philo->last_meal[id - 1])
		print_action(philo, id, "died");
	if (if_time_update)
		philo->last_meal[id - 1] = timestamp(philo, 0);
	pthread_mutex_unlock(philo->time_mutex + id - 1);
}
