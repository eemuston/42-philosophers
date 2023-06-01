/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:49:46 by eemuston          #+#    #+#             */
/*   Updated: 2023/05/31 11:27:01 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_philo(t_philo *philo)
{
	message(philo, "has taken a fork", get_time(philo));
	ft_usleep(philo->arg->to_die / 1000);
	message(philo, "died", get_time(philo));	
	return (0);
}