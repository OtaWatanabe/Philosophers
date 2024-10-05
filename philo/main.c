/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:19:42 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/02 14:16:08 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q philo");
// }

void	join_all(t_philo *philo, pthread_t supervise_thread)
{
	int	i;

	i = 0;
	pthread_join(supervise_thread, NULL);
	while (i < philo->philo_num)
	{
		pthread_join(philo->thread[i], NULL);
		++i;
	}
}

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
			check_die_update(philo, i + 1, 0);
			++i;
		}
		if (check_exit(philo))
			return (NULL);
	}
}

int	start_simulation(t_philo *philo, pthread_t *supervise_thread)
{
	int	i;

	if (pthread_create(supervise_thread, NULL, supervise, (void *)philo) == -1)
	{
		printf("thread error\n");
		return (-1);
	}
	i = 0;
	while (pthread_create(philo->thread + i, NULL, routine, (void *)philo) == 0
		&& ++i < philo->philo_num && check_exit(philo) == 0)
		;
	if (i != philo->philo_num)
	{
		if (!check_exit(philo))
			print_error(philo, "thread", 0);
		while (i--)
			pthread_join(philo->thread[i], NULL);
		pthread_join(*supervise_thread, NULL);
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo		philo;
	pthread_t	supervise_thread;

	if (philo_init(&philo, argc, argv) == -1)
		return (1);
	if (start_simulation(&philo, &supervise_thread) == 0)
		join_all(&philo, supervise_thread);
	clean_up(&philo);
}
