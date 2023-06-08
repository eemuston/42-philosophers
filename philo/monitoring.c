/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:19:23 by eemuston          #+#    #+#             */
/*   Updated: 2023/06/07 11:15:14 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_args *arg, int i)
{
	pthread_mutex_lock(&arg->philos[i].p);
	if (get_timestamp() - arg->philos[i].last_eaten >= arg->to_die)
	{
		pthread_mutex_lock(&arg->alive_mutex);
		arg->alive = 1;
		pthread_mutex_unlock(&arg->alive_mutex);
		printf("%lld %d died\n", \
			get_timestamp() - arg->starting_time, i + 1);
		pthread_mutex_unlock(&arg->philos[i].p);
		return (1);
	}
	pthread_mutex_unlock(&arg->philos[i].p);
	return (0);
}

int	monitoring(t_args *arg)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < arg->philo_num)
		{
			if (arg->philo_num == 1)
				return (0);
			pthread_mutex_lock(&arg->sim);
			if (arg->ready >= arg->philo_num)
			{
				pthread_mutex_unlock(&arg->sim);
				return (0);
			}
			pthread_mutex_unlock(&arg->sim);
			if (check_death(arg, i) == 1)
				return (0);
			i++;
		}
		usleep(500);
	}
}
