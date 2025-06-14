/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/13 21:31:18 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Processes the actions of a philosopher.
 * This function encapsulates the actions of a philosopher
 * in a single routine, allowing the philosopher to take forks,
 * eat, release forks, sleep, and think in a loop
 * until the simulation ends.
 * @param philo Pointer to the philosopher struct.
 */
static void	process_actions(t_philo *philo)
{
	philo_take_forks(philo);
	philo_eat(philo);
	philo_release_forks(philo);
	philo_sleep(philo);
	philo_think(philo);
}

/**
 * @brief The main routine for each philosopher thread.
 * This function is executed by each philosopher thread.
 * It handles the case where there is only one philosopher,
 * and processes the actions of the philosopher in a loop
 * until the simulation ends.
 * @param arg Pointer to the philosopher struct.
 */
void	*philo_routine(void *arg)
{
	t_philo			*philo;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	if (philo->table->num_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, TAKEN_FORKS);
		sleep_in_ms(philo->table->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (should_continue(philo->table))
		process_actions(philo);
	return (NULL);
}
