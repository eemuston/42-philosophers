/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:47:25 by eemuston          #+#    #+#             */
/*   Updated: 2023/06/07 13:21:51 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	join_threads(t_args	*arg, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(arg->philos[i].thread, NULL);
		i++;
	}
}

void	free_all(t_args *arg)
{
	int	i;

	i = 0;
	while (i < arg->philo_num)
	{
		pthread_mutex_destroy(&arg->forks[i]);
		pthread_mutex_destroy(&arg->philos[i].p);
		i++;
	}
	pthread_mutex_destroy(&arg->sim);
	pthread_mutex_destroy(&arg->start_mutex);
	pthread_mutex_destroy(&arg->alive_mutex);
	free(arg->forks);
	free(arg->philos);
	return ;
}

void	init_args(t_args *arg, int argc, char **argv)
{
	arg->philo_num = ft_atoi(argv[1]);
	arg->to_die = ft_atoi(argv[2]);
	arg->to_eat = ft_atoi(argv[3]);
	arg->to_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&arg->sim, NULL);
	pthread_mutex_init(&arg->alive_mutex, NULL);
	pthread_mutex_init(&arg->start_mutex, NULL);
	arg->ready = 0;
	arg->alive = 0;
	arg->starting_time = get_timestamp();
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
	if (init_forks(&arg) == -1)
		return ;
	if (init_philos(&arg) == -1)
		return ;
	if (init_thread(&arg) == -1)
		return ;
	monitoring(&arg);
	join_threads(&arg, arg.philo_num);
	free_all(&arg);
}

int	main(int argc, char **argv)
{	
	if (error_check(argc, argv) != 0)
		return (-1);
	init_all(argc, argv);
	return (0);
}
