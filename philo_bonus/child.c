/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:09:48 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/27 12:31:24 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// void	check_usleep(t_philo *philo, int usec)
// {
// 	if (usleep(usec) == -1)
// 		print_error(philo, "usleep");
// }

long long	timestamp(t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error(philo, "time access");
		return (-1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_msec(t_philo *philo, int msec, int id)
{
	long long	end;
	long long	time;

	end = timestamp(philo) + msec;
	time = timestamp(philo);
	while (time < end)
	{
		if (usleep(500) == -1)
			print_error(philo, "usleep");
		time = timestamp(philo);
		if (philo->last_meal + philo->time_die < time)
			die_exit(philo, id);
	}
}

void	philo_process(t_philo *philo, int id)
{
	pthread_t	thread;

	philo->id = id;
	if (pthread_mutex_init(&philo->mutex, NULL) != 0)
	{
		print_error(philo, "mutex init");
		exit(1);
	}
	philo->last_meal = timestamp(philo);
	if (pthread_create(&thread, NULL, routine, (void *)philo) != 0)
	{
		print_error(philo, "thread create");
		exit(1);
	}
	pthread_detach(thread);
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->last_meal + philo->time_die < timestamp(philo))
			die_exit(philo, id);
		pthread_mutex_unlock(&philo->mutex);
	}
}

void	philo_wait_eat(t_philo *philo, int *eat_count)
{
	sem_wait(philo->sem_permission);
	sem_wait(philo->sem_fork);
	print_fork(philo, philo->id);
	sem_wait(philo->sem_fork);
	print_fork(philo, philo->id);
	philo->last_meal = timestamp(philo);
	print_action(philo, philo->id, "eating");
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = timestamp(philo);
	pthread_mutex_unlock(&philo->mutex);
	if (++*eat_count == philo->must_eat)
		sem_post(philo->sem_eat);
	wait_msec(philo, philo->time_eat, philo->id);
	sem_post(philo->sem_fork);
	sem_post(philo->sem_fork);
	sem_post(philo->sem_permission);
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	int				eat_count;

	philo = (t_philo *)ptr;
	eat_count = 0;
	while (1)
	{
		philo_wait_eat(philo, &eat_count);
		print_action(philo, philo->id, "sleeping");
		wait_msec(philo, philo->time_sleep, philo->id);
		print_action(philo, philo->id, "thinking");
	}
	return (NULL);
}
