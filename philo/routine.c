/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:36:05 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/25 11:26:44 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// void	get_fork(t_philo *philo, t_info *info)
// {
// 	if (philo->exit)
// 		return ;
// 	pthread_mutex_lock(philo->fork_mutex + philo->id - 1);
// 	pthread_mutex_lock(philo->fork_mutex + philo->id % philo->philo_num);
// 	if (philo->fork_count[info->id - 1] <= info->now)
// 	{
// 		print_fork(philo, info);
// 		++philo->fork_count[info->id - 1];
// 	}
// 	if (info->id == philo->philo_num && philo->fork_count[0] <= info->now)
// 	{
// 		print_fork(philo, info);
// 		++philo->fork_count[info->id - 1];
// 	}
// 	else if (info->id != philo->philo_num && philo->fork_count[info->id] <= info->now)
// 	{
// 		print_fork(philo, info);
// 		++philo->fork_count[info->id];
// 	}
// 	pthread_mutex_unlock(philo->fork_mutex + philo->id - 1);
// 	pthread_mutex_unlock(philo->fork_mutex + philo->id % philo->philo_num);
// }

void	set_eat_time(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(philo->fork_mutex + info->id - 1);
	pthread_mutex_lock(philo->fork_mutex + info->id % philo->philo_num);
	philo->fork_count[info->id - 1] = info->now + philo->time_eat;
	philo->fork_count[info->id % philo->philo_num] = info->now + philo->time_eat;
	pthread_mutex_unlock(philo->fork_mutex + info->id - 1);
	pthread_mutex_unlock(philo->fork_mutex + info->id % philo->philo_num);
	info->last_meal = info->now;
}

void	load_status(t_info *info, t_philo *philo)
{
	int	n;
	
	n = philo->fork_count[info->id - 1] - info->fork_count;
	info->fork_count += n;
	print_fork(philo, info, n);
	if (info->after_sleep && info->fork_count < 2)
	{
		info->after_sleep = 0;
		print_action(philo, info, "thinking");
	}
	if (info->fork_count < 2)
		return ;
	print_action(philo, info, "eating");
	info->last_meal = info->now;
	wait_mseconds(info, philo, philo->time_eat);
	pthread_mutex_lock(&philo->fork_mutex[(info->id + philo->philo_num - 2) % philo->philo_num]);
	++philo->fork_count[(info->id + philo->philo_num - 2) % philo->philo_num];
	pthread_mutex_unlock(&philo->fork_mutex[(info->id + philo->philo_num - 2) % philo->philo_num]);
	pthread_mutex_lock(&philo->fork_mutex[info->id % philo->philo_num]);
	++philo->fork_count[info->id % philo->philo_num];
	pthread_mutex_unlock(&philo->fork_mutex[info->id % philo->philo_num]);
	philo->fork_count[info->id - 1] = 0;
	print_action(philo, info, "sleeping");
	wait_mseconds(info, philo, philo->time_sleep);
	info->after_sleep = 1;
}

void	print_time(int id)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	printf("%d: time: %ld\n", id, tv.tv_sec * 1000000 + tv.tv_usec);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->id_mutex);
	info.id = ++philo->id;
	pthread_mutex_unlock(&philo->id_mutex);
	info.now = philo->start;
	info.last_meal = info.now;
	init_routine(philo, &info);
	while (philo->exit == 0)
	{
		// print_time(info.id);
		if (philo->fork_count[info.id - 1] < 2)
			philo_usleep(philo, 500);
		if (info.fork_count != philo->fork_count[info.id - 1] || info.after_sleep)
			load_status(&info, philo);
		else
			next_time(philo, &info);
		// printf("time: %lld fork: %d id: %d\n", info.now, philo->fork_count[info.id - 1], info.id);
	}
	return (NULL);
}
