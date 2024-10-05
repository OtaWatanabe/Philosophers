/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:34:00 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/05 14:01:00 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

u_int64_t	timestamp(t_philo *philo, int if_wait)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error(philo, "time access", if_wait);
		return (-1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_till(t_philo *philo, u_int64_t time)
{
	u_int64_t	now;

	now = timestamp(philo, 0);
	while (now != 0 && now < time)
	{
		if (usleep(200) == -1)
			print_error(philo, "usleep", 0);
		now = timestamp(philo, 0);
	}
}
