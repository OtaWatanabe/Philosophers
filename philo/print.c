/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:22:59 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/02 13:22:41 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	print_error(t_philo *philo, char *error, int if_lock)
{
	if (if_lock)
	{
		philo->exit = 1;
		printf("%s error\n", error);
		return ;
	}
	pthread_mutex_lock(&philo->exit_mutex);
	if (philo->exit == 0)
	{
		philo->exit = 1;
		printf("%s error\n", error);
	}
	pthread_mutex_unlock(&philo->exit_mutex);
}

void	print_action(t_philo *philo, int id, char *action)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->exit_mutex);
	time = timestamp(philo, 0) - philo->start;
	if (philo->exit == 0)
	{
		printf("%lld %d %s\n", time, id, action);
		if (action[0] == 'd')
			philo->exit = 1;
	}
	pthread_mutex_unlock(&philo->exit_mutex);
}
