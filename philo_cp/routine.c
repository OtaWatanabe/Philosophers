/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:28:46 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/02 13:22:45 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	alone_case(t_philo *philo)
{
	print_action(philo, 1, "has taken a fork");
	while (1)
	{
		if (check_exit(philo))
			return ;
	}
}

void	philo_eat(t_philo *philo, int *eat_count, int id)
{
	pthread_mutex_lock(philo->fork_mutex + id - 1);
	print_action(philo, id, "has taken a fork");
	pthread_mutex_lock(philo->fork_mutex + id % philo->philo_num);
	print_action(philo, id, "has taken a fork");
	check_die_update(philo, id, 1);
	print_action(philo, id, "is eating");
	wait_till(philo, philo->time_eat + philo->last_meal[id - 1]);
	pthread_mutex_unlock(philo->fork_mutex + id % philo->philo_num);
	pthread_mutex_unlock(philo->fork_mutex + id - 1);
	if (philo->must_eat != 0 && philo->must_eat == ++*eat_count)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		if (philo->philo_num == ++philo->finish_eat)
			assign_exit(philo);
		pthread_mutex_unlock(&philo->eat_mutex);
	}
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
	if (id % 2 == 0)
		check_usleep(philo, 500);
	eat_count = 0;
	if (philo->philo_num == 1)
	{
		alone_case(philo);
		return (NULL);
	}
	while (1)
	{
		philo_eat(philo, &eat_count, id);
		print_action(philo, id, "is sleeping");
		wait_till(philo, timestamp(philo, 0) + philo->time_sleep);
		print_action(philo, id, "is thinking");
		if (check_exit(philo))
			return (NULL);
	}
}
