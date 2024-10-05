/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:40:21 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/05 13:52:38 by otawatanabe      ###   ########.fr       */
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

void	make_process(t_philo *philo)
{
	pid_t		p;
	int			i;
	pthread_t	thread;

	i = 0;
	philo->start = timestamp(philo, 0);
	while (i < philo->philo_num)
	{
		p = fork();
		if (p == -1)
		{
			printf("fork error\n");
			kill(0, SIGTERM);
			return ;
		}
		if (p == 0)
			philo_process(philo, i + 1);
		++i;
	}
	if (philo->must_eat == 0
		|| pthread_create(&thread, NULL, eat_count, (void *)philo) == 0)
		sem_wait(philo->sem_kill);
	else
		printf("thread error\n");
	kill(0, SIGTERM);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;

	if (philo_init(&philo, argc, argv) == -1)
		return (1);
	make_process(&philo);
}
