/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:50:43 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/03 16:55:06 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	clean_up(t_philo *philo)
{
	sem_check_destroy(philo->sem_eat, "eat");
	sem_check_destroy(philo->sem_fork, "fork");
	sem_check_destroy(philo->sem_kill, "kill");
	sem_check_destroy(philo->sem_permission, "permission");
	sem_check_destroy(philo->sem_time, "time");
	sem_check_destroy(philo->sem_print, "print");
}

void	sem_check_destroy(sem_t *sem, char *sem_name)
{
	if (sem != NULL)
	{
		sem_close(sem);
		sem_unlink(sem_name);
	}
}
