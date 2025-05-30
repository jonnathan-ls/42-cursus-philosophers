/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/05/26 22:01:38 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table	*table)
{
	while (!get_bool(&table->ready_mutex, &table->all_threads_ready_created))
		;
}

void *simulates_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);

	while (!is_simulation_finished(philo->table))
	{
		if (philo->is_satisfied)
			break ;
		if (philo->meals_eaten >= philo->table->amount_limit_meals)
		{
			set_bool(&philo->table->ready_mutex, &philo->is_satisfied, TRUE);
			return (NULL);
		}
		// Simulate eating, sleeping, thinking, etc.
		// This is where the philosopher's logic would go.
	}

}

void	start_dinner(t_table *table)
{
	int index;

	index	= -1;
	if (table->amount_limit_meals)
		return ;
	else if (table->amount_limit_meals == 1)
	{
		// TODO
	}
	else
	{
		while (++index < table->amount_philos)
		{
			safe_thread(CREATE,
					&table->philos[index].thread_id, simulates_dinner, table);
		}
	}
	table->start_dinner_time = get_current_time_in_ms();
	set_bool(&table->ready_mutex, &table->all_threads_ready_created, TRUE);
	index = -1;
	while (++index < table->amount_philos)
		safe_thread(JOIN, &table->philos[index].thread_id, NULL, table);

}