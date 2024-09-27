/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:59:00 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/27 12:35:40 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	*eat_count(void *ptr)
{
	t_philo	*philo;
	int		count;

	count = 0;
	philo = (t_philo *)ptr;
	while (1)
	{
		sem_wait(philo->sem_eat);
		++count;
		if (count == philo->philo_num)
		{
			sem_post(philo->sem_kill);
			return (NULL);
		}
	}
}

int	main(int argc, char *argv[])
{
	t_philo		philo;

	if (philo_init(&philo, argc, argv) == -1)
		return (1);
	make_process(&philo);
	sem_check_destroy(philo.sem_fork, "fork");
	sem_check_destroy(philo.sem_print, "print");
	sem_check_destroy(philo.sem_permission, "permission");
	sem_check_destroy(philo.sem_eat, "eat");
	sem_check_destroy(philo.sem_kill, "kill");
}
