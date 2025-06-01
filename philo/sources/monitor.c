/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 17:00:57 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

static t_bool	philo_is_dead(t_philo *philo, t_table *table)
{
	uint64_t	time_since_last_meal;

	pthread_mutex_lock(&table->philo_mutex);
	time_since_last_meal = get_current_time_in_ms() - philo->last_meal_time;
	if (time_since_last_meal > table->time_to_die)
	{
		philo->is_dead = TRUE;
		table->simulation_running = FALSE;
		pthread_mutex_unlock(&table->philo_mutex);
		print_status(philo, DEAD);
		return (TRUE);
	}
	pthread_mutex_unlock(&table->philo_mutex);
	return (FALSE);
}

static t_bool	philo_is_satisfied(t_philo *philo, t_table *table)
{
	t_bool	should_stop;

	pthread_mutex_lock(&table->philo_mutex);
	should_stop = philo->meals_eaten >= table->meals_required;
	if (table->meals_required > 0 && should_stop)
	{
		pthread_mutex_unlock(&table->philo_mutex);
		stop_simulation(table);
		return (TRUE);
	}
	pthread_mutex_unlock(&table->philo_mutex);
	return (FALSE);
}

void	*monitor(void *arg)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (should_continue(table))
	{
		if (philo_is_dead(philo, table))
			return (NULL);
		if (philo_is_satisfied(philo, table))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
