/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/13 21:31:06 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if a philosopher is dead.
 * Locks the meal mutex to safely access the last meal time,
 * calculates the time difference between the current time
 * and the last meal time, and checks if it exceeds the time to die.
 * If the philosopher is dead, stops the simulation and prints the status.
 * @param philo Pointer to the philosopher struct.
 * @param table Pointer to the table struct containing the philosopher.
 * @return TRUE if the philosopher is dead, FALSE otherwise.
 * * @note The function uses a margin of error
 * to account for timing inaccuracies.
 */
static t_bool	philo_is_dead(t_philo *philo, t_table *table)
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
			printf(COLOR_RED "💀 Philosopher %d is dead after %lu ms\n"
				COLOR_RESET, philo->id, time_difference);
			pthread_mutex_unlock(&table->print_mutex);
		}
		return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief Stops the simulation and prints a message if all philosophers
 * have eaten the required number of meals.
 * This function is called when all philosophers
 * have satisfied their meal requirements.
 * It locks the print mutex to ensure thread-safe printing.
 * @param table Pointer to the table struct containing the philosophers.
 * @return TRUE indicating that the simulation has ended successfully.
 */
static t_bool	all_philos_satisfied(t_table *table)
{
	if (CSS)
	{
		pthread_mutex_lock(&table->print_mutex);
		printf(COLOR_GREEN "✅ All philosophers have eaten %ld meals.\n",
			table->meals_required);
		pthread_mutex_unlock(&table->print_mutex);
		stop_simulation(table);
	}
	else
		stop_simulation(table);
	return (TRUE);
}

/**
 * @brief Checks if the dinner should end.
 * Iterates through all philosophers to check if any philosopher is dead.
 * If the meals_required is set, it checks if all philosophers
 * have eaten the required number of meals.
 * If all conditions are met, it stops the simulation and returns TRUE.
 * @param philos Pointer to the array of philosophers.
 * @param table Pointer to the table struct containing the philosophers.
 * @return TRUE if the dinner should end, FALSE otherwise.
 * @note The function uses a mutex to safely access the meals_eaten count
 * for each philosopher.
 */
static t_bool	should_end_dinner(t_philo *philos, t_table *table)
{
	int		i;
	int		meals_eaten;
	int		all_satisfied;

	i = -1;
	all_satisfied = 0;
	while (++i < table->num_philosophers)
	{
		if (philo_is_dead(&philos[i], table))
			return (TRUE);
		if (table->meals_required != -1)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			meals_eaten = philos[i].meals_eaten;
			pthread_mutex_unlock(&philos[i].meal_mutex);
			if (meals_eaten >= table->meals_required)
				all_satisfied++;
		}
	}
	if (table->meals_required != -1
		&& all_satisfied == table->num_philosophers)
		return (all_philos_satisfied(table));
	return (FALSE);
}

/**
 * @brief Monitors the philosophers during the dinner.
 * Continuously checks if any philosopher is dead or if all philosophers
 * have eaten the required number of meals. If any condition is met,
 * it stops the simulation and exits the monitoring thread.
 * @param table Pointer to the table struct containing the philosophers.
 */
void	*monitor_philos(t_table *table)
{
	t_philo		*philos;

	philos = table->philos;
	while (!should_end_dinner(philos, table))
		usleep(100);
	return (NULL);
}
