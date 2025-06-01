/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 16:25:06 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

void	free_resources(t_table *table)
{
	int	index;

	if (!table)
		return ;
	if (table->forks)
	{
		index = -1;
		while (++index < table->num_philosophers)
			pthread_mutex_destroy(&table->forks[index]);
		free(table->forks);
		table->forks = NULL;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->philo_mutex);
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}

void	exit_with_error(char	*msg, t_table *table)
{
	if (msg)
		printf(COLOR_RED "%s" COLOR_RESET, msg);
	free_resources(table);
	exit(EXIT_FAILURE);
}
