/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:09:48 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/30 17:32:44 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	process_init(t_philo *philo, int id, pthread_t *thread)
{
	char		*sem_name;

	philo->id = id;
	sem_name = get_sem_name(id);
	philo->last_meal = philo->start;
	if (sem_name == NULL)
	{
		sem_post(philo->sem_kill);
		exit(1);
	}
	sem_unlink(sem_name);
	philo->sem_exit = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->sem_exit == NULL)
	{
		print_error(philo, "sem open");
		exit(1);
	}
	if (pthread_create(thread, NULL, routine, (void *)philo) != 0)
	{
		print_error(philo, "thread create");
		exit(1);
	}
	pthread_detach(*thread);
}

void	philo_process(t_philo *philo, int id)
{
	pthread_t	thread;

	process_init(philo, id, &thread);
	while (1)
	{
		sem_wait(philo->sem_exit);
		if (philo->last_meal + philo->time_die < timestamp(philo))
			die_exit(philo, id);
		sem_post(philo->sem_exit);
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
	sem_wait(philo->sem_exit);
	philo->last_meal = timestamp(philo);
	sem_post(philo->sem_exit);
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
