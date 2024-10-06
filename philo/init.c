/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:23:48 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/06 16:59:27 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	philo_init(t_philo *philo, int argc, char *argv[])
{
	memset(philo, 0, sizeof(t_philo));
	if (get_input(philo, argc, argv) == -1)
		return (-1);
	if (malloc_philo(philo) == -1)
		return (-1);
	if (philo_mutex_init(philo) == -1)
		return (-1);
	if (time_init(philo) == -1)
		return (-1);
	return (0);
}

int	malloc_philo(t_philo *philo)
{
	philo->thread = (pthread_t *)malloc(sizeof(t_philo) * philo->philo_num);
	philo->last_meal = (u_int64_t *)malloc(
			sizeof(u_int64_t) * philo->philo_num);
	philo->time_mutex = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * philo->philo_num);
	philo->fork_mutex = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * philo->philo_num);
	if (philo->last_meal == NULL || philo->time_mutex == NULL
		|| philo->fork_mutex == NULL || philo->thread == NULL)
	{
		printf("malloc error\n");
		free_philo(philo);
		return (-1);
	}
	return (0);
}

int	philo_mutex_init(t_philo *philo)
{
	if (pthread_mutex_init(&philo->exit_mutex, NULL) == -1)
	{
		printf("mutex init error\n");
		return (-1);
	}
	else if (pthread_mutex_init(&philo->id_mutex, NULL) == -1)
	{
		printf("mutex init error\n");
		pthread_mutex_destroy(&philo->exit_mutex);
		return (-1);
	}
	else if (pthread_mutex_init(&philo->eat_mutex, NULL) == -1)
	{
		printf("mutex init error\n");
		pthread_mutex_destroy(&philo->exit_mutex);
		pthread_mutex_destroy(&philo->id_mutex);
		return (-1);
	}
	return (philo_array_init(philo));
}

int	philo_array_init(t_philo *philo)
{
	if (mutex_array_init(philo->time_mutex, philo->philo_num) == -1)
	{
		pthread_mutex_destroy(&philo->exit_mutex);
		pthread_mutex_destroy(&philo->id_mutex);
		pthread_mutex_destroy(&philo->eat_mutex);
		free_philo(philo);
		return (-1);
	}
	if (mutex_array_init(philo->fork_mutex, philo->philo_num) == -1)
	{
		pthread_mutex_destroy(&philo->exit_mutex);
		pthread_mutex_destroy(&philo->id_mutex);
		pthread_mutex_destroy(&philo->eat_mutex);
		destroy_array_mutex(philo->time_mutex, philo->philo_num);
		free_philo(philo);
		return (-1);
	}
	return (0);
}

int	mutex_array_init(pthread_mutex_t *mutex_array, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(mutex_array + i, NULL) == -1)
			break ;
		++i;
	}
	if (i != num)
	{
		printf("mutex init error\n");
		destroy_array_mutex(mutex_array, i);
		return (-1);
	}
	return (0);
}
