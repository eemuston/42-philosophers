/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:47:25 by eemuston          #+#    #+#             */
/*   Updated: 2023/05/30 19:04:27 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(t_philo *philo)
{
	return (get_timestamp() - philo->arg->starting_time);
}

void	join_threads(t_args	*arg)
{
	int	i;

	i = 0;
	while (i < arg->philo_num)
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
		pthread_mutex_destroy(arg->forks);
		i++;
	}
	pthread_mutex_destroy(&arg->sim);
	free(arg->forks);
	free(arg->philos);
	exit(0);
}

int	main(int argc, char **argv)
{	
	if (error_check(argc, argv) != 0)
		return (-1);
	init_all(argc, argv);
	return (0);
}
