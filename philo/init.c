/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1309839457 <1309839457@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 23:01:51 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/30 13:31:10 by 1309839457       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	mutex_init(t_philo *philo)
{
	philo->fork_mutex = malloc(sizeof(pthread_mutex_t) * philo->philo_num);
	philo->time_mutex = malloc(sizeof(pthread_mutex_t) * philo->philo_num);
	philo->last_meal = malloc(sizeof(long long) * philo->philo_num);
	if (philo->fork_mutex == NULL || philo->time_mutex == NULL
		|| philo->last_meal == NULL)
		printf("malloc error\n");
	else if (pthread_mutex_init(&philo->id_mutex, NULL))
		printf("mutex init error\n");
	else if (pthread_mutex_init(&philo->eat_mutex, NULL))
	{
		pthread_mutex_destroy(&philo->id_mutex);
		printf("mutex init error\n");
	}
	else if (pthread_mutex_init(&philo->exit_mutex, NULL))
	{
		pthread_mutex_destroy(&philo->id_mutex);
		pthread_mutex_destroy(&philo->eat_mutex);
		printf("mutex init error\n");
	}
	else
		return (0);
	return (-1);
}

int	philo_init(t_philo *philo, int argc, char *argv[])
{
	memset(philo, 0, sizeof(t_philo));
	if (argc < 5 || 6 < argc)
	{
		printf("The number of arguments must be 4 or 5.\n");
		return (-1);
	}
	philo->philo_num = check_atoi(argv[1]);
	philo->time_die = check_atoi(argv[2]);
	philo->time_eat = check_atoi(argv[3]);
	philo->time_sleep = check_atoi(argv[4]);
	if (argc == 6)
		philo->must_eat = check_atoi(argv[5]);
	if (philo->philo_num == -1 || philo->time_die == -1 || philo->time_eat == -1
		|| philo->time_sleep == -1 || philo->must_eat == -1)
		return (-1);
	if (!mutex_init(philo) && !philo_init_2(philo))
		return (0);
	free(philo->fork_mutex);
	free(philo->time_mutex);
	free(philo->last_meal);
	return (-1);
}

int	philo_init_2(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_num
		&& !pthread_mutex_init(philo->fork_mutex + i, NULL))
		++i;
	if (i != philo->philo_num)
	{
		printf("mutex init error\n");
		while (i--)
			pthread_mutex_destroy(philo->fork_mutex + i);
		return (-1);
	}
	i = 0;
	while (i < philo->philo_num
		&& !pthread_mutex_init(philo->time_mutex + i++, NULL))
		;
	if (i == philo->philo_num)
		return (0);
	printf("mutex init error\n");
	while (i--)
		pthread_mutex_destroy(philo->fork_mutex + i);
	return (-1);
}

void	create_destroy(t_philo *philo, pthread_t *thread, pthread_t time)
{
	int	i;

	i = 0;
	while (pthread_create(thread + i, NULL, routine, (void *)philo) == 0
		&& ++i < philo->philo_num)
		;
	if (i != philo->philo_num)
	{
		printf("thread error\n");
		pthread_mutex_lock(&philo->exit_mutex);
		philo->exit = 1;
		pthread_mutex_unlock(&philo->exit_mutex);
		while (i--)
			pthread_detach(thread[i]);
		pthread_detach(time);
		free(thread);
		return ;
	}
	while (i--)
		pthread_join(thread[i], NULL);
	pthread_join(time, NULL);
}

int	check_atoi(const char *str)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (INT_MAX / 10 < ret
			|| (ret == INT_MAX / 10 && INT_MAX % 10 < str[i] - '0'))
		{
			printf("Number too large.\n");
			return (-1);
		}
		ret = ret * 10 + str[i++] - '0';
	}
	if (str[i] || ret == 0)
	{
		printf("Number must be valid and positive.\n");
		return (-1);
	}
	return (ret);
}
