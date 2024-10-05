/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:44:52 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/02 11:48:23 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	clean_up(t_philo *philo)
{
	destroy_array_mutex(philo->time_mutex, philo->philo_num);
	destroy_array_mutex(philo->fork_mutex, philo->philo_num);
	free_philo(philo);
}

void	destroy_array_mutex(pthread_mutex_t *mutex, int num)
{
	while (num--)
		pthread_mutex_destroy(mutex + num);
}

void	free_philo(t_philo *philo)
{
	free(philo->time_mutex);
	free(philo->fork_mutex);
	free(philo->last_meal);
	free(philo->thread);
}
