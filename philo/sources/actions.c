/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:48:17 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/12 20:38:43 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	sleep_in_ms(table->time_to_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
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
	sleep_in_ms(table->time_to_sleep);
}

/**
 * @brief Philosopher thinks for a short duration.
 * This simulates the time the philosopher spends thinking between meals.
 * The philosopher will not be able to eat or sleep during this time.
 * @param philo Pointer to the philosopher struct.
 */
void	philo_think(t_philo *philo)
{
	print_status(philo, THINKING);
	sleep_in_ms(1);
}
