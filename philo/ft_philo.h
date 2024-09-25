/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:59:32 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/25 11:30:01 by otawatanabe      ###   ########.fr       */
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
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				*fork_count;
	int				exit;
	long long		start;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	id_mutex;
	pthread_mutex_t	*fork_mutex;
}	t_philo;

typedef struct s_info
{
	int			id;
	long long	now;
	long long	last_meal;
	int			after_sleep;
	int			fork_count;
	int			first;
}	t_info;

void		*routine(void *philo);
void		load_status(t_info *info, t_philo *philo);
void		set_eat_time(t_philo *philo, t_info *info);
void		wait_mseconds(t_info *info, t_philo *philo, int msec);
void		next_time(t_philo *philo, t_info *info);
long long	timestamp(t_philo *philo);
void		get_fork(t_philo *philo, t_info *info);
void		philo_usleep(t_philo *philo, int usec);
void		print_fork(t_philo *philo, t_info *info, int n);
void		print_action(t_philo *philo, t_info *info, char *action);
void		print_death(t_philo *philo, t_info *info);
void		print_error(t_philo *philo, char *error);
void		wait_start(t_philo *philo, int id);
int			set_fork(t_philo *philo);
void		init_routine(t_philo *philo, t_info *info);

#endif