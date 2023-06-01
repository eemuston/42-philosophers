/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:06:27 by eemuston          #+#    #+#             */
/*   Updated: 2023/06/01 15:09:54 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_thread(t_args *arg)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&arg->start_mutex);
	while (++i < arg->philo_num)
	{
		pthread_create(&arg->philos[i].thread, NULL, \
			&start_simulation, &(arg->philos[i]));
	}
	i = -1;
	arg->starting_time = get_timestamp();
	printf("starting_time = %llu\n", arg->starting_time);
	while(++i < arg->philo_num)		
	{
		arg->philos[i].last_eaten = arg->starting_time;
	}
	printf(CYAN"Main thread unlocking mutex\n"WHITE);
	pthread_mutex_unlock(&arg->start_mutex);
	printf(CYAN"Mutex unlocked\n"WHITE);
}

void	init_philos(t_args *arg)
{
	int	i;

	i = 0;
	arg->philos = calloc(sizeof(t_philo), arg->philo_num);
	while (i < arg->philo_num)
	{
		arg->philos[i].num = i + 1;
		arg->philos[i].right_fork = &arg->forks[i];
		arg->philos[i].arg = arg;
		arg->philos[i].times_eaten = 0;
		pthread_mutex_init(&arg->philos[i].p, NULL);
		if (i == 0)
			arg->philos[i].left_fork = &arg->forks[arg->philo_num - 1];
		else
			arg->philos[i].left_fork = &arg->forks[i - 1];
		i++;
	}
}

void	init_forks(t_args *arg)
{
	int	i;

	i = 0;
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	while (i < arg->philo_num)
	{
		pthread_mutex_init(&arg->forks[i], NULL);
		i++;
	}
}

void	init_args(t_args *arg, int argc, char **argv)
{
	arg->philo_num = ft_atoi(argv[1]);
	arg->to_die = 1000 * ft_atoi(argv[2]);
	arg->to_eat = 1000 * ft_atoi(argv[3]);
	arg->to_sleep = 1000 * ft_atoi(argv[4]);
	pthread_mutex_init(&arg->sim, NULL);
	pthread_mutex_init(&arg->alive_mutex, NULL);
	pthread_mutex_init(&arg->start_mutex, NULL);
	arg->ready = 0;
	arg->alive = 0;
	arg->which = 0;
	if (argc == 6)
		arg->must_eat = ft_atoi(argv[5]);
	else
		arg->must_eat = -1;
}

void	init_all(int argc, char **argv)
{
	t_args	arg;

	init_args(&arg, argc, argv);
	init_forks(&arg);
	init_philos(&arg);
	init_thread(&arg);
	monitoring(&arg);
	join_threads(&arg);
	free_all(&arg);
}
