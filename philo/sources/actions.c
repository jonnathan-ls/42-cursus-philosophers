/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:48:17 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/13 23:18:15 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
	* @brief Sleeps for a specified duration in milliseconds,
	* checking periodically if the simulation should continue.
	* This allows the simulation to be stopped gracefully
	* while a philosopher is sleeping.
	* @param table Pointer to the table struct containing the philosophers.
	* @param time_in_ms The duration to sleep in milliseconds.
	* @return TRUE if the sleep was completed
	* without interruption, FALSE otherwise.
	*/
t_bool	sleep_with_check(t_table *table, uint64_t time_in_ms)
{
	uint64_t	start_time;
	uint64_t	elapsed_time;

	elapsed_time = 0;
	start_time = get_current_time_in_ms();
	while (elapsed_time < time_in_ms)
	{
		if (!should_continue(table))
			return (FALSE);
		sleep_in_ms(5);
		elapsed_time = get_current_time_in_ms() - start_time;
	}
	return (TRUE);
}

/**
 * @brief Locks the forks for the philosopher to eat.
 * The philosopher takes the left fork first if their ID is even,
 * otherwise they take the right fork first.
 * Locks the forks in a way to avoid deadlock.
 * @param philo Pointer to the philosopher struct.
 */
void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKEN_FORKS);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKEN_FORKS);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKEN_FORKS);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKEN_FORKS);
	}
}

/**
 * @brief Philosopher eats for a specified duration.
 * Updates the last meal time and increments the meals eaten count.
 * Locks the meal mutex to ensure thread safety.
 * @param philo Pointer to the philosopher struct.
 */
void	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time_in_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, EATING);
	if (sleep_with_check(table, table->time_to_eat) && should_continue(table))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
	}
}

/**
 * @brief Releases the forks held by the philosopher.
 * The philosopher releases the left fork first if their ID is even,
 * otherwise they release the right fork first.
 * This helps to avoid deadlock and allows other philosophers to eat.
 * @param philo Pointer to the philosopher struct.
 */
void	philo_release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

/**
 * @brief Philosopher sleeps for a specified duration.
 * This simulates the time the philosopher spends sleeping after eating.
 * The philosopher will not be able to eat or think during this time.
 * @param philo Pointer to the philosopher struct.
 */
void	philo_sleep(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	print_status(philo, SLEEPING);
	sleep_with_check(table, table->time_to_sleep);
}
