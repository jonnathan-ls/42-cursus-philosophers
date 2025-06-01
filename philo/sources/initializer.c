/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/07 21:01:29 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table)
{
	table->forks = NULL;
	table->philos = NULL;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->meals_required = -1;
	table->num_philosophers = 0;
	table->dinner_in_progress = TRUE;
	table->start_dinner_time = get_current_time_in_ms();
}

void	init_args(t_table *table, int argc, char **argv)
{
	table->num_philosophers = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->meals_required = ft_atol(argv[5]);
	else
		table->meals_required = -1;
}

void	init_philos(t_table *table)
{
	t_philo	*philo;
	int		index_fork;
	int		index_philo;

	index_philo = -1;
	while (++index_philo < table->num_philosophers)
	{
		philo = table->philos + index_philo;
		philo->table = table;
		philo->thread_id = -1;
		philo->meals_eaten = 0;
		philo->last_meal_time = table->start_dinner_time;
		philo->id = index_philo + 1;
		philo->right_fork = &table->forks[index_philo];
		index_fork = (index_philo + 1) % table->num_philosophers;
		philo->left_fork = &table->forks[index_fork];
	}
}
