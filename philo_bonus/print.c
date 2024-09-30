/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:01:47 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/30 17:24:07 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	print_fork(t_philo *philo, int id)
{
	long long	time;

	time = timestamp(philo) - philo->start;
	sem_wait(philo->sem_print);
	printf("%lld %d has taken a fork\n", time, id);
	sem_post(philo->sem_print);
}

void	print_action(t_philo *philo, int id, char *action)
{
	long long	time;

	time = timestamp(philo) - philo->start;
	sem_wait(philo->sem_print);
	printf("%lld %d is %s\n", time, id, action);
	sem_post(philo->sem_print);
}

void	die_exit(t_philo *philo, int id)
{
	long long	time;

	time = timestamp(philo) - philo->start;
	sem_wait(philo->sem_print);
	printf("%lld %d died\n", time, id);
	sem_post(philo->sem_kill);
}

void	print_error(t_philo *philo, char *error)
{
	sem_wait(philo->sem_print);
	printf("%s error\n", error);
	sem_post(philo->sem_kill);
}
