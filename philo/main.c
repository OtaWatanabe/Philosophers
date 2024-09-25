/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:59:00 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/25 23:04:41 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q philo");
// }

void	*time_manage(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	while (philo->time < philo->start)
	{
		pthread_mutex_lock(&philo->time_mutex);
		philo->time = timestamp(philo);
		pthread_mutex_unlock(&philo->time_mutex);
		philo_usleep(philo, 50);
	}
	while (philo_usleep(philo, 50) == 0)
	{
		if (philo->time < timestamp(philo))
		{
			pthread_mutex_lock(&philo->time_mutex);
			philo->time = timestamp(philo);
			pthread_mutex_unlock(&philo->time_mutex);
		}
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_philo		philo;
	int			i;

	if (philo_init(&philo, argc, argv) == -1)
		return (1);
	philo.time = timestamp(&philo);
	philo.start = philo.time + 10;
	make_thread(&philo);
	pthread_mutex_destroy(&philo.id_mutex);
	pthread_mutex_destroy(&philo.print_mutex);
	pthread_mutex_destroy(&philo.eat_mutex);
	pthread_mutex_destroy(&philo.time_mutex);
	i = 0;
	while (i < philo.philo_num)
	{
		pthread_mutex_destroy(philo.fork_mutex + i);
		++i;
	}
	free(philo.fork_available);
	free(philo.fork_mutex);
}
