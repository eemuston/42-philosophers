/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:43:27 by eemuston          #+#    #+#             */
/*   Updated: 2023/04/25 22:58:12 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	only_nums(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	error_message(void)
{
	write(2, "Usage ./philo [Number of philosophers] [time to die]", 53);
	write(2, " [time to eat] [time to sleep] ", 32);
	write(2, "[number of times each philosopher must eat]\n", 45);
	return (-1);
}

int	error_check(int argc, char **argv)
{
	if (only_nums(argc, argv) != 0)
		return (error_message());
	if (argc != 6 && argc != 5)
		return (error_message());
	return (0);
}
