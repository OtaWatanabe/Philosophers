/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1309839457 <1309839457@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:36:05 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/30 13:48:24 by 1309839457       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	check_usleep(t_philo *philo, int usec)
{
	if (usleep(usec) == -1)
	{
		pthread_mutex_lock(&philo->exit_mutex);
		if (!philo->exit)
			printf("usleep error\n");
		philo->exit = 1;
		pthread_mutex_unlock(&philo->exit_mutex);
	}
}

int	philo_cycle_1(t_philo *philo, int id)
{
	pthread_mutex_lock(philo->fork_mutex + id - 1);
	print_fork(philo, id);
	while (philo->philo_num == 1)
	{
		pthread_mutex_lock(&philo->exit_mutex);
		if (philo->exit)
		{
			pthread_mutex_unlock(&philo->exit_mutex);
			pthread_mutex_unlock(philo->fork_mutex + id - 1);
			return (-1);
		}
		pthread_mutex_unlock(&philo->exit_mutex);
	}
	pthread_mutex_lock(philo->fork_mutex + id % philo->philo_num);
	print_fork(philo, id);
	print_action(philo, id, "eating");
	pthread_mutex_lock(philo->time_mutex + id - 1);
	philo->last_meal[id - 1] = timestamp(philo);
	pthread_mutex_unlock(philo->time_mutex + id - 1);
	wait_time(philo, philo->time_eat + philo->last_meal[id - 1]);
	pthread_mutex_unlock(philo->fork_mutex + id % philo->philo_num);
	pthread_mutex_unlock(philo->fork_mutex + id - 1);
	return (0);
}

void	philo_cycle(t_philo *philo, int *eat_count, int id)
{
	if (philo_cycle_1(philo, id) == -1)
		return ;
	if (philo->must_eat != 0 && philo->must_eat == ++*eat_count)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		if (philo->philo_num == ++philo->finish_eat)
		{
			pthread_mutex_lock(&philo->exit_mutex);
			philo->exit = 1;
			pthread_mutex_unlock(&philo->exit_mutex);
		}
		pthread_mutex_unlock(&philo->eat_mutex);
	}
	print_action(philo, id, "sleeping");
	wait_time(philo, timestamp(philo) + philo->time_sleep);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	int		id;
	int		eat_count;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->id_mutex);
	id = ++philo->id;
	pthread_mutex_unlock(&philo->id_mutex);
	pthread_mutex_lock(&philo->time_mutex[id - 1]);
	philo->last_meal[id - 1] = timestamp(philo);
	pthread_mutex_unlock(&philo->time_mutex[id - 1]);
	if (id % 2 == 0)
		check_usleep(philo, 500);
	eat_count = 0;
	while (1)
	{
		philo_cycle(philo, &eat_count, id);
		pthread_mutex_lock(&philo->exit_mutex);
		if (philo->exit)
			break ;
		pthread_mutex_unlock(&philo->exit_mutex);
		print_action(philo, id, "thinking");
	}
	pthread_mutex_unlock(&philo->exit_mutex);
	return (NULL);
}
