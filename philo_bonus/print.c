/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:45:23 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/05 13:55:03 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	print_action(t_philo *philo, char *action)
{
	u_int64_t	time;

	sem_wait(philo->sem_print);
	time = timestamp(philo, 1);
	if (time != 0)
		printf("%ld %d %s\n", time - philo->start, philo->id, action);
	if (action[0] == 'd')
		sem_post(philo->sem_kill);
	else
		sem_post(philo->sem_print);
}

void	print_error(t_philo *philo, char *error, int if_wait)
{
	if (!if_wait)
		sem_wait(philo->sem_print);
	printf("%s error\n", error);
	sem_post(philo->sem_kill);
}
