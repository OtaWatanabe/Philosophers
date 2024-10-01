/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:10:54 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/01 18:30:01 by owatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	count_size(int n)
{
	int	c;

	c = 1;
	while (n / 10)
	{
		c++;
		n /= 10;
	}
	return (c);
}

char	*get_sem_name(int n)
{
	char	*ret;
	size_t	c;

	c = count_size(n);
	ret = malloc(c + 4);
	if (ret == 0)
	{
		printf("malloc error\n");
		return (NULL);
	}
	ret[c + 3] = '\0';
	while (n / 10)
	{
		ret[--c] = '0' + n % 10;
		n /= 10;
	}
	ret[0] = 's';
	ret[1] = 'e';
	ret[2] = 'm';
	return (ret);
}

long long	timestamp(t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error(philo, "time access");
		return (-1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_msec(t_philo *philo, int msec, int id)
{
	long long	end;
	long long	time;

	end = timestamp(philo) + msec;
	time = timestamp(philo);
	while (time < end)
	{
		if (usleep(500) == -1)
			print_error(philo, "usleep");
		time = timestamp(philo);
		if (philo->last_meal + philo->time_die < time)
			die_exit(philo, id);
	}
}
