/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 23:01:51 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/30 17:37:07 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	sem_check_destroy(sem_t *sem, char *str)
{
	if (sem != NULL)
	{
		sem_close(sem);
		sem_unlink(str);
	}
}

int	sem_init_all(t_philo *philo)
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
	sem_check_destroy(philo->sem_fork, "fork");
	sem_check_destroy(philo->sem_permission, "permission");
	sem_check_destroy(philo->sem_print, "print");
	sem_check_destroy(philo->sem_eat, "eat");
	sem_check_destroy(philo->sem_kill, "kill");
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
	philo->start = timestamp(philo);
	return (sem_init_all(philo));
}

void	make_process(t_philo *philo)
{
	pid_t		p;
	int			i;
	pthread_t	thread;

	i = 0;
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
