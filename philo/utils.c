/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:01:29 by eemuston          #+#    #+#             */
/*   Updated: 2023/05/31 16:57:42 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	long_result(int s)
{
	if (s == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *n)
{
	unsigned long long	r;
	int					s;
	int					i;

	r = 0;
	s = 1;
	i = 0;
	while ((n[0] >= 9 && n[0] <= 13) || n[0] == 32)
		n++;
	if (n[0] == 45)
		s *= -1;
	if (n[0] == 45 || n[0] == 43)
		n++;
	while (n[0] == '0')
		n++;
	while (n[i] >= 48 && n[i] <= 57 && n[i] != '\0')
		r = r * 10 + n[i++] - 48;
	if (i > 19 || r >= 9223372036854775808ULL)
		return (long_result(s));
	return (r * s);
}

long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long ms)
{
	long long	end;

	end = get_timestamp() + ms;
	while (get_timestamp() < end)
		usleep(ms / 1000);
}

int	message(t_philo *philo, char *action, long long time)
{
	time = 0;
	pthread_mutex_lock(&philo->arg->alive_mutex);
	if (philo->arg->alive == 1)
	{
		pthread_mutex_unlock(&philo->arg->alive_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->arg->alive_mutex);
	pthread_mutex_lock(&philo->arg->sim);
	printf("%lld %d %s\n", get_timestamp() - philo->arg->starting_time, philo->num, action);
	pthread_mutex_unlock(&philo->arg->sim);
	return (0);
}
