/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/12 20:40:28 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Gets the current time in milliseconds since the epoch.
 * Uses gettimeofday to retrieve the current
 * time and converts it to milliseconds.
 * If an error occurs, prints an error message and returns 0.
 * @return The current time in milliseconds, or 0 on error.
 */
uint64_t	get_current_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf(COLOR_RED GET_TIME_ERR_MSG COLOR_RESET);
		return (0);
	}
	if (time.tv_sec < 0 || time.tv_usec < 0)
	{
		printf(COLOR_RED TIME_EVAL_VALUES_ERR_MSG COLOR_RESET
			"tv_sec=%ld, tv_usec=%ld\n", time.tv_sec, time.tv_usec);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @brief Sleeps for a specified duration in milliseconds.
 * Uses usleep to sleep for a fraction of the time
 * to allow for more frequent checks of the elapsed time.
 * @param time_ms The duration to sleep in milliseconds.
 * @return The current time in milliseconds after sleeping.
 */
uint64_t	sleep_in_ms(uint64_t time_ms)
{
	uint64_t	start_ms;
	uint64_t	elapsed_ms;
	uint64_t	current_time;

	if (time_ms == 0)
		return (0);
	start_ms = get_current_time_in_ms();
	while (TRUE)
	{
		usleep(time_ms / 10);
		current_time = get_current_time_in_ms();
		elapsed_ms = current_time - start_ms;
		if (elapsed_ms >= time_ms)
			break ;
	}
	return (get_current_time_in_ms());
}

/**
 * @brief Checks if the simulation should continue.
 * Checks the dinner_in_progress flag in the table struct
 * to determine if the simulation is still active.
 * @param table Pointer to the table struct.
 * @return TRUE if the simulation should continue, FALSE otherwise.
 */
t_bool	should_continue(t_table *table)
{
	t_bool	result;

	if (!table)
		return (FALSE);
	pthread_mutex_lock(&table->philo_mutex);
	result = table->dinner_in_progress;
	pthread_mutex_unlock(&table->philo_mutex);
	return (result);
}

/**
 * @brief Stops the simulation by setting the dinner_in_progress flag to FALSE.
 * This function is called when a philosopher dies or when the simulation
 * needs to be stopped for any reason.
 * @param table Pointer to the table struct.
 */
void	stop_simulation(t_table *table)
{
	if (!table)
		return ;
	pthread_mutex_lock(&table->philo_mutex);
	table->dinner_in_progress = FALSE;
	pthread_mutex_unlock(&table->philo_mutex);
}

/**
 * @brief Prints the status of a philosopher.
 * Prints a formatted message indicating the philosopher's status,
 * including the timestamp and philosopher ID.
 * The message is printed only if the philosopher
 * is dead or if the simulation is still in progress.
 * @param philo Pointer to the philosopher struct.
 * @param status The status of the philosopher to print.
 * The status can be DEAD, TAKEN_FORKS, THINKING, EATING, or SLEEPING.
 * @note The function locks the print_mutex to ensure thread safety
 * when printing the status message.
 */
void	print_status(t_philo *philo, t_status status)
{
	t_table		*table;
	uint64_t	timestamp;

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	if (status == DEAD || should_continue(table))
	{
		timestamp = get_current_time_in_ms() - table->start_dinner_time;
		printf(get_status_message(TIMESTAMP), timestamp);
		printf(get_status_message(PHILO_ID), philo->id);
		printf("%s\n", get_status_message(status));
	}
	pthread_mutex_unlock(&table->print_mutex);
}
