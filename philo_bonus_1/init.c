/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:43:21 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/03 15:56:02 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	philo_init(t_philo *philo, int argc, char *argv[])
{
	memset(philo, 0, sizeof(t_philo));
	if (get_input(philo, argc, argv) == -1)
		return (-1);
	return (philo_sem_init(philo));
}

int	philo_sem_init(t_philo *philo)
{
	sem_unlink("fork");
	sem_unlink("permission");
	sem_unlink("print");
	sem_unlink("eat");
	sem_unlink("kill");
	philo->sem_fork = sem_open("fork",
			O_CREAT | O_EXCL, 0644, philo->philo_num);
	philo->sem_permission = sem_open("permission",
			O_CREAT | O_EXCL, 0644, (philo->philo_num + 1) / 2);
	philo->sem_print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	philo->sem_eat = sem_open("eat", O_CREAT | O_EXCL, 0644, 0);
	philo->sem_kill = sem_open("kill", O_CREAT | O_EXCL, 0644, 0);
	if (philo->sem_fork && philo->sem_permission
		&& philo->sem_print && philo->sem_eat && philo->sem_kill)
		return (0);
	printf("sem_open error\n");
	clean_up(philo);
	return (-1);
}

int	get_input(t_philo *philo, int argc, char *argv[])
{
	if (argc < 5 || 6 < argc)
	{
		printf("The number of arguments must be 4 or 5.\n");
		return (-1);
	}
	philo->philo_num = check_atoi(argv[1]);
	if (philo->philo_num == -1)
		return (-1);
	if (100000 < philo->philo_num)
	{
		printf("Too many philosophers\n");
		return (-1);
	}
	philo->time_die = check_atoi(argv[2]);
	if (philo->time_die == -1)
		return (-1);
	philo->time_eat = check_atoi(argv[3]);
	if (philo->time_eat == -1)
		return (-1);
	philo->time_sleep = check_atoi(argv[4]);
	if (philo->time_sleep == -1)
		return (-1);
	if (argc == 6)
		philo->must_eat = check_atoi(argv[5]);
	if (philo->must_eat == -1)
		return (-1);
	return (0);
}

int	check_atoi(char *str)
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
