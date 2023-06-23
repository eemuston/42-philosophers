/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:42:02 by eemuston          #+#    #+#             */
/*   Updated: 2023/06/23 12:32:57 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				num;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				times_eaten;
	long long		last_eaten;
	struct s_args	*arg;
	pthread_mutex_t	p;
}				t_philo;

typedef struct s_args
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	sim;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	alive_mutex;
	t_philo			*philos;
	long long		starting_time;
	int				philo_num;
	long long		to_die;
	long long		to_eat;
	long long		to_sleep;
	int				must_eat;
	int				ready;
	int				alive;
	int				which;
}				t_args;

int			error_check(int argc, char **argv);
int			only_nums(int argc, char **argv);
int			error_message(void);
int			ft_atoi(const char *n);
void		init_all(int argc, char **argv);
void		*start_simulation(void *arg);
void		init_args(t_args *arg, int argc, char **argv);
long long	get_timestamp(void);
int			ft_usleep(t_philo *philo, long long ms);
int			init_forks(t_args *arg);
int			init_thread(t_args *arg);
int			init_philos(t_args *arg);
int			simulation(t_philo *philo);
int			take_forks(t_philo *philo);
int			sleeping(t_philo *philo);
int			message(t_philo *philo, char *action, long long time);
long long	get_time(t_philo *philo);
int			monitoring(t_args *arg);
void		join_threads(t_args	*arg, int n);
void		free_all(t_args *arg);
int			one_philo(t_philo *philo);
int			check_death(t_args *arg, int i);
int			eating_checks(t_philo *philo);
int			good_nums(int argc, char **argv);

#endif