/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:06:02 by eemuston          #+#    #+#             */
/*   Updated: 2023/06/01 15:05:49 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleeping(t_philo *philo)
{
	if (message(philo, "is sleeping", get_time(philo)) == -1)
		return (-1);
	ft_usleep(philo->arg->to_sleep / 1000);
	return (0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (message(philo, "has taken a fork", get_time(philo)) == -1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	pthread_mutex_lock(philo->left_fork);
	if (message(philo, "has taken a fork", get_time(philo)) == -1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	if (message(philo, "is eating", get_time(philo)) == -1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	philo->times_eaten++;
	pthread_mutex_lock(&philo->arg->sim);
	if (philo->times_eaten == philo->arg->must_eat)
		philo->arg->ready++;
	if (philo->arg->ready == philo->arg->philo_num)
	{
		pthread_mutex_unlock(&philo->arg->sim);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	pthread_mutex_unlock(&philo->arg->sim);
	pthread_mutex_lock(&philo->p);
	philo->last_eaten = get_timestamp();
	pthread_mutex_unlock(&philo->p);
	ft_usleep(philo->arg->to_eat / 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	simulation(t_philo *philo)
{
	// printf("%d Starting time: %lld\n", philo->num, get_time(philo));
	message(philo, GREEN"is thinking"WHITE, get_time(philo));
	// printf(GREEN"%lld %d is thinking\n"WHITE, get_timestamp() - philo->arg->starting_time, philo->num);
	if (philo->arg->philo_num == 1)
		return (one_philo(philo));
	if (philo->num % 2 == 0)
		ft_usleep((philo->arg->to_eat / 1000) / 2);
	while (1)
	{
		if (take_forks(philo) == -1)
			return (0);
		if (sleeping(philo) == -1)
			return (0);
		if(message(philo, "is thinking", get_time(philo)) == -1)
			return (0);
	}
	return (0);
}

void	*start_simulation(void *args)
{
	t_philo			*philo;

	philo = (t_philo *)args;
	message(philo, YELLOW"waiting for mutex"WHITE, get_time(philo));
	pthread_mutex_lock(&philo->arg->start_mutex);
	pthread_mutex_unlock(&philo->arg->start_mutex);
	// printf(YELLOW"%llu %d waiting for mutex\n"WHITE, get_timestamp() - philo->arg->starting_time, philo->num);
	message(philo, RED"has passed the mutex"WHITE, get_time(philo));
	// printf(RED"%llu %d has passed the mutex\n"WHITE, get_timestamp() - philo->arg->starting_time, philo->num);
	simulation(philo);
	return (args);
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
			pthread_mutex_lock(&arg->philos[i].p);
			if (get_timestamp() - arg->philos[i].last_eaten >= arg->to_die / 1000)
			{
				pthread_mutex_lock(&arg->alive_mutex);
				arg->alive = 1;
				pthread_mutex_unlock(&arg->alive_mutex);
				printf("%lld %d died\n", \
					get_timestamp() - arg->starting_time, i + 1);
				pthread_mutex_unlock(&arg->philos[i].p);
				return (0);
			}
			pthread_mutex_unlock(&arg->philos[i].p);
			i++;
		}
		usleep(500);
	}
}
