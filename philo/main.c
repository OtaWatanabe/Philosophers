/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:59:00 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/30 14:52:52 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q philo");
// }

void	*supervise(void *ptr)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)ptr;
	while (1)
	{
		i = 0;
		while (i < philo->philo_num)
		{
			pthread_mutex_lock(philo->time_mutex + i);
			if (philo->time_die < timestamp(philo) - philo->last_meal[i])
				print_death(philo, i + 1);
			pthread_mutex_unlock(philo->time_mutex + i);
			++i;
		}
		pthread_mutex_lock(&philo->exit_mutex);
		if (philo->exit)
		{
			pthread_mutex_unlock(&philo->exit_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->exit_mutex);
	}
}

void	make_thread(t_philo *philo)
{
	pthread_t	*thread;
	pthread_t	time;
	int			i;

	thread = malloc(sizeof(pthread_t) * philo->philo_num);
	if (thread == NULL)
	{
		printf("malloc error\n");
		return ;
	}
	philo->start = timestamp(philo);
	i = 0;
	while (i < philo->philo_num)
		philo->last_meal[i++] = philo->start;
	if (pthread_create(&time, NULL, supervise, (void *)philo) == -1)
	{
		printf("thread error\n");
		free(thread);
		return ;
	}
	create_destroy(philo, thread, time);
	free(thread);
}

int	main(int argc, char *argv[])
{
	t_philo		philo;
	int			i;

	if (philo_init(&philo, argc, argv) == -1)
		return (1);
	make_thread(&philo);
	pthread_mutex_destroy(&philo.id_mutex);
	pthread_mutex_destroy(&philo.exit_mutex);
	pthread_mutex_destroy(&philo.eat_mutex);
	i = 0;
	while (i < philo.philo_num)
	{
		pthread_mutex_destroy(philo.fork_mutex + i);
		pthread_mutex_destroy(philo.time_mutex + i);
		++i;
	}
	free(philo.last_meal);
	free(philo.fork_mutex);
	free(philo.time_mutex);
}
