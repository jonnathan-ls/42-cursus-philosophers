/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:18:28 by jlacerda          #+#    #+#             */
/*   Updated: 2025/06/01 17:18:18 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Gets the current time in milliseconds.
 * @return The current time in milliseconds.
 */
size_t	get_current_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf(COLOR_RED GET_TIME_ERR_MSG COLOR_RESET);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @brief Sleeps for a specified number of milliseconds.
 * @return The current time in milliseconds.
 */
int	sleep_in_ms( size_t miliseconds)
{
	struct timeval	start;
	struct timeval	current;
	size_t			elapsed;

	if (miliseconds == 0)
		return (0);
	if (gettimeofday(&start, NULL) == -1)
		printf(COLOR_RED GET_TIME_ERR_MSG COLOR_RESET);
	while (TRUE)
	{
		if (gettimeofday(&current, NULL) == -1)
			printf(COLOR_RED GET_TIME_ERR_MSG COLOR_RESET);
		elapsed = (current.tv_sec - start.tv_sec) * 1000
			+ (current.tv_usec - start.tv_usec) / 1000;
		if (elapsed >= miliseconds)
			break ;
		usleep(100);
	}
	return (get_current_time_in_ms());
}

t_bool	should_continue(t_table *table)
{
	t_bool	result;

	if (!table)
		return (FALSE);
	pthread_mutex_lock(&table->philo_mutex);
	result = table->simulation_running;
	pthread_mutex_unlock(&table->philo_mutex);
	return (result);
}

void	stop_simulation(t_table *table)
{
	if (!table)
		return ;
	pthread_mutex_lock(&table->philo_mutex);
	table->simulation_running = FALSE;
	pthread_mutex_unlock(&table->philo_mutex);
}

void	print_status(t_philo *philo, t_status status)
{
	t_table		*table;
	long		timestamp;
	static char	*status_strs[] = {
		"has taken a fork",
		COLOR_YELLOW "is thinking" COLOR_RESET,
		COLOR_GREEN "is eating" COLOR_RESET,
		COLOR_BLUE "is sleeping"	COLOR_RESET,
		COLOR_RED "died" COLOR_RESET,
	};

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	if (should_continue(table) || status == DEAD)
	{
		timestamp = get_current_time_in_ms() - table->start_dinner_time;
		printf(COLOR_CYAN "%ld" COLOR_RESET " %d %s\n",
			timestamp, philo->id, status_strs[status]);
	}
	pthread_mutex_unlock(&table->print_mutex);
}
