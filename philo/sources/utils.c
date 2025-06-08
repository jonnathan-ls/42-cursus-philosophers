/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/08 16:31:43 by jlacerda         ###   ########.fr       */
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

int	is_valid_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (FALSE);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '+')
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

void	exit_with_error(char	*msg, t_table *table)
{
	if (msg)
		printf(COLOR_RED "%s" COLOR_RESET, msg);
	free_resources(table);
	exit(EXIT_FAILURE);
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
		{
			pthread_mutex_destroy(&table->forks[index]);
			pthread_mutex_destroy(&table->philos[index].meal_mutex);
		}
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

char	*get_status_message(t_status status)
{
	char	*messages[6];
	
	messages[TAKEN_FORKS] = " 🍴 has taken a fork";
	messages[DEAD] = COLOR_RED " 💀 DIED" COLOR_RESET;
	messages[TIMESTAMP] = COLOR_CYAN "⏳ %ld" COLOR_RESET;
	messages[PHILO_ID] = COLOR_MAGENTA " 👤 %d" COLOR_RESET;
	messages[EATING] = COLOR_GREEN " 🍝 is eating" COLOR_RESET;
	messages[SLEEPING] = COLOR_BLUE " 🛌 is sleeping" COLOR_RESET;
	messages[THINKING] = COLOR_YELLOW " 💭 is thinking" COLOR_RESET;
	if (!CSS)
	{
		messages[DEAD] = " died";
		messages[PHILO_ID] = " %d";
		messages[TIMESTAMP] = "%ld";
		messages[EATING] = " is eating";
		messages[THINKING] = " is thinking";
		messages[SLEEPING] = " is sleeping";
		messages[TAKEN_FORKS] = " has taken a fork";
	}
	return	(messages[status]);
}
