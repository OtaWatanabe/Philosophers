/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:59:32 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/19 17:29:05 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# define INT_MAX 2147483647

typedef struct s_philo
{
	int				id;
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				*fork_status;
	int				exit;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_info
{
	int				id;
	struct timeval	now;
	struct timeval	last_meal;
	int				status;
}	t_info;

void	*routine(void *philo);
int		next_time(t_philo *philo);

#endif