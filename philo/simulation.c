/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:06:02 by eemuston          #+#    #+#             */
/*   Updated: 2023/06/23 12:34:00 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleeping(t_philo *philo)
{
	if (message(philo, "is sleeping", get_time(philo)) == -1)
		return (-1);
	ft_usleep(philo, philo->arg->to_sleep);
	return (0);
}

int	eating_checks(t_philo *philo)
{
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
	ft_usleep(philo, philo->arg->to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
	if (eating_checks(philo) == -1)
		return (-1);
	return (0);
}

int	simulation(t_philo *philo)
{
	message(philo, "is thinking", get_time(philo));
	if (philo->arg->philo_num == 1)
		return (one_philo(philo));
	if (philo->num % 2 == 0)
		ft_usleep(philo, (philo->arg->to_eat) / 2);
	while (1)
	{
		if (take_forks(philo) == -1)
			return (0);
		if (sleeping(philo) == -1)
			return (0);
		if (message(philo, "is thinking", get_time(philo)) == -1)
			return (0);
	}
	return (0);
}

void	*start_simulation(void *args)
{
	t_philo			*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->arg->start_mutex);
	pthread_mutex_unlock(&philo->arg->start_mutex);
	simulation(philo);
	return (args);
}
