/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:59:32 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/09/30 17:22:30 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>

typedef struct s_philo
{
	int				exit;
	int				id;
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	long long		last_meal;
	long long		start;
	sem_t			*sem_eat;
	sem_t			*sem_fork;
	sem_t			*sem_kill;
	sem_t			*sem_permission;
	sem_t			*sem_print;
	sem_t			*sem_exit;
}	t_philo;

typedef struct s_info
{
	int			id;
	long long	now;
	long long	last_meal;
	int			after_sleep;
	int			fork_count;
	int			eat_count;
}	t_info;

int			check_atoi(const char *str);
int			count_size(int n);
void		die_exit(t_philo *philo, int id);
void		*eat_count(void *ptr);
char		*get_sem_name(int n);
void		make_process(t_philo *philo);
int			philo_init(t_philo *philo, int argc, char *argv[]);
void		philo_process(t_philo *philo, int id);
void		print_action(t_philo *philo, int id, char *action);
void		print_error(t_philo *philo, char *error);
void		print_fork(t_philo *philo, int id);
void		*routine(void *ptr);
void		sem_check_destroy(sem_t *sem, char *str);
int			sem_init_all(t_philo *philo);
long long	timestamp(t_philo *philo);
void		wait_msec(t_philo *philo, int msec, int id);

#endif