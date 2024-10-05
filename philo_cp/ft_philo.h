/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:20:11 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/03 16:36:41 by otawatanabe      ###   ########.fr       */
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
	int				exit;
	int				finish_eat;
	u_int64_t		*last_meal;
	u_int64_t		start;
	pthread_t		*thread;
	pthread_mutex_t	*time_mutex;
	pthread_mutex_t	exit_mutex;
	pthread_mutex_t	id_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	*fork_mutex;
}	t_philo;

typedef struct s_info
{
	int			id;
	u_int64_t	now;
	u_int64_t	last_meal;
	int			after_sleep;
	int			fork_count;
	int			eat_count;
}	t_info;

void		assign_exit(t_philo *philo);
int			check_atoi(char *str);
void		check_die_update(t_philo *philo, int id, int if_time_update);
int			check_exit(t_philo *philo);
void		check_usleep(t_philo *philo, int usec);
void		clean_up(t_philo *philo);
void		destroy_array_mutex(pthread_mutex_t *mutex, int num);
void		free_philo(t_philo *philo);
void		join_all(t_philo *philo, pthread_t supervise_thread);
int			get_input(t_philo *philo, int argc, char *argv[]);
int			malloc_philo(t_philo *philo);
int			mutex_array_init(pthread_mutex_t *mutex_array, int num);
int			philo_array_init(t_philo *philo);
void		philo_eat(t_philo *philo, int *eat_count, int id);
int			philo_init(t_philo *philo, int argc, char *argv[]);
int			philo_mutex_init(t_philo *philo);
void		print_action(t_philo *philo, int id, char *action);
void		print_error(t_philo *philo, char *error, int if_lock);
void		*routine(void *ptr);
int			start_simulation(t_philo *philo, pthread_t *supervise_thread);
void		*supervise(void *ptr);
u_int64_t	timestamp(t_philo *philo, int if_lock);
void		wait_till(t_philo *philo, u_int64_t time);

#endif