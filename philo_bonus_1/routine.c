/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:25:59 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/05 14:10:26 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;
	int		eat_count;

	philo = (t_philo *)ptr;
	eat_count = 0;
	while (1)
	{
		philo_eat(philo, &eat_count);
		print_action(philo, "sleeping");
		wait_till(philo, philo->time_sleep + timestamp(philo, 0));
		print_action(philo, "is thinking");
	}
	return (NULL);
}

void	philo_eat(t_philo *philo, int *eat_count)
{
	sem_wait(philo->sem_permission);
	sem_wait(philo->sem_fork);
	print_action(philo, "has taken a fork");
	sem_wait(philo->sem_fork);
	print_action(philo, "has taken a fork");
	sem_wait(philo->sem_time);
	if (philo->last_meal + philo->time_die < timestamp(philo, 0))
		print_action(philo, "died");
	sem_post(philo->sem_time);
	print_action(philo, "is eating");
	sem_wait(philo->sem_time);
	philo->last_meal = timestamp(philo, 0);
	sem_post(philo->sem_time);
	if (++*eat_count == philo->must_eat)
		sem_post(philo->sem_eat);
	wait_till(philo, philo->time_eat + timestamp(philo, 0));
	sem_post(philo->sem_fork);
	sem_post(philo->sem_fork);
	sem_post(philo->sem_permission);
}
