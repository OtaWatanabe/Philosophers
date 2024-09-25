/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:59:00 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/25 10:10:22 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	j;
	int				k;

	i = 1;
	j = 0;
	k = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		i -= *str++ - '+';
	while (*str == 0)
		str++;
	while (str[k] <= '9' && str[k] >= '0')
	{
		if ((j > 922337203685477580) || (j == 922337203685477580 && ((i == 1
						&& str[k] > '7') || (i == -1 && str[k] > '8'))))
			return ((-i - 1) / 2);
		j *= 10;
		j += str[k++] - '0';
	}
	return ((int)j * i);
}

int	if_number(char *str)
{
	if (*str == '\0' || (*str == '0' && str[1] != '\0'))
		return (-1);
	if (*str == '-')
	{
		++str;
		if (*str == '0' || *str == '\0')
			return (-1);
	}
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			return (-1);
		++str;
	}
	return (0);
}

int	too_large(char *str)
{
	int	n;

	n = 0;
	while (*str)
	{
		if (INT_MAX / 10 < n)
			return (-1);
		if (n == INT_MAX / 10)
		{
			if (INT_MAX % 10 < *str - '0')
				return (-1);
		}
		n = n * 10 + (*str - '0');
		++str;
	}
	return (0);
}

int	check_arg(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || 6 < argc)
	{
		printf("The number of arguments must be 4 or 5.\n");
		return (-1);
	}
	i = 1;
	while (i < argc)
	{
		if (if_number(argv[i]) == -1)
		{
			printf("Arguments must be valid numbers.\n");
			return (-1);
		}
		if (argv[i][0] == '-')
		{
			printf("Arguments must not be negative.\n");
			return (-1);
		}
		if (too_large(argv[i]))
		{
			printf("Too large an argument.\n");
			return (-1);
		}
		++i;
	}
	return (0);
}

int	philo_init(t_philo *philo, int argc, char *argv[])
{
	if (check_arg(argc, argv) == -1)
		return (-1);
	philo->philo_num = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->must_eat = ft_atoi(argv[5]);
	if (pthread_mutex_init(&philo->id_mutex, NULL) != 0 || pthread_mutex_init(&philo->print_mutex, NULL) != 0)
	{
		printf("mutex init error\n");
		return (-1);
	}
	philo->id = 0;
	philo->exit = 0;
	return (set_fork(philo));
}

int	set_fork(t_philo *philo)
{
	int	i;

	philo->fork_count = malloc(sizeof(int) * philo->philo_num);
	philo->fork_mutex = malloc(sizeof(pthread_mutex_t) * philo->philo_num);
	if (philo->fork_count == NULL || philo->fork_mutex == NULL)
	{
		free(philo->fork_count);
		free(philo->fork_mutex);
		return (-1);
	}
	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_mutex_init(philo->fork_mutex + i, NULL) == -1)
		{
			printf("mutex init error\n");
			free(philo->fork_count);
			free(philo->fork_mutex);
			return (-1);
		}
		++i;
	}
	memset(philo->fork_count, 0, philo->philo_num);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo		philo;
	pthread_t	*thread;
	int			i;
	
	if (philo_init(&philo, argc, argv) == -1)
		return (1);
	thread = malloc(sizeof(pthread_t) * philo.philo_num);
	if (thread == NULL)
		return (1);
	philo.start = timestamp(&philo) + 10;
	i = 0;
	while (i < philo.philo_num)
	{
		pthread_create(thread + i, NULL, routine, (void *)&philo);
		++i;
	}
	i = 0;
	while (i < philo.philo_num)
	{
		pthread_join(thread[i], NULL);
		++i;
	}
	free(thread);
	free(philo.fork_count);
	free(philo.fork_mutex);
}
