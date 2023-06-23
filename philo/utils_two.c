/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:49:46 by eemuston          #+#    #+#             */
/*   Updated: 2023/06/23 12:33:31 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_philo(t_philo *philo)
{
	message(philo, "has taken a fork", get_time(philo));
	ft_usleep(philo, philo->arg->to_die);
	message(philo, "died", get_time(philo));
	return (0);
}

long long	get_time(t_philo *philo)
{
	return (get_timestamp() - philo->arg->starting_time);
}
