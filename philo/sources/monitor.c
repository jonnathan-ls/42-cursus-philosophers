/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/13 23:20:02 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if a philosopher has died 
 * by comparing the time since their last meal with the time to die.
 * If the philosopher has died, it stops the simulation,
 * prints the death status, and frees resources.
 * @param philo Pointer to the philosopher struct.
 * @param table Pointer to the table struct containing the philosophers.
 * @return TRUE if the simulation should continue, FALSE otherwise.
 */
static t_bool	philo_died(t_philo *philo, t_table *table)
{
	uint64_t	current_time;
	uint64_t	last_meal_time;
	uint64_t	time_difference;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	current_time = get_current_time_in_ms();
	time_difference = current_time - last_meal_time;
	if (time_difference > table->time_to_die + MARGIN_ERR_DEAD_MS)
	{
		stop_simulation(table);
		print_status(philo, DEAD);
		if (CSS)
		{
			pthread_mutex_lock(&table->print_mutex);
			printf(COLOR_RED "💀 Philosopher %d died after %lu ms.\n"
				COLOR_RESET, philo->id, time_difference);
			pthread_mutex_unlock(&table->print_mutex);
		}
		return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief Checks if all philosophers have eaten the required number of meals.
 * If all philosophers have eaten at least the required number of meals,
 * it stops the simulation, prints a success message,
 * and frees resources.
 * @param table Pointer to the table struct containing the philosophers.
 * @param all_satisfied The number of philosophers
 * who have eaten the required meals.
 * @return TRUE if the simulation should continue, FALSE otherwise.
 */
static t_bool	all_philos_satisfied(t_table *table, int all_satisfied)
{
	if (table->meals_required != -1
		&& all_satisfied == table->num_philosophers)
	{
		stop_simulation(table);
		if (CSS)
		{
			pthread_mutex_lock(&table->print_mutex);
			printf(COLOR_GREEN "✅ All philosophers ate at least %ld meals.\n"
				COLOR_RESET, table->meals_required);
			pthread_mutex_unlock(&table->print_mutex);
		}
		return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief Checks if the dinner has ended by verifying
 * if any philosopher has died or if all philosophers
 * have eaten the required number of meals.
 * It iterates through all philosophers, checking their status.
 * If a philosopher has died, it stops the simulation.
 * If all philosophers have eaten the required meals,
 * it stops the simulation and prints a success message.
 * @param philos Pointer to the array of philosophers.
 * @param table Pointer to the table struct containing the philosophers.
 */
static void	check_end_of_dinner(t_philo *philos, t_table *table)
{
	int		i;
	int		meals_eaten;
	int		all_satisfied;

	i = -1;
	all_satisfied = 0;
	while (++i < table->num_philosophers)
	{
		if (philo_died(&philos[i], table))
			return ;
		if (table->meals_required != -1)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			meals_eaten = philos[i].meals_eaten;
			if (meals_eaten >= table->meals_required)
				all_satisfied++;
			pthread_mutex_unlock(&philos[i].meal_mutex);
		}
		if (all_philos_satisfied(table, all_satisfied))
			return ;
	}
}

/**
 * @brief Monitors the philosophers during the dinner.
 * It continuously checks if any philosopher has died
 * or if all philosophers have eaten the required number of meals.
 * If a philosopher dies, it stops the simulation and frees resources.
 * This function runs in a separate thread.
 * @param table Pointer to the table struct containing the philosophers.
 * @return NULL (as it is used as a thread function).
 */
void	*monitor_philos(t_table *table)
{
	while (should_continue(table))
	{
		check_end_of_dinner(table->philos, table);
		sleep_in_ms(1);
	}
	return (NULL);
}
