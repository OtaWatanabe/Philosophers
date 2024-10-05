/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:16:27 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/02 13:47:41 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

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
