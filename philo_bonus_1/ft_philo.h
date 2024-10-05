/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:41:33 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/05 14:11:12 by otawatanabe      ###   ########.fr       */
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
	int			exit;
	int			id;
	int			philo_num;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			must_eat;
	u_int64_t	last_meal;
	u_int64_t	start;
	sem_t		*sem_eat;
	sem_t		*sem_fork;
	sem_t		*sem_kill;
	sem_t		*sem_permission;
	sem_t		*sem_print;
	sem_t		*sem_time;
}	t_philo;

int		check_atoi(char *str);
void	clean_up(t_philo *philo);
int	count_size(int n);
void	*eat_count(void *ptr);
int	get_input(t_philo *philo, int argc, char *argv[]);
char	*get_sem_name(int n);
void	make_process(t_philo *philo);
void	philo_eat(t_philo *philo, int *eat_count);
int		philo_init(t_philo *philo, int argc, char *argv[]);
void	philo_process(t_philo *philo, int id);
int	philo_sem_init(t_philo *philo);
void	print_action(t_philo *philo, char *action);
void	print_error(t_philo *philo, char *error, int if_wait);
void	*routine(void *ptr);
void	sem_check_destroy(sem_t *sem, char *str);
void	start_routine(t_philo *philo, int id, pthread_t *thread);
u_int64_t	timestamp(t_philo *philo, int if_wait);
void	wait_till(t_philo *philo, u_int64_t time);

#endif