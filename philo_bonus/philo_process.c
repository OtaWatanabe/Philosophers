/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:57:09 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/05 13:51:27 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	philo_process(t_philo *philo, int id)
{
	pthread_t	thread;

	start_routine(philo, id, &thread);
	philo->last_meal = philo->start;
	while (1)
	{
		sem_wait(philo->sem_time);
		if (philo->last_meal + philo->time_die < timestamp(philo, 0))
			print_action(philo, "died");
		sem_post(philo->sem_time);
	}
}

int	count_size(int n)
{
	int	c;

	c = 1;
	while (n / 10)
	{
		c++;
		n /= 10;
	}
	return (c);
}

char	*get_sem_name(int n)
{
	char	*ret;
	size_t	c;

	c = count_size(n);
	ret = malloc(c + 4);
	if (ret == 0)
	{
		printf("malloc error\n");
		return (NULL);
	}
	ret[c + 3] = '\0';
	while (n / 10)
	{
		ret[--c] = '0' + n % 10;
		n /= 10;
	}
	ret[0] = 's';
	ret[1] = 'e';
	ret[2] = 'm';
	return (ret);
}

void	start_routine(t_philo *philo, int id, pthread_t *thread)
{
	char	*sem_name;

	philo->id = id;
	sem_name = get_sem_name(id);
	philo->last_meal = philo->start;
	if (sem_name == NULL)
	{
		sem_post(philo->sem_kill);
		exit(1);
	}
	sem_unlink(sem_name);
	philo->sem_time = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->sem_time == NULL)
	{
		print_error(philo, "sem open", 0);
		exit(1);
	}
	if (pthread_create(thread, NULL, routine, (void *)philo) != 0)
	{
		print_error(philo, "thread create", 0);
		exit(1);
	}
	pthread_detach(*thread);
}
