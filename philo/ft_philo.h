/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:59:32 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/20 17:44:39 by owatanab         ###   ########.fr       */
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
	int			id;
	long long	now;
	long long	last_meal;
	int			after_sleep;
}	t_info;

void		*routine(void *philo);
void		load_status(t_info *info, t_philo *philo, int fork_num);
void		put_down_fork(t_philo *philo, int id);
void		wait_mseconds(t_info *info, t_philo *philo, int msec);
void		next_time(t_philo *philo, t_info *info);
long long	timestamp(t_philo *philo);
int			get_fork(t_philo *philo, t_info *info);
void		philo_usleep(t_philo *philo, int usec);

#endif