/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:06:27 by eemuston          #+#    #+#             */
/*   Updated: 2023/06/07 14:59:28 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_thread(t_args *arg)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&arg->start_mutex);
	while (++i < arg->philo_num)
	{
		if (pthread_create(&arg->philos[i].thread, NULL, \
			&start_simulation, &(arg->philos[i])) != 0)
		{
			join_threads(arg, i);
			free_all(arg);
			return (-1);
		}
	}
	i = -1;
	arg->starting_time = get_timestamp();
	pthread_mutex_unlock(&arg->start_mutex);
	while (++i < arg->philo_num)
			arg->philos[i].last_eaten = arg->starting_time;
	return (0);
}

int	init_philos(t_args *arg)
{
	int	i;

	i = 0;
	arg->philos = malloc(sizeof(t_philo) * arg->philo_num);
	if (!arg->philos)
		return (-1);
	while (i < arg->philo_num)
	{
		arg->philos[i].num = i + 1;
		arg->philos[i].right_fork = &arg->forks[i];
		arg->philos[i].arg = arg;
		arg->philos[i].times_eaten = 0;
		arg->philos[i].last_eaten = arg->starting_time;
		pthread_mutex_init(&arg->philos[i].p, NULL);
		if (i == 0)
			arg->philos[i].left_fork = &arg->forks[arg->philo_num - 1];
		else
			arg->philos[i].left_fork = &arg->forks[i - 1];
		i++;
	}
	return (0);
}

int	init_forks(t_args *arg)
{
	int	i;

	i = 0;
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!arg->forks)
		return (-1);
	while (i < arg->philo_num)
	{
		pthread_mutex_init(&arg->forks[i], NULL);
		i++;
	}
	return (0);
}
